#ifndef H_WEEK2
#define H_WEEK2

#include <type_traits>
#include <iostream>
#include <string>
#include <vector>

class Complex {
    private:
        double real;
        double imag;
    public:
        Complex();
        template <typename NumericType> Complex(NumericType real, NumericType imag);
        template <typename NumericType> Complex add(NumericType adder);
        Complex add(Complex c);
        template <typename NumericType> Complex multiply(NumericType multiplier);
        Complex multiply(Complex multiplier);
        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& output, const Complex &C);
        template <typename NumericType> Complex operator+(NumericType n);
        template <typename NumericType> Complex operator*(NumericType n);
        template <typename NumericType> bool operator==(NumericType n);
        bool operator==(Complex c);
        Complex operator+(Complex c);
        Complex operator*(Complex c);
        double length();
};

class Polynomial {
    private:
        std::vector<double> coefficients;
    public:
        Polynomial(std::vector<double> coefficients);
        template <typename NumericType> double operator() (NumericType x);
        template <typename NumericType> double evaluate(NumericType x);
};

#endif
