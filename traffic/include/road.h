#ifndef ROAD_H
#define ROAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Eigen/Dense>

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
        Eigen::Vector2f get_display_position(Eigen::Vector2f pos);
};

#endif
