#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "pool.h"
#include "car.h"
#include "road.h"
#include "path.h"

RoadPool init_roadpool() {
    RoadPool road_pool = RoadPool(4);

    road_pool.new_road(190, 190, 300, 200);
    road_pool.new_road(300, 200, 300, 300);
    road_pool.new_road(300, 300, 250, 400);
    road_pool.new_road(300, 300, 100, 200);

    return road_pool;
}

PathPool init_pathpool() {
    PathPool path_pool = PathPool(6);
    path_pool.new_path(std::vector<int> {0, 1, 2});
    path_pool.new_path(std::vector<int> {0, 1, 3});
    return path_pool;
}


CarPool init_carpool(RoadPool road_pool, PathPool path_pool) {
    CarPool car_pool = CarPool(2);
    car_pool.new_car_on_path(0, road_pool, path_pool);
    car_pool.new_car_on_path(1, road_pool, path_pool);
    return car_pool;
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
    RoadPool road_pool = init_roadpool();
    PathPool path_pool = init_pathpool();
    CarPool car_pool = init_carpool(road_pool, path_pool);

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

        car_pool.behaviour(road_pool, path_pool);
        car_pool.physics(dT);

        road_pool.display(rend);
        car_pool.display(rend);

        SDL_RenderPresent(rend);
	lastupdate = current;
    }

    return 0;
}
