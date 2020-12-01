#ifndef WEEK2_H
#define WEEK2_H

#include <vector>

class QuadraticSum {
    public:
        int operator() (std::vector<int> x);
        template <typename NumericType> double operator() (std::vector<NumericType> x);
};

std::vector<int> random_squared();

#endif
