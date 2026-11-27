#include <cmath>
#include <algorithm>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "math/Arithmetic.hpp"

TEST_CASE("Arithmetic", "[all]")
{
    SECTION("Rounding")
    {
        constexpr float   roundUp = 13.7f, roundDown = 0.2f,
                          pointFive = 3.5f, pointZero = 2.0f;

        // Testing with a number with a decimal part above .5
        CHECK(math::Floor(roundUp) == std::floor(roundUp));
        CHECK(math::Round(roundUp) == std::round(roundUp));
        CHECK(math::Ceil(roundUp) == std::ceil(roundUp));

        // Testing with a decimal part below .5
        CHECK(math::Floor(roundDown) == std::floor(roundDown));
        CHECK(math::Round(roundDown) == std::round(roundDown));
        CHECK(math::Ceil(roundDown) == std::ceil(roundDown));

        // Testing with a decimal part equal to .5
        CHECK(math::Floor(pointFive) == std::floor(pointFive));
        CHECK(math::Round(pointFive) == std::round(pointFive));
        CHECK(math::Ceil(pointFive) == std::ceil(pointFive));

        // Testing with a decimal part equal to 0
        CHECK(math::Floor(pointZero) == std::floor(pointZero));
        CHECK(math::Round(pointZero) == std::round(pointZero));
        CHECK(math::Ceil(pointZero) == std::ceil(pointZero));

    }


    SECTION("Comparisons")
    {
        constexpr float   big = 1555.4f, small = 3.77777f,
                          eq1 = 5.1f, eq2 = 5.10001f;

        // Very close numbers should be treated as equal
        CHECK(math::AlmostEqual(eq1, eq1));
        CHECK(math::AlmostEqual(eq1, eq2));

        // Vastly different numbers should NOT be treated as equal
        CHECK_FALSE(math::AlmostEqual(big, small));

        // Similar numbers can be considered different with a small enough precision
        CHECK_FALSE(math::AlmostEqual(eq1, eq2, 0.000001f));

        // Get smallest and largest numbers
        CHECK(math::Min(big, small) == std::min(big, small));
        CHECK(math::Max(big, small) == std::max(big, small));

        // Absolute values
        CHECK(math::Absolute(-small) == small);
        CHECK(math::Absolute(small) == small);

        // Integer absolute values
        CHECK(math::Absolute(1) == 1);
        CHECK(math::Absolute(-1) == 1);

    }


    SECTION("Multiplication/Division")
    {
       constexpr float      big = 1555.4f, small = 3.f,
                            veryBig = 99999.f, verySmall = 0.4f;

       CHECK(math::Clamp(veryBig, small, big) == std::clamp(veryBig, small, big));
       CHECK(math::Clamp(verySmall, small, big) == std::clamp(verySmall, small, big));

       CHECK(math::Pow(small, 10u) == std::pow(small, 10.f));

       CHECK(math::Factorial(5u) == 120u);
       CHECK(math::Factorial(0u) == 1u);
       CHECK(math::Factorial(1u) == 1u);
       CHECK(math::Factorial(2u) == 2u);
    }
}

