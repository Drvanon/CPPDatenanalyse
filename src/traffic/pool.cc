#include "pool.h"
#include "car.h"
#include "road.h"
#include "path.h"
#include "intersection.h"

template <typename T>
Pool<T>::Pool(int size): size(size) {
    this->pool = new T[size];
    this->index = 0;
}

template Pool<Car>::Pool(int size);
template Pool<Road>::Pool(int size);
template Pool<PathPiece>::Pool(int size);
template Pool<Intersection>::Pool(int size);
