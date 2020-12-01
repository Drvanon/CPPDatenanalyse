#ifndef CAR_H
#define CAR_H

#include <SDL2/SDL.h>
#include "pool.h"
#include "entities.h"

void car_physics(Pool<Car>& car_pool, float dT);
void display_cars(Pool<Car>& car_pool);
void display_cars(Pool<Car>& car_pool, SDL_Renderer* renderer);
void null_car(Car& car);

#endif
