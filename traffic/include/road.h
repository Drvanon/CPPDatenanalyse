#ifndef ROAD_H
#define ROAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Road {
    private:
        SDL_Texture* texture;
        SDL_Renderer* rend;
        int repeats;
        void fill_texture();
    public:
        int length;
        int lanes;
        Road(int lanes, SDL_Renderer* rend, SDL_Texture* texture);
        ~Road();
        void display(SDL_Renderer* rend);
};

#endif
