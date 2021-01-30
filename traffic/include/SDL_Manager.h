#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <SDL2/SDL_ttf.h>

class SDL_Manager {
    private:
        TTF_Font* font;
        void load_font();
    public:
        SDL_Manager();
        ~SDL_Manager();
};

#endif
