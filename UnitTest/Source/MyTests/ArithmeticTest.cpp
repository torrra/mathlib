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
        CHECK(mth::Floor(roundUp) == std::floor(roundUp));
        CHECK(mth::Round(roundUp) == std::round(roundUp));
        CHECK(mth::Ceil(roundUp) == std::ceil(roundUp));

        // Testing with a decimal part below .5
        CHECK(mth::Floor(roundDown) == std::floor(roundDown));
        CHECK(mth::Round(roundDown) == std::round(roundDown));
        CHECK(mth::Ceil(roundDown) == std::ceil(roundDown));

        // Testing with a decimal part equal to .5
        CHECK(mth::Floor(pointFive) == std::floor(pointFive));
        CHECK(mth::Round(pointFive) == std::round(pointFive));
        CHECK(mth::Ceil(pointFive) == std::ceil(pointFive));

        // Testing with a decimal part equal to 0
        CHECK(mth::Floor(pointZero) == std::floor(pointZero));
        CHECK(mth::Round(pointZero) == std::round(pointZero));
        CHECK(mth::Ceil(pointZero) == std::ceil(pointZero));

    }


    SECTION("Comparisons")
    {
        constexpr float   big = 1555.4f, small = 3.77777f,
                          eq1 = 5.1f, eq2 = 5.10001f;

        // Very close numbers should be treated as equal
        CHECK(mth::AlmostEqual(eq1, eq1));
        CHECK(mth::AlmostEqual(eq1, eq2));

        // Vastly different numbers should NOT be treated as equal
        CHECK_FALSE(mth::AlmostEqual(big, small));

        // Similar numbers can be considered different with a small enough precision
        CHECK_FALSE(mth::AlmostEqual(eq1, eq2, 0.000001f));

        // Get smallest and largest numbers
        CHECK(mth::Min(big, small) == std::min(big, small));
        CHECK(mth::Max(big, small) == std::max(big, small));

        // Absolute values
        CHECK(mth::Absolute(-small) == small);
        CHECK(mth::Absolute(small) == small);

        // Integer absolute values
        CHECK(mth::Absolute(1) == 1);
        CHECK(mth::Absolute(-1) == 1);

    }


    SECTION("Multiplication/Division")
    {
       constexpr float      big = 1555.4f, small = 3.f,
                            veryBig = 99999.f, verySmall = 0.4f;

       CHECK(mth::Clamp(veryBig, small, big) == std::clamp(veryBig, small, big));
       CHECK(mth::Clamp(verySmall, small, big) == std::clamp(verySmall, small, big));

       CHECK(mth::Pow(small, 10u) == std::pow(small, 10.f));

       CHECK(mth::Factorial(5u) == 120u);
       CHECK(mth::Factorial(0u) == 1u);
       CHECK(mth::Factorial(1u) == 1u);
       CHECK(mth::Factorial(2u) == 2u);
    }
}

