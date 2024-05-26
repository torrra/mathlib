#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "libmath/Arithmetic.h"
#include "libmath/Angle.h"


using namespace mth::Literal;

TEST_CASE("Degree - my tests", "[angle] [all]")
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


TEST_CASE("Radians - my tests", "[angle] [all]")
{
	SECTION("Instanciation")
	{
		// Default
		mth::Radian		emptyRad;

		// With value
		mth::Radian		valueRad(1.2f);

		// Copy constructor
		mth::Radian		cpyRad(valueRad);

		// Literal
		mth::Radian     litRad = 15_rad;
		mth::Radian		litRad2 = .4_rad;


		CHECK(valueRad.Raw() == 1.2f);
		CHECK(valueRad.Raw() == cpyRad.Raw());
		CHECK(litRad.Raw() == 15.f);
		CHECK(litRad2.Raw() == 0.4f);

	}

	SECTION("Accessors")
	{
		constexpr float		radCircle = glm::two_pi<float>();

		mth::Radian			wrapTrue{ 5.8f }, wrapNever{ 1.2f }, wrapFalse{ -2.2f };

		// No wrap
		CHECK(wrapTrue.Rad(false) == wrapTrue.Raw());
		CHECK(wrapFalse.Rad(true) == wrapFalse.Raw());
		CHECK(wrapNever.Rad(true) == wrapNever.Raw());
		CHECK(wrapNever.Rad(false) == wrapNever.Raw());

		// Wrap values
		CHECK(mth::AlmostEqual(wrapTrue.Rad(true), wrapTrue.Raw() - radCircle));
		CHECK(mth::AlmostEqual(wrapFalse.Rad(false), radCircle + wrapFalse.Raw()));

	}

	SECTION("Radian - radian operators")
	{
		constexpr float	thirtyDeg = MTH_PI / 6.f, sixtyDeg = MTH_PI / 3.f;

		mth::Radian		firstRad(sixtyDeg), secondRad(thirtyDeg);

		mth::Radian		result = firstRad + secondRad;

		CHECK(result.Raw() == MTH_PI / 2.f);

		result = firstRad - secondRad;

		CHECK(result.Raw() == thirtyDeg);

		result = firstRad * secondRad;

		CHECK(result.Raw() == thirtyDeg * sixtyDeg);

		result = firstRad / secondRad;

		CHECK(result.Raw() == 2.f);

		result = sixtyDeg;

		CHECK(result.Raw() == sixtyDeg);

		result += secondRad;

		CHECK(result.Raw() == MTH_PI / 2.f);

		result -= secondRad;

		CHECK(result.Raw() == sixtyDeg);

		result *= mth::Radian(2.f);

		CHECK(result.Raw() == MTH_PI / 1.5f);

		result /= mth::Radian(2.f);

		CHECK(result.Raw() == sixtyDeg);
	}


	SECTION("Radian - float operators")
	{
		constexpr float		thirtyDeg = MTH_PI / 6.f, sixtyDeg = MTH_PI / 3.f;

		mth::Radian			firstRad(sixtyDeg);

		constexpr float		rightOperand = thirtyDeg;

		mth::Radian		result = firstRad + rightOperand;

		CHECK(result.Raw() == MTH_PI / 2.f);

		result = firstRad - rightOperand;

		CHECK(result.Raw() == thirtyDeg);

		result = firstRad * rightOperand;

		CHECK(result.Raw() == sixtyDeg * thirtyDeg);

		result = firstRad / rightOperand;

		CHECK(result.Raw() == 2.f);

		result = sixtyDeg;

		CHECK(result.Raw() == sixtyDeg);

		result += rightOperand;

		CHECK(result.Raw() == MTH_PI / 2.f);

		result -= rightOperand;

		CHECK(result.Raw() == sixtyDeg);

		result *= 2.f;

		CHECK(result.Raw() == MTH_PI / 1.5f);

		result /= 2.f;

		CHECK(result.Raw() == sixtyDeg);
	}
}