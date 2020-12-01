#include <SDL2/SDL.h>
#include "traffic.h"
#include "car.h"
#include "pool.h"
#include "entities.h"

void car_physics(Pool<Car>& car_pool, float dT) {
    for (int i=0;i<car_pool.size;i++) {
        car_pool.pool[i].pos_x += car_pool.pool[i].vel_x * dT;
        car_pool.pool[i].pos_y += car_pool.pool[i].vel_y * dT;
        car_pool.pool[i].vel_x += car_pool.pool[i].acc_x * dT;
        car_pool.pool[i].vel_y += car_pool.pool[i].acc_y * dT;
    }
}

void display_cars(Pool<Car>& car_pool, SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); // the rect color (solid red)

    for (int i=0;i<car_pool.size;i++) {
        Car car = car_pool.pool[i];
        SDL_Rect rect(car.pos_x, car.pos_y, 5, 10);
        SDL_RenderFillRect(rend, &rect);
    }
}

void null_car(Car& car) {
    car.pos_x = 1;
    car.pos_y = 1;
    car.vel_x = 0;
    car.vel_y = 0;
    car.acc_x = 0;
    car.acc_y = 0;
}
