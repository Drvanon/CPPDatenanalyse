#include "intersection.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include "road.h"


IntersectionPool::IntersectionPool(int size): Pool(size) {
    this->index = 0;
    for (int i=0; i<size; i++) {
        for (int j=0; j<8; j++) {
            this->pool[i].road[j] = -1;
        }
    }
    for (int i=0; i<size; i++) {
        for (int j=0; j<8; j++) {
            this->pool[i].intersection[j] = -1;
        }
    }
}

int IntersectionPool::new_intersection(float pos_x, float pos_y) {
    Intersection new_intersection;
    new_intersection.pos = Eigen::Vector2f(pos_x, pos_y);
    new_intersection.id = this->index;
    for (int i=0;i < 8; i++) {
        new_intersection.road[i] = -1;
        new_intersection.intersection[i] = -1;
    }

    (*this)[this->index] = new_intersection;
    this->index++;

    return new_intersection.id;
}

float custom_round(float a) {
    return round(a);
}

Eigen::Vector2f IntersectionPool::get_connection_position(int intersection_id, int direction_id) {
    float INTERSECTION_RADIUS = 15;

    Intersection* intersection = &(*this)[intersection_id];
    Eigen::Vector2f pos = intersection->pos;

    // Main direction
    Eigen::Vector2f relative;
    relative << INTERSECTION_RADIUS * cos(2 * M_PI / 4 * floor(direction_id / 2)),
                INTERSECTION_RADIUS * sin(2 * M_PI / 4 * floor(direction_id / 2));
    // In/out
    Eigen::Vector2f in_out;
    in_out << INTERSECTION_RADIUS / 4 * cos(2 * M_PI / 4 * floor(direction_id / 2) + M_PI * (direction_id % 2) + M_PI/2),
              INTERSECTION_RADIUS / 4 * sin(2 * M_PI / 4 * floor(direction_id / 2) + M_PI * (direction_id % 2) + M_PI/2);

    Eigen::Vector2f res = pos + relative + in_out;
    res.unaryExpr(&custom_round);
    return res;
}

void IntersectionPool::display(SDL_Renderer* rend) {
    for (int i=0; i<this->index; i++) {
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
        Intersection intersection = (*this)[i];
        SDL_Rect rect(intersection.pos(0), intersection.pos(1), 5, 5);

        for (int j=0; j<8; j++) {
            if (intersection.road[j] == -1) continue;
            if ( j % 2 )
                SDL_SetRenderDrawColor(rend, 0, 255, 255, 255);
            else
                SDL_SetRenderDrawColor(rend, 255, 0, 255, 255);


            Eigen::Vector2f pos = this->get_connection_position(i, j);
            SDL_Rect rect(pos(0), pos(1), 3, 3);
            SDL_RenderFillRect(rend, &rect);
        }

    }
}

void IntersectionPool::connect_road_start(int intersection_id, int direction_id, int road_id, RoadPool& road_pool) {
    Intersection* inters = &(*this)[intersection_id];
    inters->road[direction_id] = road_id;
    road_pool.set_road_start(road_id, this->get_connection_position(intersection_id, direction_id));
}

void IntersectionPool::connect_road_stop(int intersection_id, int direction_id, int road_id, RoadPool& road_pool) {
    Intersection* inters = &(*this)[intersection_id];
    inters->road[direction_id] = road_id;
    road_pool.set_road_stop(road_id, this->get_connection_position(intersection_id, direction_id));
}

int IntersectionPool::new_road_between_intersections(
    int start_intersection_id, int stop_intersection_id,
    int start_direction, int stop_direction,
    RoadPool& road_pool
) {
    int new_id = road_pool.new_road();
    if (start_intersection_id > this->index or stop_intersection_id > this->index )
        throw std::overflow_error("Trying to connect a intersection that does not exist.");
    this->connect_road_start(start_intersection_id, start_direction, new_id, road_pool);
    this->connect_road_stop(stop_intersection_id, stop_direction, new_id, road_pool);
    (*this)[start_intersection_id].intersection[start_direction] = stop_intersection_id;
    (*this)[stop_intersection_id].intersection[stop_direction] = start_intersection_id;


    return new_id;
}

std::vector<int> IntersectionPool::generate_path() {
    int STEPS = 3;

    int current_intersection_id = rand() % this->index;
    Intersection cur_intersection = (*this)[current_intersection_id];
    std::vector<int> path = {current_intersection_id};
    for (int i=0; i<STEPS; i++) {
        std::vector<int> options;

        for (int j=0; j<4; j++) {
            int next_intersection = cur_intersection.intersection[j*2 + 1];
            if (next_intersection != -1)
                options.push_back(j*2 + 1);
        }

        int choice = options[rand() % options.size()];
        path.push_back(cur_intersection.road[choice]);
        current_intersection_id = cur_intersection.intersection[choice];
        cur_intersection = (*this)[current_intersection_id];
    }
    return path;
}
