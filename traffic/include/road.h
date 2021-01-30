#ifndef ROAD_H
#define ROAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Eigen/Dense>

#include "SDL_Manager.h"

class Road {
    private:
        int repeats;
        void fill_texture();
        SDL_Manager* sdl;
    public:
        int length;
        int lanes;
        Road(int lanes, SDL_Manager* sdl);
        Eigen::Vector2f get_display_position(Eigen::Vector2f pos);
};

#endif
