#include "intersection.h"
#include <cmath>
#include "road.h"


IntersectionPool::IntersectionPool(int size): Pool(size) {
    this->index = 0;
}

int IntersectionPool::new_intersection(float pos_x, float pos_y) {
    Intersection new_intersection;
    new_intersection.pos = Eigen::Vector2f(pos_x, pos_y);
    new_intersection.id = this->index;
    for (int i=0;i < 8; i++) new_intersection.road[i] = -1;

    this->pool[this->index] = new_intersection;
    this->index++;

    return new_intersection.id;
}

float custom_round(float a) {
    return round(a);
}

Eigen::Vector2f IntersectionPool::get_connection_position(int intersection_id, int direction_id) {
    float INTERSECTION_RADIUS = 15;

    Intersection* intersection = &this->pool[intersection_id];
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
    for (int i=0; i<this->size; i++) {
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
        Intersection intersection = this->pool[i];
        SDL_Rect rect(intersection.pos(0), intersection.pos(1), 5, 5);

        for (int j=0; j<8; j++) {
            // if (intersection.road[j] == -1) continue;
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

int IntersectionPool::new_road_between_intersections(
        int intersection1_id, int intersection2_id,
        int direction_index_1, int direction_index_2,
        RoadPool road_pool
) {
    Intersection* intersection1 = &this->pool[intersection1_id];
    Intersection* intersection2 = &this->pool[intersection2_id];

    Road new_road;
    return new_road.id;
}
