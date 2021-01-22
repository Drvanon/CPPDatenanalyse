#include "car.h"

#include <cmath>
#include <iostream>

float MAX_ACC = 40;
float MAX_VEL = 20;

CarPool::CarPool(int size): Pool(size) {}

int CarPool::new_car(float pos_x, float pos_y) {
    Car new_car;
    new_car.id = this->index;
    new_car.alive = true;
    new_car.pos = Eigen::Vector2f(pos_x, pos_y);
    new_car.vel = Eigen::Vector2f::Zero();
    new_car.acc = Eigen::Vector2f::Zero();
    new_car.road = -1;
    new_car.path = -1;
    new_car.path_step = -1;

    (*this)[this->index] = new_car;
    this->index++;

    return new_car.id;
}

void CarPool::new_path(std::vector<int> path) {
    this->paths.push_back(path);
}

Car CarPool::get_car(int car_id) {
    return (*this)[car_id];
}

int CarPool::new_car_on_road(Road road) {
    int new_car_id = this->new_car(road.start(0), road.start(1));
    (*this)[new_car_id].road = road.id;
    return new_car_id;
}

int CarPool::new_car_on_path(int path, RoadPool& road_pool) {
    int road_id = this->paths[path][0];
    Road road = road_pool[road_id];
    int new_car_id = this->new_car_on_road(road);
    (*this)[new_car_id].path = path;
    (*this)[new_car_id].path_step = 0;
    return new_car_id;
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

Eigen::Vector2f find_goal(Eigen::Vector2f car_pos, Road road) {
    if (
        (car_pos - road.start).dot(road.stop - road.start) > 0 ||
        (car_pos - road.start).norm() < MAX_VEL / 10
    ) {
        return road.stop;
    } else {
        return road.start;
    }
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

bool CarPool::car_close_to_end_of_road(Car car, Road road) {
    return (car.pos - road.stop).norm() < car.vel.norm() / 5;
}

bool CarPool::car_at_end_of_path(Car car) {
    bool at_end = (
        car.path == -1 ||
        ( this->paths[car.path].size() == car.path_step )
    );

    return at_end;
}

void CarPool::behaviour(RoadPool& road_pool) {
    for (int i=0;i<this->index;i++) {
        Car* car = &((*this)[i]);
        if (car->road == -1 || not car->alive) continue;

        Road road = road_pool[car->road];
        Eigen::Vector2f goal = find_goal(car->pos, road);
        car->acc = accelerate_car_towards(*car, goal);
        car->acc += steer_towards(*car, goal);

        // If the stopping point could be reached within a second
        // switch to the next point if available.
        if (car_close_to_end_of_road(*car, road)) {
            car->path_step++;
            if (this->car_at_end_of_path(*car)) {
                car->alive = false;
            } else {
                std::cout << "Car " << car->id << " was on road " << car->road;
                car->road = this->paths[car->path][car->path_step];
                std::cout << " and now is on road " << car->road
                          << " step: " << car->path_step
                          << "/" << this->paths[car->path].size()
                          << " on path " << car->path << std::endl;
            }
        }
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
        SDL_Rect rect(car.pos(0), car.pos(1), 5, 10);
        SDL_RenderFillRect(rend, &rect);
    }
}
