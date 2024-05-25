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

#pragma region timer_macros
#ifdef DISPLAY_TRIG

#define RECORD_FUNC(timer, func, out)\
timer.clear();\
timer.start();\
out = func;\
timer.stop();\
std::cout << '\n' << #func << '\n'; \
timer.display()


#define RECORD_VOID(timer, func)\
timer.clear();\
timer.start();\
func;\
timer.stop();\
std::cout << '\n' << #func << '\n';\
timer.display()


#define AVERAGE_VOID(timer, func, avg, maxIt)\
avg       = 0;\
for (int i = 0; i < maxIt; ++i)\
{\
timer.clear(); \
timer.start(); \
func; \
timer.stop(); \
avg += timer.getElapsed();\
}\
avg /= maxIt;\
std::cout << '\n' << #func ": Average execution time over " <<\
maxIt << " iterations: " << avg << " ns \n"

#define AVERAGE_FUNC(timer, func, out, avg, maxIt)\
avg = 0; \
for (int i = 0; i < maxIt; ++i)\
{\
timer.clear(); \
timer.start(); \
out = func; \
timer.stop(); \
avg += timer.getElapsed(); \
}\
avg /= maxIt; \
std::cout << '\n' << #func ": Average execution time over " << \
maxIt << " iterations: " << avg << " ns \n"


#else

# define RECORD_FUNC(timer, func, out)\
out = func

#define RECORD_VOID(timer, func)

#define AVERAGE_VOID(timer, func, avg, maxIt)\
avg = 0; \
for (int i = 0; i < maxIt; ++i)\
{\
timer.clear(); \
timer.start(); \
func; \
timer.stop(); \
avg += timer.getElapsed(); \
}\
avg /= maxIt


#define AVERAGE_FUNC(timer, func, out, avg, maxIt)\
avg = 0; \
for (int i = 0; i < maxIt; ++i)\
{\
timer.clear(); \
timer.start(); \
out = func; \
timer.stop(); \
avg += timer.getElapsed(); \
}\
avg /= maxIt


#endif

#pragma endregion timer_macros

TEST_CASE("Trigonometry - my tests", "[all]")
{

	Timer				stopwatch;

	constexpr float		sixtyDeg = MTH_PI / 3.f;

	mth::Radian			myRad(sixtyDeg);

	float				myCos, glmCos, stdCos;
	float				mySin, glmSin, stdSin;
	float				myTan, glmTan, stdTan;

	SECTION("Positive angle")
	{


		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(sixtyDeg), glmCos);
		RECORD_FUNC(stopwatch, std::cos(sixtyDeg), stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));


		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(sixtyDeg), glmSin);
		RECORD_FUNC(stopwatch, std::sin(sixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));


		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);
		RECORD_FUNC(stopwatch, glm::tan(sixtyDeg), glmTan);
		RECORD_FUNC(stopwatch, std::tan(sixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

		long long		avg;
		int				iterations = (int) 1e4;

		AVERAGE_VOID(stopwatch, mth::cos(myRad), avg, iterations);
		AVERAGE_FUNC(stopwatch, glm::cos(sixtyDeg), glmCos, avg, iterations);

		AVERAGE_VOID(stopwatch, mth::sin(myRad), avg, iterations);
		AVERAGE_FUNC(stopwatch, glm::sin(sixtyDeg), glmSin, avg, iterations);

		AVERAGE_VOID(stopwatch, mth::tan(myRad), avg, iterations);
		AVERAGE_FUNC(stopwatch, glm::tan(sixtyDeg), glmTan, avg, iterations);


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


		myRad = minusSixtyDeg;

		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(minusSixtyDeg), glmCos);
		RECORD_FUNC(stopwatch, std::cos(minusSixtyDeg), stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));

		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(minusSixtyDeg), glmSin);
		RECORD_FUNC(stopwatch, std::sin(minusSixtyDeg), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));


		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);
		RECORD_FUNC(stopwatch, glm::tan(minusSixtyDeg), glmTan);
		RECORD_FUNC(stopwatch, std::tan(minusSixtyDeg), stdTan);

		CHECK(mth::almostEqual(myTan, glmTan));

		//const char* hi = "coucou\0


		//stopwatch.recordFunction<float>(mth::cos, true);

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

		myRad = minusFive;



		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(minusFive), glmCos);
		RECORD_FUNC(stopwatch, std::cos(minusFive), stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));
;

		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(minusFive), glmSin);
		RECORD_FUNC(stopwatch, std::sin(minusFive), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));



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
		constexpr float		sevenRad = 7.3f;

		myRad = sevenRad;



		RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);
		RECORD_FUNC(stopwatch, glm::cos(sevenRad), glmCos);
		RECORD_FUNC(stopwatch, std::cos(sevenRad), stdCos);

		CHECK(mth::almostEqual(myCos, glmCos));


		RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);
		RECORD_FUNC(stopwatch, glm::sin(sevenRad), glmSin);
		RECORD_FUNC(stopwatch, std::sin(sevenRad), stdSin);

		CHECK(mth::almostEqual(mySin, glmSin));



		RECORD_FUNC(stopwatch, mth::tan(myRad), myTan);
		RECORD_FUNC(stopwatch, glm::tan(sevenRad), glmTan);
		RECORD_FUNC(stopwatch, std::tan(sevenRad), stdTan);

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