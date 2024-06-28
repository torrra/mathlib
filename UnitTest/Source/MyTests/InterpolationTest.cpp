#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/norm.hpp>

#include "math/Interpolation.h"

TEST_CASE("Interpolation", "[all]")
{
	float	belowOneRatio = 0.7f, overOneRatio = 7.f, low = 5.f, high = 8.f;


	float	belowLerp = ion::math::Lerp(low, high, belowOneRatio);
	float	overLerp = ion::math::Lerp(low, high, overOneRatio);

	// Ratio below one
	CHECK(belowLerp == Catch::Approx(glm::lerp(low, high, belowOneRatio)));

	// Ratio over 1
	CHECK(overLerp == Catch::Approx(glm::lerp(low, high, overOneRatio)));


	// Inverse
	float	invBelow = ion::math::InverseLerp(belowLerp, low, high);
	float	invOver = ion::math::InverseLerp(overLerp, low, high);

	CHECK(invBelow == Catch::Approx(belowOneRatio));
	CHECK(invOver == Catch::Approx(overOneRatio));


	// Negative ratio
	float	negRatio = -0.1f, negOverOne = -5.f;

	float	negLerp = ion::math::Lerp(low, high, negRatio);
	float	negLerpOver = ion::math::Lerp(low, high, negOverOne);


	CHECK(negLerp == Catch::Approx(glm::lerp(low, high, negRatio)));
	CHECK(negLerpOver == Catch::Approx(glm::lerp(low, high, negOverOne)));

	// Get ratios back from lerped values
	float	invNeg = ion::math::InverseLerp(negLerp, low, high);
	float	invOverNeg = ion::math::InverseLerp(negLerpOver, low, high);


	CHECK(invNeg == Catch::Approx(negRatio));
	CHECK(invOverNeg == Catch::Approx(negOverOne));
}