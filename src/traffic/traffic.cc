#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "traffic.h"
#include "pool.h"
#include "car.h"

void init_pool(Pool<Car>& car_pool) {
    for (int i=0;i<car_pool.size;i++) {
        null_car(car_pool.pool[i]);
    }

    Car* car1 = &car_pool.pool[0];
    car1->pos_x = 200;
    car1->pos_y = 200;
    car1->vel_x = 20;
}

int main () {
    Pool<Car> car_pool = Pool<Car>(2);
    init_pool(car_pool);

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

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                running = false;
                break;
            }
        }

        float dT = (current - lastupdate) / 1000.0;
        car_physics(car_pool, dT);
        display_cars(car_pool, rend);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
	lastupdate = current;
    }

    return 0;
}
