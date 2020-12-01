#include "traffic.h"
#include "car.h"
#include "pool.h"
#include "entities.h"

CarPool::CarPool(int size): Pool(size) {}

void CarPool::new_car(float pos_x, float pos_y) {
    Car new_car;
    new_car.pos_x = pos_x;
    new_car.pos_y = pos_y;
    new_car.vel_x = new_car.vel_y = new_car.acc_x = new_car.acc_y = 0;

    this->pool[this->index] = new_car;
    this->index++;
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
