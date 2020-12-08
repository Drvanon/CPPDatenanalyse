#ifndef ROAD_H
#define ROAD_H

#include <SDL2/SDL.h>
#include <Eigen/Dense>

#include "road.h"
#include "entities.h"
#include "pool.h"


struct Road {
    int id;
    Eigen::Vector2f start;
    Eigen::Vector2f stop;
};

class RoadPool: public Pool<Road> {
    private:
        int index;
    public:
        RoadPool(int size);
        void display(SDL_Renderer* rend);
        int new_road();
        int new_road(float start_x, float start_y, float stop_x, float stop_y);
        Road get_road(int id);
        void set_road_start(int id, Eigen::Vector2f pos);
        void set_road_stop(int id, Eigen::Vector2f pos);
};

#endif
