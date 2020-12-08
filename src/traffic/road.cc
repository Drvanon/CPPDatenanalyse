#include <stdexcept>
#include "road.h"

RoadPool::RoadPool(int size): Pool<Road>(size) {
    this->index = 0;
}

int RoadPool::new_road() {
    Road new_road;
    new_road.id = this->index;

    this->pool[new_road.id] = new_road;
    this->index++;
    return new_road.id;
}

int RoadPool::new_road(float start_x, float start_y, float stop_x, float stop_y) {
    Road new_road;
    new_road.id = this->index;

    new_road.start = Eigen::Vector2f(start_x, start_y);
    new_road.stop = Eigen::Vector2f(stop_x, stop_y);

    this->pool[this->index] = new_road;
    this->index++;
    return new_road.id;
}

Road RoadPool::get_road(int id) {
    return this->pool[id];
}

void RoadPool::set_road_start(int id, Eigen::Vector2f pos) {
    this->pool[id].start = pos;
}

void RoadPool::set_road_stop(int id, Eigen::Vector2f pos) {
    this->pool[id].stop = pos;
}

void RoadPool::display(SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    for (int i=0;i < this->size; i++) {
        Road road = this->pool[i];
        SDL_RenderDrawLine(rend,
                           road.start(0), road.start(1),
                           road.stop(0), road.stop(1));
    }
}

