#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <Eigen/Dense>
#include <vector>
#include "road.h"

enum DIR_IN_OUT {
    RIGHT_IN,
    RIGHT_OUT,
    BOTTOM_IN,
    BOTTOM_OUT,
    LEFT_IN,
    LEFT_OUT,
    TOP_IN,
    TOP_OUT
};

struct Intersection {
    int id;
    int road[8];
    int intersection[8];
    Eigen::Vector2f pos;
};

class IntersectionPool: public Pool<Intersection> {
    private:
        int find_road_between_intersections(int int1_id, int int2_id);
    public:
        IntersectionPool(int size);
        Eigen::Vector2f get_connection_position(int intersection_id, int direction_id);
        int new_intersection(float pos_x, float pos_y);
        void connect_road_start(int intersection_id, int direction_id, int road_id, RoadPool& road_pool);
        void connect_road_stop(int intersection_id, int direction_id, int road_id, RoadPool& road_pool);
        std::vector<int> generate_path(int steps);
        int new_road_between_intersections(
            int start_intersection_id, int stop_intersection_id,
            int start_direction, int stop_direction,
            RoadPool& road_pool
        );
        void display(SDL_Renderer* renderer, TTF_Font* font);
};

#endif
