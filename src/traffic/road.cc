#include "road.h"

RoadPool::RoadPool(int size): Pool<Road>(size) {}

void RoadPool::new_road(float start_x, float start_y, float stop_x, float stop_y) {
    Road new_road;
    new_road.start_x = start_x;
    new_road.start_y = start_y;
    new_road.stop_x = stop_x;
    new_road.stop_y = stop_y;

    this->pool[this->index] = new_road;
    this->index++;
}

void RoadPool::display(SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    for (int i=0;i < this->size; i++) {
        Road road = this->pool[i];
        SDL_RenderDrawLine(rend,
                           road.start_x, road.start_y,
                           road.stop_x, road.stop_y);
    }
}

