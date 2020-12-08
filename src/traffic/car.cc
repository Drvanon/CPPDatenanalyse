#include "car.h"

float MAX_ACC = 10;
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

    this->pool[this->index] = new_car;
    this->index++;

    return new_car.id;
}

Car CarPool::get_car(int car_id) {
    return this->pool[car_id];
}

int CarPool::new_car_on_road(Road road) {
    int new_car_id = this->new_car(road.start(0), road.start(1));
    this->pool[new_car_id].road = road.id;
    return new_car_id;
}

int CarPool::new_car_on_path(int path, RoadPool road_pool, PathPool path_pool) {
    int road_id = path_pool.get_first_road(path);
    Road road = road_pool.get_road(road_id);
    int new_car_id = this->new_car_on_road(road);
    this->pool[new_car_id].path = path;
    return new_car_id;
}

void CarPool::behaviour(RoadPool road_pool, PathPool path_pool) {
    for (int i=0;i<this->size;i++) {
        Car* car = &(this->pool[i]);
        if (car->road == -1)
            continue;

        Road road = road_pool.get_road(car->road);

        Eigen::Vector2f direction = (road.stop - car->pos).normalized();
        Eigen::Vector2f acc = direction * MAX_ACC;
        car->acc = acc;

        // If the stopping point could be reached within a second
        // switch to the next point if available.
        if (
            (car->pos - road.stop).norm() < MAX_VEL
        ) {
            if (
                car->path == -1 ||
                path_pool.get_next_path_piece(car->path, car->road) == -1
            ) {
                car->alive = false;
            } else {
                car->road = path_pool.get_next_path_piece(car->path, car->road);
            }
        }
    }
}

void CarPool::physics(float dT) {
    for (int i=0;i<this->size;i++) {
        Car* car = &this->pool[i];
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

    for (int i=0;i<this->size;i++) {
        Car car = this->pool[i];
        if (!car.alive) continue;
        SDL_Rect rect(car.pos(0), car.pos(1), 5, 10);
        SDL_RenderFillRect(rend, &rect);
    }
}
