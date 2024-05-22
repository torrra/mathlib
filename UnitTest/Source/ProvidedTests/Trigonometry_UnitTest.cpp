#include <libmath/Trigonometry.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>

#include <iostream>

TEST_CASE("Trigonometry", "[all]")
{
	LibMath::Radian radian{ 1.2f };

	CHECK(LibMath::sin(radian) == Catch::Approx(glm::sin(1.2f)));
	CHECK(LibMath::cos(radian) == Catch::Approx(glm::cos(1.2f)));
	CHECK(LibMath::tan(radian) == Catch::Approx(glm::tan(1.2f)));

	CHECK(LibMath::asin(0.5f).Rad() == Catch::Approx(glm::asin(0.5f)));
	CHECK(LibMath::acos(0.5f).Rad() == Catch::Approx(glm::acos(0.5f)));
	CHECK(LibMath::atan(0.5f).Rad() == Catch::Approx(glm::atan(0.5f)));
	//CHECK(LibMath::atan(1.f, -2.f).Rad() == Catch::Approx(glm::atan(1.f, -2.f)));
}