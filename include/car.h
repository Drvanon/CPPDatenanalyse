#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include "pool.h"

struct Car {
    int id;
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    float acc_x;
    float acc_y;
    int road;
    int path;
};

class CarPool: public Pool<Car> {
    public:
        void new_car(float pos_x, float pos_y);
        void display(SDL_Renderer* renderer);
        void physics(float dT);
        CarPool(int size);
};

#endif
