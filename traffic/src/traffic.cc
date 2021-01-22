#include <iostream>

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

int CAR_CREATION_PERIOD = 15000;

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 650;

enum SIM_STATE {
    RUNNING,
    PAUSED,
    STOPPING
};

CarPool init_carpool(Road road) {
    CarPool car_pool = CarPool(200);
    return car_pool;
}

Uint32 create_car(Uint32 last_car_creation, CarPool& car_pool, Road road) {
    if (SDL_GetTicks() - last_car_creation > CAR_CREATION_PERIOD) {
        // Create path
        // car_pool.new_car_on_path(path_index, road_pool);
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

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("assets/coolvetica rg.ttf", 24);
    if (font == NULL) {
        std::cout << "Font not found: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Window* window = SDL_CreateWindow(
        "Traffic Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0
    );
    SDL_UpdateWindowSurface(window);
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Road road = Road(3);
    CarPool car_pool = init_carpool(road);

    Uint32 lastupdate = SDL_GetTicks();
    Uint32 last_car_creation = -CAR_CREATION_PERIOD;
    SIM_STATE state = RUNNING;
    while (state == RUNNING || state == PAUSED) {
        state = handle_events(state);
    	Uint32 current = SDL_GetTicks();
        float dT = (current - lastupdate) / 1000.0;
	lastupdate = current;

        if (state == RUNNING) {
            last_car_creation = create_car(last_car_creation, car_pool, road);
            car_pool.physics(dT);
            car_pool.behaviour(road);
        }

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        car_pool.display(rend);
        road.display(rend);

        SDL_RenderPresent(rend);
    }

    return 0;
}
