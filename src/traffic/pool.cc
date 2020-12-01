#include "traffic.h"

template <typename T>
Pool<T>::Pool(int size): size(size) {
    this->pool = new T[size];
}

template Pool<Car>::Pool(int size);
