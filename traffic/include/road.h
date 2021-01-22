#ifndef ROAD_H
#define ROAD_H

#include <SDL2/SDL.h>

class Road {
    private:
        int repeats;
    public:
        int length;
        int lanes;
        Road(int lanes);
        void display(SDL_Renderer* renderer);
};

#endif
