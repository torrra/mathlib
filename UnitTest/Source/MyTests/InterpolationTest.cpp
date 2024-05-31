#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/norm.hpp>

#include "libmath/Interpolation.h"

TEST_CASE("Interpolation", "[all]")
{
	float	belowOneRatio = 0.7f, overOneRatio = 7.f, low = 5.f, high = 8.f;


	float	belowLerp = mth::Lerp(low, high, belowOneRatio);
	float	overLerp = mth::Lerp(low, high, overOneRatio);

	// Ratio below one
	CHECK(belowLerp == Catch::Approx(glm::lerp(low, high, belowOneRatio)));

	// Ratio over 1
	CHECK(overLerp == Catch::Approx(glm::lerp(low, high, overOneRatio)));


	// Inverse
	float	invBelow = mth::InverseLerp(belowLerp, low, high);
	float	invOver = mth::InverseLerp(overLerp, low, high);

	CHECK(invBelow == Catch::Approx(belowOneRatio));
	CHECK(invOver == Catch::Approx(overOneRatio));


	// Negative ratio
	float	negRatio = -0.1f, negOverOne = -5.f;

	float	negLerp = mth::Lerp(low, high, negRatio);
	float	negLerpOver = mth::Lerp(low, high, negOverOne);


	CHECK(negLerp == Catch::Approx(glm::lerp(low, high, negRatio)));
	CHECK(negLerpOver == Catch::Approx(glm::lerp(low, high, negOverOne)));

	// Get ratios back from lerped values
	float	invNeg = mth::InverseLerp(negLerp, low, high);
	float	invOverNeg = mth::InverseLerp(negLerpOver, low, high);


	CHECK(invNeg == Catch::Approx(negRatio));
	CHECK(invOverNeg == Catch::Approx(negOverOne));
}