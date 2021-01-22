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
        float distance_to_car_in_front(Car& car);
        Eigen::Vector2f accelerate_car_towards(Car car, Eigen::Vector2f goal);
    public:
        int new_car(Eigen::Vector2f pos);
        void set_car_road(int car_id, int road_id);
        Car get_car(int car_id);
        void behaviour(Road road);
        void physics(float dT);
        void display(SDL_Renderer* renderer);
        CarPool(int size);
};

#endif
