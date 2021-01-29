#ifndef CAR_H
#define CAR_H

#include "cuda_runtime.h"
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

class CarPool {
    private:
        Car* device_cars;
        Car* host_cars;
        int index;
        int size;
        std::default_random_engine random_generator;
        std::normal_distribution<float> acc_dist;
        std::normal_distribution<float> vel_dist;
        std::normal_distribution<float> steer_dist;
    public:
        int new_car(Eigen::Vector2f pos);
        void behaviour(Road* road);
        void physics(float dT);
        void display(SDL_Renderer* renderer, Road* road);
        CarPool(int size);
        ~CarPool();
};

#endif
