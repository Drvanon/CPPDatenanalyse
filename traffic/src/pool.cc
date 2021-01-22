#include "pool.h"
#include "car.h"

#include <stdexcept>

template <typename T>
Pool<T>::Pool(int size): size(size) {
    this->pool = new T[size];
    this->index = 0;
}

template <typename T>
T& Pool<T>::operator[](int index) {
    if (index > this->index) throw std::overflow_error("Reached unset part of pool");
    if (index < 0) throw std::underflow_error("Negative index supplied");
    return this->pool[index];
}

template Pool<Car>::Pool(int size);
template Car& Pool<Car>::operator[](int index);
