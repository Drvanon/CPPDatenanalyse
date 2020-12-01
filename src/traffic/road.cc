#include "road.h"

RoadPool::RoadPool(int size): Pool<Road>(size) {
    this->index = 0;
}


void RoadPool::new_road(float start_x, float start_y, float stop_x, float stop_y) {
    Road new_road;
    new_road.id = this->index;

    Eigen::Vector2f start;
    start << start_x, start_y;
    Eigen::Vector2f stop;
    stop << stop_x, stop_y;

    new_road.start = start;
    new_road.stop = stop;

    this->pool[this->index] = new_road;
    this->index++;
}

Road RoadPool::get_road(int id) {
    return this->pool[id];
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

