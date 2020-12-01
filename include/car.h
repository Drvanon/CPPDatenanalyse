#ifndef CAR_H
#define CAR_H

void car_physics(Pool<Car>& car_pool, float time_frac);
void display_cars(Pool<Car>& car_pool);
void display_cars(Pool<Car>& car_pool, SDL_Renderer* renderer);
void null_car(Car& car);

#endif
