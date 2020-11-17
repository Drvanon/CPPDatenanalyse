#include <iostream>
#include "week2.h"

int main() {
    Complex c = Complex(1, 1);
    Complex c2 = Complex(1, 1);
    bool val = c == c2;
    std::cout << val << std::endl;
}
