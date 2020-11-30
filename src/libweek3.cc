#include "week3.h"
#include <algorithm>

int QuadraticSum::operator() (std::vector<int> input) {
    int sum = 0;

    // In my opinion this is much more readable.
    for (int x: input) {
        sum += x * x;
    }

    return sum;
}

template <typename NumericType>
double QuadraticSum::operator() (std::vector<NumericType> input) {
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
    int sum = 0;

    for_each(input.begin(), input.end(), [&sum] (const NumericType& n) { sum += n * n; });
    return sum;
}

template double QuadraticSum::operator()<float>(std::vector<float>);
template double QuadraticSum::operator()<double>(std::vector<double>);
