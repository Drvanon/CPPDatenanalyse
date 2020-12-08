#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <SDL2/SDL.h>
#include <Eigen/Dense>
#include "road.h"

struct Intersection {
    int id;
    int road[8];
    Eigen::Vector2f pos;
};

class IntersectionPool: public Pool<Intersection> {
    public:
        IntersectionPool(int size);
        Eigen::Vector2f get_connection_position(int intersection_id, int direction_id);
        int new_intersection(float pos_x, float pos_y);
        int new_road_between_intersections(
            int intersection1_id, int intersection2_id,
            int direction_index_1, int direction_index_2,
            RoadPool road_pool
        );
        void display(SDL_Renderer* renderer);
};

#endif
