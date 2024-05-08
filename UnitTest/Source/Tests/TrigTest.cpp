#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "libmath/Trigonometry.h"

#include "Timer.h"

#include <cmath>

#define RECORD_FUNC(timer, func, out)\
timer.clear();\
timer.start();\
out = func;\
timer.stop();\
timer.display();


TEST_CASE("Trigonometry", "[all]")
{
	constexpr float sixtyDeg = MTH_PI * 6.5f;

	mth::Radian  myRad(sixtyDeg);

	Timer  stopwatch;

	float myCos, glmCos, stdCos;

	RECORD_FUNC(stopwatch, mth::cos(myRad), myCos);

	RECORD_FUNC(stopwatch, glm::cos(sixtyDeg), glmCos);

	RECORD_FUNC(stopwatch, std::cos(sixtyDeg), stdCos);

	std::printf("mine : %.5f\tglm : %.5f\t cmath : %.5f\n", myCos, glmCos, stdCos);

	/*float mySin, glmSin, stdSin;

	RECORD_FUNC(stopwatch, mth::sin(myRad), mySin);

	RECORD_FUNC(stopwatch, glm::sin(sixtyDeg), glmSin);

	RECORD_FUNC(stopwatch, std::sin(sixtyDeg), stdSin);

	std::printf("mine : %.5f\tglm : %.5f\t cmath : %.5f\n", mySin, glmSin, stdSin);*/


}