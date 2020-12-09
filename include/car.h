#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include <Eigen/Dense>
#include "pool.h"
#include "road.h"
#include "path.h"

struct Car {
    int id;
    Eigen::Vector2f pos;
    Eigen::Vector2f vel;
    Eigen::Vector2f acc;
    int road;
    int path;
    bool alive;
};

class CarPool: public Pool<Car> {
    public:
        int new_car(float pos_x, float pos_y);
        void set_car_road(int car_id, int road_id);
        int new_car_on_road(Road road);
        int new_car_on_path(int path, RoadPool& road_pool, PathPool& path_pool);
        Car get_car(int car_id);
        void behaviour(RoadPool& road_pool, PathPool& path_pool);
        void physics(float dT);
        void display(SDL_Renderer* renderer);
        CarPool(int size);
};

#endif
