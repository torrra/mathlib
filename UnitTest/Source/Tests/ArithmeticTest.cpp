#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>

#include "libmath/Arithmetic.h"

TEST_CASE("Arithmetic", "[all]")
{
    SECTION("Rounding")
    {
        constexpr float   roundUp = 13.7f, roundDown = 0.2f, 
                          pointFive = 3.5f, pointZero = 2.0f;

        // Testing with a number with a decimal part above .5
        CHECK(mth::floor(roundUp) == std::floor(roundUp));
        CHECK(mth::round(roundUp) == std::round(roundUp));
        CHECK(mth::ceil(roundUp) == std::ceil(roundUp));

        // Testing with a decimal part below .5
        CHECK(mth::floor(roundDown) == std::floor(roundDown));
        CHECK(mth::round(roundDown) == std::round(roundDown));
        CHECK(mth::ceil(roundDown) == std::ceil(roundDown));

        // Testing with a decimal part equal to .5
        CHECK(mth::floor(pointFive) == std::floor(pointFive));
        CHECK(mth::round(pointFive) == std::round(pointFive));
        CHECK(mth::ceil(pointFive) == std::ceil(pointFive));

        // Testing with a decimal part equal to 0
        CHECK(mth::floor(pointZero) == std::floor(pointZero));
        CHECK(mth::round(pointZero) == std::round(pointZero));
        CHECK(mth::ceil(pointZero) == std::ceil(pointZero));
        
    }


    SECTION("Comparisons")
    {
        constexpr float   big = 1555.4f, small = 3.77777f,
                          eq1 = 5.1f, eq2 = 5.10001f;      
    
        // Very close numbers should be treated as equal
        CHECK(mth::almostEqual(eq1, eq1));
        CHECK(mth::almostEqual(eq1, eq2));

        // Vastly different numbers should NOT be treated as equal
        CHECK_FALSE(mth::almostEqual(big, small));

        // Similar numbers can be considered different with a small anough precision
        CHECK_FALSE(mth::almostEqual(eq1, eq2, 0.000001f));

        // Get smallest and largest numbers
        CHECK(mth::min(big, small) == std::min(big, small));
        CHECK(mth::max(big, small) == std::max(big, small));

        // Absolute values
        CHECK(mth::absolute(-small) == small);
        CHECK(mth::absolute(small) == small);

        // Integer absolute values
        CHECK(mth::absolute(1) == 1);
        CHECK(mth::absolute(-1) == 1);

    }


    SECTION("Multiplication/Division")
    {
       constexpr float      big = 1555.4f, small = 3.f,
                            veryBig = 99999.f, verySmall = 0.4f;

       // TODO: Test wrap 

       CHECK(mth::clamp(veryBig, small, big) == std::clamp(veryBig, small, big));
       CHECK(mth::clamp(verySmall, small, big) == std::clamp(verySmall, small, big));

       CHECK(mth::pow(small, 10u) == std::pow(small, 10.f));

       CHECK(mth::factorial(5u) == 120u);
       CHECK(mth::factorial(0u) == 1u);
       CHECK(mth::factorial(1u) == 1u);
       CHECK(mth::factorial(2u) == 2u);
    }
}

