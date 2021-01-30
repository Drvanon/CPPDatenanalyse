#include "SDL_Manager.h"

SDL_Manager::SDL_Manager () {
}

void SDL_Manager::load_font() {
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("assets/coolvetica rg.ttf", 24);
    if (font == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font not found: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return font;
}

