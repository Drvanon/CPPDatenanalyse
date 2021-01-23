#include "car.h"

#include <cmath>
#include <iostream>

float MAX_ACC = 40;
float MAX_VEL = 20;
int CAR_WIDTH = 5;
int CAR_LENGTH = 10;

CarPool::CarPool(int size): Pool(size) {}

int CarPool::new_car(Eigen::Vector2f pos) {
    Car new_car;
    new_car.id = this->index;
    new_car.alive = true;
    new_car.pos = pos;
    new_car.vel = Eigen::Vector2f::Zero();
    new_car.acc = Eigen::Vector2f::Zero();
    new_car.road = -1;
    new_car.path = -1;
    new_car.path_step = -1;

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
        if (other_car.road != car.road || other_car.id == car.id) continue;
        // Other car must be in front of this one.
        if (car.vel.dot(other_car.pos - car.pos) < 0) continue;
        float distance_i = (car.pos - other_car.pos).norm();
        distance = std::min(distance_i, distance);
    }
    return distance;
}

Eigen::Vector2f get_perpendicular_clockwise(Eigen::Vector2f vec) {
    return Eigen::Vector2f(vec(1), -vec(0)).normalized();
}

Eigen::Vector2f steer_towards(Car car, Eigen::Vector2f goal) {
    Eigen::Vector2f perp_clockwise = get_perpendicular_clockwise(car.vel);
    Eigen::Vector2f perp_anticlockwise = -perp_clockwise;
    Eigen::Vector2f acc;

    if (perp_anticlockwise.dot(goal - car.pos) > 0.0001 ) {
        acc = MAX_ACC * perp_anticlockwise;
    }
    if (perp_clockwise.dot(goal - car.pos) > 0.0001 ) {
        acc = MAX_ACC * perp_clockwise;
    }

    return acc;
}

float sigmoid(float x) {
    return 1 / (1 +  exp(-x))-.5;
}

Eigen::Vector2f CarPool::accelerate_car_towards(Car car, Eigen::Vector2f goal) {
    float dist_next_car = this->distance_to_car_in_front(car);

    Eigen::Vector2f dir;
    if (car.vel.norm() < MAX_VEL * 0.01) {
        dir = (goal - car.pos).normalized();
    } else {
        dir = car.vel.normalized();
    }
    Eigen::Vector2f acc = dir * MAX_ACC;

    if (dist_next_car < 0.6 * MAX_VEL) {
        float scared_factor = sigmoid(dist_next_car - car.vel.norm());
        // std::cout << "Scared factor: " << scared_factor << std::endl;
        acc *= scared_factor;
    }

    return acc;
}

void CarPool::behaviour() {
    for (int i=0;i<this->index;i++) {
        Car* car = &((*this)[i]);
        if (car->road == -1 || not car->alive) continue;

        Eigen::Vector2f goal = Eigen::Vector2f::Zero(); // find_goal(car->pos, road);
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
        if (car->vel.norm() > MAX_VEL) {
            car->vel.normalize();
            car->vel *= MAX_VEL;
        }
    }
}

void CarPool::display(SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    for (int i=0;i<this->index;i++) {
        Car car = (*this)[i];
        if (!car.alive) continue;
        SDL_Rect rect(car.pos(0), car.pos(1), CAR_WIDTH, CAR_LENGTH);
        SDL_RenderFillRect(rend, &rect);
    }
}
