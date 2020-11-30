#define CATCH_CONFIG_MAIN
#include "week3.h"
#include <vector>
#include <cmath>
#include <catch2/catch.hpp>


TEST_CASE("Functor that raises to the second power and sums.", "[functor]") {
    SECTION("Standard case") {
        std::vector<int> input {71, 1, 19, 12, 66, 23, 92};
        int expected_output = 18896;
        auto qs = QuadraticSum();
        REQUIRE(qs(input) == expected_output);
    }

    SECTION("General case") {
        std::vector<float> input {45, 51.2, 312.145, 68.9};
        double expected_output = 106828.151025;
        float allowed_error_range = 0.00001;

        auto qs = QuadraticSum();
        REQUIRE( abs((qs(input) - expected_output)/expected_output) < 1 + allowed_error_range );
    }
}

