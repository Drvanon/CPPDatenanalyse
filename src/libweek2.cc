#include "week2.h"
#include <iostream>
#include <cmath>

Complex::Complex() {
    this->real = 0;
    this->imag = 0;
}

template <typename NumericType>
Complex::Complex(NumericType real, NumericType imag) {
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
    this->real = real;
    this->imag = imag;
}

template <typename NumericType> Complex Complex::multiply(NumericType multiplier) {
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
    return Complex(multiplier * this->real, multiplier * this->imag);
}

template <typename NumericType> Complex Complex::add(NumericType adder) {
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
    return Complex(adder + this->real, this->imag);
}

Complex Complex::add(Complex c) {
    return Complex(c.real + this->real, c.imag + this->imag);
}

Complex Complex::multiply(Complex c) {
    double real = c.real * this->real - c.imag * this->imag;
    double imag = c.real * this->imag + c.imag * this->real;
    return Complex(real, imag);
}

std::string Complex::toString() const {
    std::string real_string = std::to_string(this->real);
    std::string imag_string = std::to_string(this->imag);
    return real_string + "+i" + imag_string;
}

double Complex::length() {
   return sqrt(pow(this->real, 2) + pow(this->imag, 2));
}

std::ostream& operator<<(std::ostream& output, const Complex &C) {
    output << C.toString();
    return output;
}

template <typename NumericType>
Complex Complex::operator+(NumericType n) {
    return this->add(n);
}

template <typename NumericType>
Complex Complex::operator*(NumericType n) {
    return this->multiply(n);
}

template <typename NumericType>
bool Complex::operator==(NumericType n) {
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
    return (this->real == n) && (this->imag == 0);
}

bool Complex::operator==(Complex c) {
    return (this->real == c.real) && (this->imag == c.imag);
}

Complex Complex::operator+(Complex c) {
    return this->add(c);
}

Complex Complex::operator*(Complex c) {
    return this->multiply(c);
}

template Complex Complex::operator+<int>(int);
template Complex Complex::operator+<float>(float);
template Complex Complex::operator+<double>(double);

template Complex Complex::operator*<int>(int);
template Complex Complex::operator*<float>(float);
template Complex Complex::operator*<double>(double);

template Complex Complex::add<int>(int);
template Complex Complex::add<float>(float);
template Complex Complex::add<double>(double);

template Complex Complex::multiply<int>(int);
template Complex Complex::multiply<float>(float);
template Complex Complex::multiply<double>(double);

template Complex::Complex<int>(int, int);
template Complex::Complex<float>(float, float);
template Complex::Complex<double>(double, double);
