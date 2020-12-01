#ifndef ROAD_H
#define ROAD_H

#include <SDL2/SDL.h>

#include "road.h"
#include "entities.h"
#include "pool.h"


struct Road {
    int id;
    float start_x;
    float start_y;
    float stop_x;
    float stop_y;
};

class RoadPool: public Pool<Road> {
    public:
        RoadPool(int size);
        void display(SDL_Renderer* rend);
        void new_road(float start_x, float start_y, float stop_x, float stop_y);
};

#endif
