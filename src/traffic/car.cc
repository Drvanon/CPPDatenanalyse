#include "car.h"

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

Eigen::Vector2f find_goal(Eigen::Vector2f car_pos, Road road) {
    if (
        (car_pos - road.start).dot(road.stop - road.start) > 0
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

    if (-0.0001 < perp_anticlockwise.dot(goal - car.pos) && perp_anticlockwise.dot(goal - car.pos) < 0.0001 ) {
        acc = MAX_ACC * (goal - car.pos).normalized();
    } else {
        if (perp_anticlockwise.dot(goal - car.pos) > 0.0001 ) {
            acc = MAX_ACC * perp_anticlockwise;
        } else {
            acc = MAX_ACC * perp_clockwise;
        }
    }

    return acc;
}

bool CarPool::car_close_to_end_of_road(Car car, Road road) {
    return (car.pos - road.stop).norm() < car.vel.norm() / 5;
}

bool CarPool::car_at_end_of_path(Car car) {
    return (
        car.path == -1 ||
        this->paths[car.path].size() <= car.path_step
    );
}

void CarPool::behaviour(RoadPool& road_pool) {
    for (int i=0;i<this->size;i++) {
        Car* car = &((*this)[i]);
        if (car->road == -1 || not car->alive) continue;

        Road road = road_pool[car->road];
        Eigen::Vector2f goal = find_goal(car->pos, road);
        car->acc = steer_towards(*car, goal);

        // If the stopping point could be reached within a second
        // switch to the next point if available.
        if (car_close_to_end_of_road(*car, road)) {
            if (car_at_end_of_path(*car)) {
                car->alive = false;
            } else {
                std::cout << "Car " << car->id << " was on road " << car->road;
                car->path_step++;
                car->road = this->paths[car->path][car->path_step];
                std::cout << " and now is on road " << car->road << std::endl;
            }
        }
    }
}

void CarPool::physics(float dT) {
    for (int i=0;i<this->size;i++) {
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
