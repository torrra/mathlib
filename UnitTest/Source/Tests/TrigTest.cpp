#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

#include "Timer.h"

#include <cmath>

#define RECORD_FUNC(timer, func, out)\
timer.clear();\
timer.start();\
out = func;\
timer.stop();\
std::cout << '\n' << #func << '\n'; \
timer.display();


TEST_CASE("Trigonometry", "[all]")
{
	SECTION("Positive angle")
	{
		constexpr float sixtyDeg = MTH_PI / 3.f;

		mth::Radian  myRad(sixtyDeg);

		Timer  stopwatch;

		float myCos, glmCos, stdCos;

		std::cout << "\n-- COSINE PI / 3 --\n";

		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);

		RECORD_FUNC(stopwatch, glm::cos(sixtyDeg), glmCos);

		RECORD_FUNC(stopwatch, std::cos(sixtyDeg), stdCos);

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myCos, glmCos, stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));

		float mySin, glmSin, stdSin;

		std::cout << "-- SINE PI / 3 --\n";

		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);

		RECORD_FUNC(stopwatch, glm::sin(sixtyDeg), glmSin);

		RECORD_FUNC(stopwatch, std::sin(sixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", mySin, glmSin, stdSin);


		float myTan, glmTan, stdTan;

		std::cout << "-- TANGENT PI / 3 --\n";

		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);

		RECORD_FUNC(stopwatch, glm::tan(sixtyDeg), glmTan);

		RECORD_FUNC(stopwatch, std::tan(sixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myTan, glmTan, stdTan);
	}

	SECTION("Negative angle")
	{
		constexpr float minusSixtyDeg = -MTH_PI / 3.f;

		mth::Radian  myRad(minusSixtyDeg);

		Timer  stopwatch;

		float myCos, glmCos, stdCos;

		std::cout << "\n-- COSINE -PI / 3 --\n";

		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);

		RECORD_FUNC(stopwatch, glm::cos(minusSixtyDeg), glmCos);

		RECORD_FUNC(stopwatch, std::cos(minusSixtyDeg), stdCos);

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myCos, glmCos, stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));

		float mySin, glmSin, stdSin;

		std::cout << "-- SINE -PI / 3 --\n";

		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);

		RECORD_FUNC(stopwatch, glm::sin(minusSixtyDeg), glmSin);

		RECORD_FUNC(stopwatch, std::sin(minusSixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", mySin, glmSin, stdSin);


		float myTan, glmTan, stdTan;

		std::cout << "-- TANGENT -PI / 3 --\n";

		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);

		RECORD_FUNC(stopwatch, glm::tan(minusSixtyDeg), glmTan);

		RECORD_FUNC(stopwatch, std::tan(minusSixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myTan, glmTan, stdTan);
	}

	SECTION("Wrapped negative angle")
	{
		constexpr float sixtyDeg = -5.f;

		mth::Radian  myRad(sixtyDeg);

		Timer  stopwatch;

		float myCos, glmCos, stdCos;

		std::cout << "\n-- COSINE -5 --\n";

		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);

		RECORD_FUNC(stopwatch, glm::cos(sixtyDeg), glmCos);

		RECORD_FUNC(stopwatch, std::cos(sixtyDeg), stdCos);

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myCos, glmCos, stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));

		float mySin, glmSin, stdSin;

		std::cout << "-- SINE -5 --\n";

		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);

		RECORD_FUNC(stopwatch, glm::sin(sixtyDeg), glmSin);

		RECORD_FUNC(stopwatch, std::sin(sixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));


		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", mySin, glmSin, stdSin);


		float myTan, glmTan, stdTan;

		std::cout << "-- TANGENT -5 --\n";

		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);

		RECORD_FUNC(stopwatch, glm::tan(sixtyDeg), glmTan);

		RECORD_FUNC(stopwatch, std::tan(sixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myTan, glmTan, stdTan);
	}

}