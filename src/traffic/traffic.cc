#include <iostream>

#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "pool.h"
#include "car.h"
#include "road.h"
#include "intersection.h"

enum SIM_STATE {
    RUNNING,
    PAUSED,
    STOPPING
};

IntersectionPool init_intersectionpool() {
    IntersectionPool int_pool = IntersectionPool(7);

    int_pool.new_intersection(200, 100);
    int_pool.new_intersection(100, 200);
    int_pool.new_intersection(300, 200);
    int_pool.new_intersection(200, 300);
    int_pool.new_intersection(200, 400);
    int_pool.new_intersection(200, 200);
    int_pool.new_intersection(300, 100);
    return int_pool;
}

RoadPool init_roadpool(IntersectionPool& int_pool) {
    RoadPool road_pool = RoadPool(20);

    int_pool.new_road_between_intersections(0, 5, BOTTOM_OUT, TOP_IN, road_pool);
    int_pool.new_road_between_intersections(5, 0, TOP_OUT, BOTTOM_IN, road_pool);
    int_pool.new_road_between_intersections(6, 0, LEFT_OUT, RIGHT_IN, road_pool);
    int_pool.new_road_between_intersections(0, 6, RIGHT_OUT, LEFT_IN, road_pool);

    int_pool.new_road_between_intersections(1, 5, RIGHT_OUT, LEFT_IN, road_pool);
    int_pool.new_road_between_intersections(5, 1, LEFT_OUT, RIGHT_IN, road_pool);

    int_pool.new_road_between_intersections(2, 5, LEFT_OUT, RIGHT_IN, road_pool);
    int_pool.new_road_between_intersections(5, 2, RIGHT_OUT, LEFT_IN, road_pool);
    int_pool.new_road_between_intersections(2, 6, TOP_OUT, BOTTOM_IN, road_pool);
    int_pool.new_road_between_intersections(6, 2, BOTTOM_OUT, TOP_IN, road_pool);

    int_pool.new_road_between_intersections(3, 5, TOP_OUT, BOTTOM_IN, road_pool);
    int_pool.new_road_between_intersections(5, 3, BOTTOM_OUT, TOP_IN, road_pool);

    int_pool.new_road_between_intersections(3, 4, BOTTOM_OUT, TOP_IN, road_pool);
    int_pool.new_road_between_intersections(4, 3, TOP_OUT, BOTTOM_IN, road_pool);

    return road_pool;
}

CarPool init_carpool(RoadPool& road_pool, IntersectionPool& int_pool) {
    CarPool car_pool = CarPool(2);
    for (int i=0; i<10; i++) {
        car_pool.new_path(int_pool.generate_path(4));
    }

    car_pool.new_car_on_path(0, road_pool);
    car_pool.new_car_on_path(1, road_pool);

    car_pool[0].pos += Eigen::Vector2f(20, 20);
    car_pool[0].vel += Eigen::Vector2f(20, 20);
    car_pool[1].pos += Eigen::Vector2f(20, 20);
    car_pool[1].vel += Eigen::Vector2f(20, 20);
    return car_pool;
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
    IntersectionPool int_pool = init_intersectionpool();
    RoadPool road_pool = init_roadpool(int_pool);
    CarPool car_pool = init_carpool(road_pool, int_pool);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(
        "Traffic Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600, 650, 0
    );
    SDL_UpdateWindowSurface(window);
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Uint32 lastupdate = SDL_GetTicks();
    SIM_STATE state = RUNNING;
    while (state == RUNNING || state == PAUSED) {
        state = handle_events(state);
    	Uint32 current = SDL_GetTicks();
        float dT = (current - lastupdate) / 1000.0;
	lastupdate = current;

        car_pool.behaviour(road_pool);
        if (state == RUNNING) car_pool.physics(dT);

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        int_pool.display(rend);
        road_pool.display(rend);
        car_pool.display(rend);

        SDL_RenderPresent(rend);
    }

    return 0;
}
