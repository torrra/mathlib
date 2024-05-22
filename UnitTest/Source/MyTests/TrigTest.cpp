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

// Uncomment to display results
//#define DISPLAY_TRIG

#ifdef DISPLAY_TRIG

#define RECORD_FUNC(timer, func, out)\
timer.clear();\
timer.start();\
out = func;\
timer.stop();\
std::cout << '\n' << #func << '\n'; \
timer.display();

#else

# define RECORD_FUNC(timer, func, out)\
out = func;

#endif

TEST_CASE("Trigonometry - my tests", "[all]")
{
	SECTION("Positive angle")
	{
		constexpr float		sixtyDeg = MTH_PI / 3.f;

		mth::Radian			myRad(sixtyDeg);
		Timer				stopwatch;
		float				myCos, glmCos, stdCos;


		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(sixtyDeg), glmCos);

		RECORD_FUNC(stopwatch, std::cos(sixtyDeg), stdCos);
		CHECK(mth::almostEqual(myCos, glmCos));

		float				mySin, glmSin, stdSin;


		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(sixtyDeg), glmSin);
		RECORD_FUNC(stopwatch, std::sin(sixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));


		float				myTan, glmTan, stdTan;


		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);
		RECORD_FUNC(stopwatch, glm::tan(sixtyDeg), glmTan);
		RECORD_FUNC(stopwatch, std::tan(sixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));



#ifdef DISPLAY_TRIG

		std::cout << "\n-- COSINE PI / 3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myCos, glmCos, stdCos);

		std::cout << "-- SINE PI / 3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", mySin, glmSin, stdSin);

		std::cout << "-- TANGENT PI / 3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myTan, glmTan, stdTan);

#endif
	}

	SECTION("Negative angle")
	{
		constexpr float		minusSixtyDeg = -MTH_PI / 3.f;
		mth::Radian			myRad(minusSixtyDeg);
		Timer				stopwatch;

		float				myCos, glmCos, stdCos;

		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(minusSixtyDeg), glmCos);
		RECORD_FUNC(stopwatch, std::cos(minusSixtyDeg), stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));

		float				mySin, glmSin, stdSin;


		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(minusSixtyDeg), glmSin);
		RECORD_FUNC(stopwatch, std::sin(minusSixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));


		float				myTan, glmTan, stdTan;


		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);
		RECORD_FUNC(stopwatch, glm::tan(minusSixtyDeg), glmTan);
		RECORD_FUNC(stopwatch, std::tan(minusSixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

#ifdef DISPLAY_TRIG

		std::cout << "\n-- COSINE -PI / 3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myCos, glmCos, stdCos);

		std::cout << "-- SINE -PI / 3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", mySin, glmSin, stdSin);

		std::cout << "-- TANGENT -PI / 3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myTan, glmTan, stdTan);

#endif
	}

	SECTION("Wrapped negative angle")
	{
		constexpr float		minusFive = -5.f;

		mth::Radian			myRad(minusFive);
		Timer				stopwatch;
		float				myCos, glmCos, stdCos;


		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(minusFive), glmCos);
		RECORD_FUNC(stopwatch, std::cos(minusFive), stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));

		float				mySin, glmSin, stdSin;

		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(minusFive), glmSin);
		RECORD_FUNC(stopwatch, std::sin(minusFive), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));

		float				myTan, glmTan, stdTan;

		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);
		RECORD_FUNC(stopwatch, glm::tan(minusFive), glmTan);
		RECORD_FUNC(stopwatch, std::tan(minusFive), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

#ifdef DISPLAY_TRIG

		std::cout << "\n-- COSINE -5 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myCos, glmCos, stdCos);

		std::cout << "-- SINE -5 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", mySin, glmSin, stdSin);

		std::cout << "-- TANGENT -5 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myTan, glmTan, stdTan);

#endif
	}

	SECTION("Wrapped positive angle")
	{
		constexpr float		sixtyDeg = 7.3f;
		mth::Radian			myRad(sixtyDeg);
		Timer				stopwatch;

		float				myCos, glmCos, stdCos;


		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(sixtyDeg), glmCos);
		RECORD_FUNC(stopwatch, std::cos(sixtyDeg), stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));

		float				mySin, glmSin, stdSin;


		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(sixtyDeg), glmSin);
		RECORD_FUNC(stopwatch, std::sin(sixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));


		float				myTan, glmTan, stdTan;

		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);
		RECORD_FUNC(stopwatch, glm::tan(sixtyDeg), glmTan);
		RECORD_FUNC(stopwatch, std::tan(sixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

#ifdef DISPLAY_TRIG

		std::cout << "\n-- COSINE 7.3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myCos, glmCos, stdCos);

		std::cout << "-- SINE 7.3--\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", mySin, glmSin, stdSin);

		std::cout << "-- TANGENT 7.3 --\n";
		std::printf("\nmine : %.5f\tglm : %.5f\t cmath : %.5f\n\n", myTan, glmTan, stdTan);

#endif
	}

}