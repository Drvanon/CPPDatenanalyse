#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include <Eigen/Dense>
#include <vector>
#include "pool.h"
#include "road.h"

struct Car {
    int id;
    Eigen::Vector2f pos;
    Eigen::Vector2f vel;
    Eigen::Vector2f acc;
    int road;
    int path;
    int path_step;
    bool alive;
};

class CarPool: public Pool<Car> {
    private:
        std::vector<std::vector<int>> paths;
    public:
        int new_car(float pos_x, float pos_y);
        void new_path(std::vector<int> path);
        void set_car_road(int car_id, int road_id);
        int new_car_on_road(Road road);
        int new_car_on_path(int path, RoadPool& road_pool);
        Car get_car(int car_id);
        void behaviour(RoadPool& road_pool);
        void physics(float dT);
        void display(SDL_Renderer* renderer);
        CarPool(int size);
};

#endif
