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

CarPool::CarPool(int size): Pool(size) {
    this->acc_dist = std::normal_distribution(MEAN_ACC, FWHM_ACC);
    this->vel_dist = std::normal_distribution(MEAN_VEL, FWHM_VEL);
    this->steer_dist = std::normal_distribution(MEAN_STEER, FWHM_STEER);
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

    (*this)[this->index] = new_car;
    this->index++;

    return new_car.id;
}

Car CarPool::get_car(int car_id) {
    return (*this)[car_id];
}

float CarPool::distance_to_car_in_front(Car& car) {
    // Arbitratrily large distance acting as infinity.
    float distance = 1000000;
    for (int i=0; i<this->index; i++) {
        Car other_car = (*this)[i];
        if (other_car.id == car.id) continue;
        // Other car must be in front of this one.
        if (car.vel.dot(other_car.pos - car.pos) < 0) continue;
        float distance_i = (car.pos - other_car.pos).norm();
        distance = std::min(distance_i, distance);
    }
    return distance;
}

vec2f get_perpendicular_clockwise(vec2f vec) {
    return vec2f(vec(1), -vec(0)).normalized();
}

vec2f steer_towards(Car car, vec2f goal) {
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

float sigmoid(float x) {
    float res = 1 / (1 +  exp(-x))-.5;
    if (res > 0) res = 0;
    return res;
}

vec2f CarPool::accelerate_car_towards(Car car, vec2f goal) {
    float dist_next_car = this->distance_to_car_in_front(car);

    vec2f dir;
    if (car.vel.norm() < car.max_vel * 0.01) {
        dir = (goal - car.pos).normalized();
    } else {
        dir = car.vel.normalized();
    }
    vec2f acc = dir * car.max_acc;

    if (dist_next_car < 0.6 * car.max_vel) {
        float scared_factor = sigmoid(dist_next_car - car.vel.norm());
        std::cout << "Scared factor: " << scared_factor << std::endl;
        acc *= scared_factor;
    }

    return acc;
}

vec2f find_goal(vec2f pos) {
    return pos + vec2f(300, 0);
}

void CarPool::behaviour(Road* road) {
    for (int i=0;i<this->index;i++) {
        Car* car = &((*this)[i]);
        if (not car->alive) continue;

        if (car->pos(0) > road->length) {
            car->pos -= vec2f(road->length, 0);
        }
        vec2f goal = find_goal(car->pos);
        car->acc = accelerate_car_towards(*car, goal);
        car->acc += steer_towards(*car, goal);
    }
}

void CarPool::physics(float dT) {
    for (int i=0;i<this->index;i++) {
        Car* car = &(*this)[i];
        if (!car->alive) continue;
        car->pos += car->vel * dT;
        car->vel += car->acc * dT;

        // Implement a physical speed limit.
        if (car->vel.norm() > car->max_vel) {
            car->vel.normalize();
            car->vel *= car->max_vel;
        }
    }
}

void CarPool::display(SDL_Renderer* rend, Road* road) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    for (int i=0;i<this->index;i++) {
        Car car = (*this)[i];
        if (!car.alive) continue;
        vec2f pos = road->get_display_position(car.pos);
        SDL_Rect rect(pos(0), pos(1), CAR_LENGTH, CAR_WIDTH);
        SDL_RenderFillRect(rend, &rect);
    }
}
