#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include <Eigen/Dense>
#include <vector>
#include <random>

#include "pool.h"
#include "road.h"

struct Car {
    int id;
    Eigen::Vector2f pos;
    Eigen::Vector2f vel;
    Eigen::Vector2f acc;
    float max_vel;
    float max_acc;
    float max_steer;
    bool alive;
};

class CarPool: public Pool<Car> {
    private:
        float distance_to_car_in_front(Car& car);
        std::default_random_engine random_generator;
        std::normal_distribution<float> acc_dist;
        std::normal_distribution<float> vel_dist;
        std::normal_distribution<float> steer_dist;
        Eigen::Vector2f accelerate_car_towards(Car car, Eigen::Vector2f goal);
    public:
        int new_car(Eigen::Vector2f pos);
        void set_car_road(int car_id, int road_id);
        Car get_car(int car_id);
        void behaviour(Road* road);
        void physics(float dT);
        void display(SDL_Renderer* renderer, Road* road);
        CarPool(int size);
};

#endif
