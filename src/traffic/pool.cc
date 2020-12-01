#include "pool.h"
#include "car.h"
#include "road.h"

template <typename T>
Pool<T>::Pool(int size): size(size) {
    this->pool = new T[size];
    this->index = 0;
}

template Pool<Car>::Pool(int size);
template Pool<Road>::Pool(int size);
