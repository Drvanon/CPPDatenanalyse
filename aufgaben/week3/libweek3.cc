#include "week3.h"
#include <algorithm>
#include <cmath>
#include <iostream>

int QuadraticSum::operator() (std::vector<int> input) {
    int sum = 0;

    // In my opinion this is much more readable.
    for (int x: input)
        sum += x * x;

    return sum;
}

template <typename NumericType>
double QuadraticSum::operator() (std::vector<NumericType> input) {
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
    int sum = 0;

    for_each(input.begin(), input.end(), [&sum] (const NumericType& n) { sum += n * n; });
    return sum;
}

std::vector<int> random_squared() {
    // Initialize with 25 zeros
    std::vector<int> vec(25, 0);

    for (auto it = vec.begin(); it != vec.end(); ++it)
        *it = pow(std::rand() % 100, 2);

    std::sort(vec.begin(), vec.end());

    return vec;
}

template double QuadraticSum::operator()<float>(std::vector<float>);
template double QuadraticSum::operator()<double>(std::vector<double>);
