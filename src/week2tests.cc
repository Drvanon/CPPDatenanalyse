#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>
#include "week2.h"

TEST_CASE( "Summing with complex numbers", "[complex]" ) {
    SECTION("Summing two complex numbers") {
        REQUIRE(( Complex() + Complex() == Complex() ));
        REQUIRE(( Complex(1, 1) + Complex() == Complex(1, 1) ));
        REQUIRE(( Complex(1, 1) + Complex(1, 2) == Complex(2, 3) ));
    }

    SECTION("Summing a complex number and a real number") {
        REQUIRE(( Complex() + 1 == Complex(1, 0) ));
        REQUIRE(( Complex(1, 1) + 1 == Complex(2, 1) ));
    }
}

TEST_CASE( "Multiplying complex numbers", "[complex]" ) {
    SECTION("Multiplying two complex numbers") {
        REQUIRE(( Complex() * Complex(2, 2) == Complex() ));
        REQUIRE(( Complex(1, 0) * Complex(2, 2) == Complex(2, 2) ));
        REQUIRE(( Complex(0, 1) * Complex(2, 3) == Complex(-3, 2) ));
        REQUIRE(( Complex(1, 1) * Complex(2, 2) == Complex(0, 4) ));
    }

    SECTION("Multiplying a complex number with a real number") {
        REQUIRE(( Complex(0, 0) * 2 == Complex(0, 0) ));
        REQUIRE(( Complex(1, 0) * 2 == Complex(2, 0) ));
        REQUIRE(( Complex(0, 1) * 2 == Complex(0, 2) ));
        REQUIRE(( Complex(1, 1) * 2 == Complex(2, 2) ));
    }
}

TEST_CASE( "Length of a complex number should be defined as the Euclidian length.", "[complex]" ) {
    REQUIRE( Complex(0, 0).length() == 0 );
    REQUIRE( Complex(3, 0).length() == 3 );
    REQUIRE( Complex(0, 4).length() == 4 );
    REQUIRE( Complex(3, 4).length() == 5 );
}

TEST_CASE( "Complex numbers should be represent as a+ib", "[complex]") {
    REQUIRE( Complex().toString() == "0.000000+i0.000000" );
    REQUIRE( Complex(1, 2).toString() == "1.000000+i2.000000" );
}

TEST_CASE( "Complex numbers should allow components to be accessible", "[complex]" ) {
    Complex c = Complex(3, 4);
    REQUIRE( c.getReal() == 3 );
    REQUIRE( c.getImag() == 4 );
}

TEST_CASE( "Polynomials should be callable", "[polynomial]" ) {
    Polynomial p = Polynomial({1});
    std::vector<double> coefficients = {1};
;
    REQUIRE(p(1) == 1);
    REQUIRE(p(1) == p.evaluate(1) );
}

TEST_CASE( "Polynomials should behave like the mathematical equivalent", "[polynomial]" ) {
    Polynomial p = Polynomial({1, 1, 1, 1, 1, 1, 1});
    REQUIRE(p(0) == 1);
    REQUIRE(p(1) == 7);
}
