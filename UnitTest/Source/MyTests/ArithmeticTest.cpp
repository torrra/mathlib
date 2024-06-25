#include <cmath>
#include <algorithm>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "libmath/Arithmetic.h"

TEST_CASE("Arithmetic", "[all]")
{
    SECTION("Rounding")
    {
        constexpr float   roundUp = 13.7f, roundDown = 0.2f,
                          pointFive = 3.5f, pointZero = 2.0f;

        // Testing with a number with a decimal part above .5
        CHECK(ion::math::Floor(roundUp) == std::floor(roundUp));
        CHECK(ion::math::Round(roundUp) == std::round(roundUp));
        CHECK(ion::math::Ceil(roundUp) == std::ceil(roundUp));

        // Testing with a decimal part below .5
        CHECK(ion::math::Floor(roundDown) == std::floor(roundDown));
        CHECK(ion::math::Round(roundDown) == std::round(roundDown));
        CHECK(ion::math::Ceil(roundDown) == std::ceil(roundDown));

        // Testing with a decimal part equal to .5
        CHECK(ion::math::Floor(pointFive) == std::floor(pointFive));
        CHECK(ion::math::Round(pointFive) == std::round(pointFive));
        CHECK(ion::math::Ceil(pointFive) == std::ceil(pointFive));

        // Testing with a decimal part equal to 0
        CHECK(ion::math::Floor(pointZero) == std::floor(pointZero));
        CHECK(ion::math::Round(pointZero) == std::round(pointZero));
        CHECK(ion::math::Ceil(pointZero) == std::ceil(pointZero));

    }


    SECTION("Comparisons")
    {
        constexpr float   big = 1555.4f, small = 3.77777f,
                          eq1 = 5.1f, eq2 = 5.10001f;

        // Very close numbers should be treated as equal
        CHECK(ion::math::AlmostEqual(eq1, eq1));
        CHECK(ion::math::AlmostEqual(eq1, eq2));

        // Vastly different numbers should NOT be treated as equal
        CHECK_FALSE(ion::math::AlmostEqual(big, small));

        // Similar numbers can be considered different with a small enough precision
        CHECK_FALSE(ion::math::AlmostEqual(eq1, eq2, 0.000001f));

        // Get smallest and largest numbers
        CHECK(ion::math::Min(big, small) == std::min(big, small));
        CHECK(ion::math::Max(big, small) == std::max(big, small));

        // Absolute values
        CHECK(ion::math::Absolute(-small) == small);
        CHECK(ion::math::Absolute(small) == small);

        // Integer absolute values
        CHECK(ion::math::Absolute(1) == 1);
        CHECK(ion::math::Absolute(-1) == 1);

    }


    SECTION("Multiplication/Division")
    {
       constexpr float      big = 1555.4f, small = 3.f,
                            veryBig = 99999.f, verySmall = 0.4f;

       CHECK(ion::math::Clamp(veryBig, small, big) == std::clamp(veryBig, small, big));
       CHECK(ion::math::Clamp(verySmall, small, big) == std::clamp(verySmall, small, big));

       CHECK(ion::math::Pow(small, 10u) == std::pow(small, 10.f));

       CHECK(ion::math::Factorial(5u) == 120u);
       CHECK(ion::math::Factorial(0u) == 1u);
       CHECK(ion::math::Factorial(1u) == 1u);
       CHECK(ion::math::Factorial(2u) == 2u);
    }
}

