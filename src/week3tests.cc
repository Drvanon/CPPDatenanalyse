#define CATCH_CONFIG_MAIN
#include "week3.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
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

template<typename T>
std::string str(T begin, T end)
{
    std::stringstream ss;
    bool first = true;
    for (; begin != end; begin++)
    {
        if (!first)
            ss << ", ";
        ss << *begin;
        first = false;
    }
    return ss.str();
}

TEST_CASE("Random numbers should be sorted and squared") {
    // Seed random
    srand(time(NULL));

    SECTION("Output vector should be between 0 and 10000 (that is 100 squared)") {
        for (int r: random_squared()) {
            REQUIRE(( 0 <= r && r < 10000 ));
        }
    }

    SECTION("Ouput vector should have 25 entries") {
        REQUIRE(random_squared().size() == 25);
    }

    SECTION("Show output of vector to manually check for randomness") {
        std::vector<int> rands[3] = {random_squared(), random_squared(), random_squared()};
        std::cout << "Does this look random to you?" << std::endl;
        for (int i=0; i<3; i++)
            std::cout << str(rands[i].begin(), rands[i].end()) << std::endl;
    }

    SECTION("Output vector needs to be sorted") {
        std::vector<int> rand = random_squared();
        for (int i=0; i<24; i++)
            REQUIRE(rand[i] <= rand[i + 1]);
    }
}
