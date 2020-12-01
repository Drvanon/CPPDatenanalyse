#include "car.h"

float MAX_ACC = 3;
float MAX_VEL = 6;

CarPool::CarPool(int size): Pool(size) {}

int CarPool::new_car(float pos_x, float pos_y) {
    Car new_car;
    new_car.id = this->index;

    Eigen::Vector2f pos;
    Eigen::Vector2f vel;
    Eigen::Vector2f acc;

    pos << pos_x, pos_y;
    vel << 0, 0;
    acc = vel;
    new_car.pos = pos;
    new_car.vel = vel;
    new_car.acc = acc;
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
    int new_car_id = this->new_car(road.start(0), road.start(1));
    this->pool[new_car_id].road = road.id;
    return new_car_id;
}

void CarPool::behaviour(RoadPool road_pool) {
    for (int i=0;i<this->size;i++) {
        Car* car = &(this->pool[i]);
        if (car->road == -1)
            continue;

        Road road = road_pool.get_road(car->road);

        Eigen::Vector2f direction = (road.stop - road.start).normalized();
        Eigen::Vector2f acc = direction * MAX_ACC;
        car->acc = acc;
    }
}

void CarPool::physics(float dT) {
    for (int i=0;i<this->size;i++) {
        Car* car = &this->pool[i];
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
        SDL_Rect rect(car.pos(0), car.pos(1), 5, 10);
        SDL_RenderFillRect(rend, &rect);
    }
}
