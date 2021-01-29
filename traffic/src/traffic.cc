#include <iostream>
#include <random>

#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "car.h"
#include "traffic.h"
#include "pool.h"
#include "road.h"

typedef Eigen::Vector2f vec2f;

int CAR_CREATION_PERIOD = 5000;

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 650;

enum SIM_STATE {
    RUNNING,
    PAUSED,
    STOPPING
};

CarPool init_carpool(Road* road) {
    CarPool car_pool = CarPool(200);
    return car_pool;
}

Uint32 create_car(Uint32 last_car_creation, CarPool& car_pool) {
    if (SDL_GetTicks() - last_car_creation > CAR_CREATION_PERIOD) {
        // Create path
        car_pool.new_car(vec2f(8500, 0));
        return SDL_GetTicks();
    }
    return last_car_creation;
}

SIM_STATE handle_events(SIM_STATE cur_state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return STOPPING;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDLK_KP_SPACE:
                    case SDL_SCANCODE_SPACE:
                        if (cur_state == RUNNING) {
                            return PAUSED;
                        } else {
                        }
                        return RUNNING;
                        break;
                }
                break;
            }
    }
    return cur_state;
}

int main () {
    srand(time(NULL));
    SDL_Window* window;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError()); }
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("assets/coolvetica rg.ttf", 24);
    if (font == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font not found: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        "Traffic Simulation",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_Texture* road_texture = SDL_CreateTexture(
        rend,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH, SCREEN_HEIGHT
    );

    Road road = Road(3, rend, road_texture);
    CarPool car_pool = init_carpool(&road);

    Uint32 lastupdate = SDL_GetTicks();
    // GetTicks gives miliseconds since start of program, so we want
    // to set the last_car_creation way back so one immediately gets created.
    Uint32 last_car_creation = -CAR_CREATION_PERIOD;
    SIM_STATE state = RUNNING;
    while (state == RUNNING || state == PAUSED) {
        state = handle_events(state);
    	Uint32 current = SDL_GetTicks();
        float dT = (current - lastupdate) / 1000.0;
	lastupdate = current;

        if (state == RUNNING) {
            last_car_creation = create_car(last_car_creation, car_pool);
            car_pool.physics(dT);
            car_pool.behaviour(&road);
        }

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        road.display(rend);
        car_pool.display(rend, &road);

        SDL_RenderPresent(rend);
    }

    return 0;
}
