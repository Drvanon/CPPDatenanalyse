#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <SDL2/SDL.h>

class SDL_Manager {
    private:
        SDL_Window* window;
        void load_font();
    public:
        int w, h;
        SDL_Renderer* rend;
        SDL_Texture* road_texture;
        void clear();
        SDL_Manager();
        void draw_to_screen();
        void draw_to_road_texture();
        void draw_road();
        void present();
        ~SDL_Manager();
};

#endif
