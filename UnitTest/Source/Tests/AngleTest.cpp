#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>

#include "libmath/Arithmetic.h"
#include "libmath/Angle.h"


using namespace mth::Literal;

TEST_CASE("Degree", "[angle] [all]")
{
	SECTION("Instanciation")
	{
			// Default
			mth::Degree		emptyDeg;

			// With value
			mth::Degree		valueDeg(300.f);

			// Copy constructor
			mth::Degree		cpyDeg(valueDeg);

			// Literal
			mth::Degree     litDeg = 16_deg;
			mth::Degree		litDeg2 = 5.4_deg;


			CHECK(valueDeg.Raw() == 300.f);
			CHECK(valueDeg.Raw() == cpyDeg.Raw());
			CHECK(litDeg.Raw() == 16.f);
			CHECK(litDeg2.Raw() == 5.4f);

	}

	SECTION("Accessors")
	{
		mth::Degree		wrapTrue(300.f), wrapFalse(-60.f), wrapNever(60.f);

		// No wrapping
		CHECK(wrapTrue.Deg(false) == wrapTrue.Raw());
		CHECK(wrapFalse.Deg(true) == wrapFalse.Raw());

		CHECK(wrapNever.Deg(false) == wrapNever.Raw());
		CHECK(wrapNever.Deg(true) == wrapNever.Raw());

		// Should wrap
		CHECK(wrapFalse.Deg(false) == 300.f);
		CHECK(wrapTrue.Deg(true) == -60.f);

	}

	SECTION("Degree - degree operators")
	{
		mth::Degree		firstDeg(60.f), secondDeg(30.f);

		mth::Degree		result = firstDeg + secondDeg;

		CHECK(result.Raw() == 90.f);

		result = firstDeg - secondDeg;

		CHECK(result.Raw() == 30.f);

		result = firstDeg * secondDeg;

		CHECK(result.Raw() == 1800.f);

		result = firstDeg / secondDeg;

		CHECK(result.Raw() == 2.f);

		result = 60.f;

		CHECK(result.Raw() == 60.f);

		result += mth::Degree(30.f);

		CHECK(result.Raw() == 90.f);

		result -= mth::Degree(30.f);

		CHECK(result.Raw() == 60.f);

		result *= mth::Degree(2.f);

		CHECK(result.Raw() == 120.f);

		result /= mth::Degree(2.f);

		CHECK(result.Raw() == 60.f);

	}

	SECTION("Degree - float operators")
	{
		mth::Degree			firstDeg(60.f);

		constexpr float		rightOperand = 30.f;

		mth::Degree		result = firstDeg + rightOperand;

		CHECK(result.Raw() == 90.f);

		result = firstDeg - rightOperand;

		CHECK(result.Raw() == 30.f);

		result = firstDeg * rightOperand;

		CHECK(result.Raw() == 1800.f);

		result = firstDeg / rightOperand;

		CHECK(result.Raw() == 2.f);

		result = 60.f;

		CHECK(result.Raw() == 60.f);

		result += rightOperand;

		CHECK(result.Raw() == 90.f);

		result -= rightOperand;

		CHECK(result.Raw() == 60.f);

		result *= 2.f;

		CHECK(result.Raw() == 120.f);

		result /= 2.f;

		CHECK(result.Raw() == 60.f);
	}
}