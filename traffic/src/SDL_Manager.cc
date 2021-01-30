#include <iostream>
#include "SDL_Manager.h"

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 650;

SDL_Manager::SDL_Manager () {
    this->w = SCREEN_WIDTH;
    this->h = SCREEN_HEIGHT;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
         exit(EXIT_FAILURE);
    }
    this->window = SDL_CreateWindow(
        "Traffic Simulation",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (this->window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open this->window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    this->rend = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    this->road_texture = SDL_CreateTexture(
        this->rend,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH, SCREEN_HEIGHT
    );
}

void SDL_Manager::draw_to_screen() {
    if (SDL_SetRenderTarget(this->rend, NULL) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set render target: %s", SDL_GetError());
    }
}

void SDL_Manager::draw_to_road_texture() {
    if (SDL_SetRenderTarget(this->rend, this->road_texture) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set render target to road texture: %s", SDL_GetError());
    }
}

void SDL_Manager::draw_road() {
    this->draw_to_screen();

    if (SDL_RenderCopy(this->rend, this->road_texture, NULL, NULL) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not copy the texture to the screen: %s", SDL_GetError());
    };
}

void SDL_Manager::present() {
    SDL_RenderPresent(this->rend);
}

void SDL_Manager::clear() {
    SDL_SetRenderDrawColor(this->rend, 0, 0, 0, 255);
    SDL_RenderClear(this->rend);
}

SDL_Manager::~SDL_Manager() {
    std::cout << "Clearing up SDL." << std::endl;
    SDL_DestroyRenderer(this->rend);
    SDL_DestroyTexture(this->road_texture);
}
