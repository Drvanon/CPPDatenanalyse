#include "car.h"
#include <Eigen/Dense>

float MAX_ACC = 3;
float MAX_VEL = 6;

CarPool::CarPool(int size): Pool(size) {}

int CarPool::new_car(float pos_x, float pos_y) {
    Car new_car;
    new_car.id = this->index;
    new_car.pos_x = pos_x;
    new_car.pos_y = pos_y;
    new_car.vel_x = new_car.vel_y = new_car.acc_x = new_car.acc_y = 0;
    new_car.road = -1;

    this->pool[this->index] = new_car;
    this->pool[this->index].road = 1;
    this->index++;

    return new_car.id;
}

Car CarPool::get_car(int car_id) {
    return this->pool[car_id];
}

int CarPool::new_car_on_road(Road road) {
    int new_car_id = this->new_car(road.start_x, road.start_y);
    this->pool[new_car_id].road = road.id;
    return new_car_id;
}

void CarPool::behaviour(RoadPool road_pool) {
    for (int i=0;i<this->size;i++) {
        Car* car = &(this->pool[i]);
        if (car->road == -1)
            continue;

        Road road = road_pool.get_road(car->road);

        Eigen::Vector2f start;
        start << road.start_x, road.start_y;
        Eigen::Vector2f stop;
        stop << road.stop_x, road.stop_y;

        Eigen::Vector2f direction = (stop - start).normalized();
        Eigen::Vector2f acc = direction * MAX_ACC;

        car->acc_x = acc(0);
        car->acc_y = acc(1);
    }
}

void CarPool::physics(float dT) {
    for (int i=0;i<this->size;i++) {
        this->pool[i].pos_x += this->pool[i].vel_x * dT;
        this->pool[i].pos_y += this->pool[i].vel_y * dT;
        this->pool[i].vel_x += this->pool[i].acc_x * dT;
        this->pool[i].vel_y += this->pool[i].acc_y * dT;
    }
}

void CarPool::display(SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    for (int i=0;i<this->size;i++) {
        Car car = this->pool[i];
        SDL_Rect rect(car.pos_x, car.pos_y, 5, 10);
        SDL_RenderFillRect(rend, &rect);
    }
}
