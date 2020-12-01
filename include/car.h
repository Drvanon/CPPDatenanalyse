#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include "pool.h"
#include "road.h"

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
        int new_car(float pos_x, float pos_y);
        void set_car_road(int car_id, int road_id);
        int new_car_on_road(Road road);
        Car get_car(int car_id);
        void behaviour(RoadPool road_pool);
        void physics(float dT);
        void display(SDL_Renderer* renderer);
        CarPool(int size);
};

#endif
