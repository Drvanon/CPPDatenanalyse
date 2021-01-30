#include "car.h"

#include <cmath>
#include <iostream>

typedef Eigen::Vector2f vec2f;

float MEAN_ACC = 40;
float FWHM_ACC = 10;
float MEAN_VEL = 50;
float FWHM_VEL = 10;
float MEAN_STEER = 10;
float FWHM_STEER = 5;
int CAR_WIDTH = 5;
int CAR_LENGTH = 10;

#define CUDA_WARN(XXX) \
    do { if (XXX != cudaSuccess) {std::cerr << "CUDA Error: " << \
    cudaGetErrorString(XXX) << ", at line " << __LINE__ \
    << " in file " __FILE__ << std::endl; \
    cudaDeviceSynchronize(); exit(EXIT_FAILURE);} } while (0)

CarPool::CarPool(int size): size(size) {
    this->index = 0;
    this->acc_dist = std::normal_distribution<float>(MEAN_ACC, FWHM_ACC);
    this->vel_dist = std::normal_distribution<float>(MEAN_VEL, FWHM_VEL);
    this->steer_dist = std::normal_distribution<float>(MEAN_STEER, FWHM_STEER);

    this->host_cars = new Car[size];
    for (int i=0; i<this->size; i++) {
        this->host_cars[i].alive = 0;
        this->host_cars[i].id = -1;
        this->host_cars[i].pos = vec2f::Zero();
        this->host_cars[i].vel = vec2f::Zero();
        this->host_cars[i].acc = vec2f::Zero();
    }

    CUDA_WARN(cudaMalloc(&(this->device_cars), size * sizeof(Car)));
    CUDA_WARN(cudaMemcpy(this->device_cars, this->host_cars, size * sizeof(Car), cudaMemcpyHostToDevice));
}

int CarPool::new_car(vec2f pos) {
    Car new_car;
    new_car.id = this->index;
    new_car.alive = true;
    new_car.pos = pos;
    new_car.vel = vec2f::Zero();
    new_car.acc = vec2f::Zero();

    new_car.max_acc = this->acc_dist(this->random_generator);
    new_car.max_vel = this->vel_dist(this->random_generator);
    new_car.max_steer = this->steer_dist(this->random_generator);

    std::cout << "New car created." << std::endl
        << "\tid: " << new_car.id << std::endl
        << "\tmax acc: " << new_car.max_acc << std::endl
        << "\tmax vel: " << new_car.max_vel << std::endl
        << "\tmax steer: " << new_car.max_steer << std::endl;

    CUDA_WARN(cudaMemcpy(this->device_cars + this->index, &new_car, sizeof(Car), cudaMemcpyHostToDevice));
    this->index++;

    return new_car.id;
}

__device__ float distance_to_car_in_front(Car& car, Car* cars, int cur_car_index) {
    // Arbitratrily large distance acting as infinity.
    float distance = 1000000;
    for (int i=0; i<cur_car_index; i++) {
        Car other_car = cars[i];
        if (other_car.id == car.id) continue;
        // Other car must be in front of this one.
        if (car.vel.dot(other_car.pos - car.pos) < 0) continue;
        float distance_i = (car.pos - other_car.pos).norm();
        distance = min(distance_i, distance);
    }
    return distance;
}

__device__ vec2f get_perpendicular_clockwise(vec2f vec) {
    return vec2f(vec(1), -vec(0)).normalized();
}

__device__ vec2f steer_towards(Car car, vec2f goal) {
    vec2f perp_clockwise = get_perpendicular_clockwise(car.vel);
    vec2f perp_anticlockwise = -perp_clockwise;
    vec2f acc = vec2f::Zero();

    if (perp_anticlockwise.dot(goal - car.pos) > 0.0001 ) {
        acc = car.max_steer * perp_anticlockwise;
    }
    if (perp_clockwise.dot(goal - car.pos) > 0.0001 ) {
        acc = car.max_steer * perp_clockwise;
    }

    return acc;
}

__device__ float sigmoid(float x) {
    float res = 1 / (1 +  exp(-x))-.5;
    if (res > 0) res = 0;
    return res;
}

__device__ vec2f accelerate_car_towards(Car car, vec2f goal, Car* cars, int cur_car_index) {
    float dist_next_car = distance_to_car_in_front(car, cars, cur_car_index);

    vec2f dir;
    if (car.vel.norm() < car.max_vel * 0.01) {
        dir = (goal - car.pos).normalized();
    } else {
        dir = car.vel.normalized();
    }
    vec2f acc = dir * car.max_acc;

    if (dist_next_car < 0.6 * car.max_vel) {
        float scared_factor = sigmoid(dist_next_car - car.vel.norm());
        acc *= scared_factor;
    }

    return acc;
}

__device__ vec2f find_goal(vec2f pos) {
    return pos + vec2f(300, 0);
}

__global__ void behaviour_kernel(int road_length, Car* cars, int cur_car_index) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i > cur_car_index - 1) return;
    Car car = cars[i];
    if (not car.alive) return;
    if (car.pos(0) > road_length) {
        car.pos -= vec2f(road_length, 0);
    }
    vec2f goal = find_goal(car.pos);
    car.acc = accelerate_car_towards(car, goal, cars, cur_car_index);
    car.acc += steer_towards(car, goal);
    cars[i] = car;
}

void CarPool::behaviour(Road* road) {
    behaviour_kernel<<< 1 + this->size/256, 256>>>(road->length, this->device_cars, this->index);
    cudaDeviceSynchronize();
}

__global__ void physics_kernel(float dT, Car* cars, int cur_car_index) {
    int i = threadIdx.x + blockIdx.x*blockDim.x;
    if (i > cur_car_index) return;
    Car car = cars[i];
    if (!car.alive) return;
    car.pos += car.vel * dT;
    car.vel += car.acc * dT;

    // Implement a physical speed limit.
    if (car.vel.norm() > car.max_vel) {
        car.vel.normalize();
        car.vel *= car.max_vel;
    }
    cars[i] = car;
}

__host__ void CarPool::physics(float dT) {
    physics_kernel<<< 1 + this->size/256, 256>>>(dT, this->device_cars, this->index);
    cudaDeviceSynchronize();
}

void CarPool::display(SDL_Manager& sdl, Road* road) {
    CUDA_WARN(cudaMemcpy(this->host_cars, this->device_cars, size * sizeof(Car), cudaMemcpyDeviceToHost));

    SDL_SetRenderDrawColor(sdl.rend, 255, 0, 0, 255);
    for (int i=0;i<this->index;i++) {
        Car car = this->host_cars[i];
        if (!car.alive) continue;
        vec2f pos = road->get_display_position(car.pos);
        SDL_Rect rect;
        rect.x = pos(0);
        rect.y = pos(1);
        rect.w = CAR_LENGTH;
        rect.h = CAR_WIDTH;
        SDL_RenderFillRect(sdl.rend, &rect);
    }
}

CarPool::~CarPool() {
    cudaFree(this->device_cars);
    free(this->host_cars);
}
