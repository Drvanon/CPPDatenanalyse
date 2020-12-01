#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "pool.h"
#include "car.h"
#include "road.h"

CarPool init_carpool() {
    CarPool car_pool = CarPool(2);
    car_pool.new_car(1, 1);
    car_pool.new_car(200, 200);
    return car_pool;
}

RoadPool init_roadpool() {
    RoadPool road_pool = RoadPool(3);

    road_pool.new_road(30, 30, 30, 200);
    road_pool.new_road(150, 400, 300, 300);
    road_pool.new_road(10, 10, 250, 300);

    return road_pool;
}

bool handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            return false;
            break;
        }
    }
    return true;
}

int main () {
    CarPool car_pool = init_carpool();
    RoadPool road_pool = init_roadpool();

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* window = SDL_CreateWindow("GAME",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          400, 500, 0);
    SDL_Surface* screenSurface = NULL;
    screenSurface = SDL_GetWindowSurface( window );

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(window);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);

    Uint32 lastupdate = SDL_GetTicks();

    bool running = true;
    while (running) {
    	Uint32 current = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        running = handle_events();

        float dT = (current - lastupdate) / 1000.0;

        car_pool.physics(dT);

        car_pool.display(rend);
        road_pool.display(rend);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
	lastupdate = current;
    }

    return 0;
}
