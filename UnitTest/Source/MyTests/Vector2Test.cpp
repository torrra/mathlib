#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/norm.hpp>

#include "libmath/Arithmetic.h"
#include "libmath/Vector2.h"

#include "Timer.h"


// Uncomment to display timer results
#define DISPLAY_VEC2

#pragma region timer_macros

#ifdef DISPLAY_VEC2

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
std::cout << #func ": Average execution time over " <<\
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

#endif

#pragma endregion timer_macros


#define CHECK_VECTOR2(vec1, vec2)\
CHECK(vec1[0] == Catch::Approx(vec2[0]));\
CHECK(vec1[1] == Catch::Approx(vec2[1]))

TEST_CASE("Vector 2", "[all][vector]")
{
	SECTION("Instanciation")
	{
		ion::math::Vector2	empty;
		ion::math::Vector2	vec2Nums(4.f, 6.f);

		ion::math::Vector2	vec1Num = ion::math::Vector2::One();
		ion::math::Vector2	copy(vec2Nums);

		glm::vec2		glmZero(0.f);
		glm::vec2		glm2Nums(4.f, 6.f);
		glm::vec2		glm1Num(1.f);

		CHECK_VECTOR2(empty, glmZero);
		CHECK_VECTOR2(vec2Nums, glm2Nums);

		CHECK_VECTOR2(vec1Num, glm1Num);

		CHECK_VECTOR2(copy, vec2Nums);

		empty = vec2Nums;

		CHECK_VECTOR2(empty, vec2Nums);
	}


	SECTION("Accessors")
	{
		ion::math::Vector2			myVec(4.f, 6.f);
		glm::vec2				glmVec(4.f, 6.f);

		CHECK(myVec.X() == glmVec.x);
		CHECK(myVec.Y() == glmVec.y);

		CHECK(myVec.GetX() == glmVec.x);
		CHECK(myVec.GetY() == glmVec.y);

		CHECK(myVec[0] == glmVec[0]);
		CHECK(myVec[1] == glmVec[1]);


		// const tests
		const ion::math::Vector2		vec2(myVec);

		// Must NOT compile
		// CHECK(vec2.X() == glmVec.x);
		// CHECK(vec2.Y() == glmVec.y);

		CHECK(vec2.GetX() == glmVec.x);
		CHECK(vec2.GetY() == glmVec.y);

		CHECK(vec2[0] == glmVec[0]);
		CHECK(vec2[1] == glmVec[1]);
	}


	SECTION("Magnitude and distance")
	{
		ion::math::Vector2	vec2Nums(4.f, 6.f);
		glm::vec2		glm2Nums(4.f, 6.f);

		ion::math::Vector2	belowOne(0.1f, 0.4f);
		glm::vec2		glmBelowOne(0.1f, 0.4f);

		ion::math::Vector2	otherBelowOne(0.6f, 0.f);
		glm::vec2		otherGlmBelowOne(0.6f, 0.f);

		CHECK(vec2Nums.Magnitude() == glm::length(glm2Nums));
		CHECK(vec2Nums.MagnitudeSquared() == glm::length2(glm2Nums));

		CHECK(belowOne.Magnitude() == glm::length(glmBelowOne));
		CHECK(belowOne.MagnitudeSquared() == glm::length2(glmBelowOne));

		CHECK(otherBelowOne.Magnitude() == glm::length(otherGlmBelowOne));
		CHECK(otherBelowOne.MagnitudeSquared() == glm::length2(otherGlmBelowOne));


		CHECK(belowOne.IsShorterThan(otherBelowOne));
		CHECK_FALSE(belowOne.IsLongerThan(vec2Nums));


		ion::math::Vector2	unit = ion::math::Vector2::Left();

		CHECK(unit.IsUnitVector());

		CHECK_FALSE(belowOne.IsUnitVector());
		CHECK_FALSE(vec2Nums.IsUnitVector());

		belowOne.Normalize();

		CHECK(belowOne.IsUnitVector());

		ion::math::Vector2	normalized = ion::math::Normalize(vec2Nums);

		CHECK(normalized.IsUnitVector());

		belowOne = { 0.1f, 0.4f };

		float distance = belowOne.DistanceFrom(vec2Nums);

		float glmDistance = glm::distance(glmBelowOne, glm2Nums);

		CHECK(distance == glmDistance);

		CHECK(belowOne.DistanceSquaredFrom(vec2Nums) == distance * distance);

		CHECK(ion::math::Distance(belowOne, vec2Nums) == glmDistance);
		CHECK(ion::math::DistanceSquared(belowOne, vec2Nums) == glmDistance * glmDistance);


	}


	SECTION("Vector operations")
	{
		const	  ion::math::Vector2		vecOne(4.f, -6.f);
		constexpr glm::vec2			glmOne(4.f, -6.f);

		const	  ion::math::Vector2		vecTwo(3.f, 9.f);
		constexpr glm::vec2			glmTwo(3.f, 9.f);


		SECTION ("Dot - cross / Translate - scale")
		{
			constexpr float				expectedCrossZ = 54.f;


			float				objDot = vecOne.Dot(vecTwo);
			float				glmDot = glm::dot(glmOne, glmTwo);

			CHECK(objDot == glmDot);
			CHECK(ion::math::Dot(vecOne, vecTwo) == objDot);

			// Test both from object reference and as function outside of class
			CHECK(vecOne.Cross(vecTwo) == expectedCrossZ);
			CHECK(ion::math::Cross(vecOne, vecTwo) == expectedCrossZ);

			// Cross product is non-commutative
			CHECK_FALSE(ion::math::Cross(vecTwo, vecOne) == expectedCrossZ);

			ion::math::Vector2		result = vecOne;

			result.Translate(vecTwo);

			CHECK_VECTOR2(result, (glmOne + glmTwo));

			result = vecOne;

			result.Scale(vecTwo);

			CHECK_VECTOR2(result, (glmOne * glmTwo));
		}


		SECTION("Angles")
		{
			float				myAngle = vecOne.AngleFrom(vecTwo)
				.Rad(false);

			float				glmAngle = glm::angle
			(
				glm::normalize(glmTwo),
				glm::normalize(glmOne)
			);

			CHECK(myAngle == Catch::Approx(glmAngle));

			ion::math::Vector2		normalOne = ion::math::Normalize(vecOne);
			ion::math::Vector2		normalTwo = ion::math::Normalize(vecTwo);

			CHECK(normalOne.IsUnitVector());
			CHECK(normalTwo.IsUnitVector());

			float				angleUnits = normalOne.AngleFromUnit(normalTwo)
													  .Rad(false);


			CHECK(angleUnits == Catch::Approx(glmAngle));


			float				cappedAngle = vecOne.AngleFromUnit(vecTwo)
													.Rad(false);

			// Should cap at PI radians
			CHECK(cappedAngle == Catch::Approx(glm::angle(glmOne, glmTwo)));

		}

		SECTION("Rotation")
		{
			// Rotate with a positive angle
			float				angleF = 35 * DEG2RAD;

			ion::math::Radian			angleRad{ 35.f * DEG2RAD };
			glm::vec2			glmRotated = glm::rotate(glmOne, angleF);
			ion::math::Vector2		rotated = ion::math::Rotate(vecOne, angleRad);

			CHECK_VECTOR2(rotated, glmRotated);

			// Negative angle
			angleF = -2.f;
			angleRad = -2.f;

			glmRotated = glm::rotate(glmOne, angleF);
			rotated = ion::math::Rotate(vecOne, angleRad);

			CHECK_VECTOR2(rotated, glmRotated);
		}



		SECTION("Projection / reflection")
		{
			ion::math::Vector2	result = ion::math::Project(vecOne, vecTwo);
			glm::vec2		glmResult = glm::proj(glmOne, glmTwo);

			CHECK_VECTOR2(result, glmResult);

			result = ion::math::Project(vecTwo, vecOne);
			glmResult = glm::proj(glmTwo, glmOne);

			CHECK_VECTOR2(result, glmResult);


			// Normalized normal
			result = ion::math::Reflect(vecOne, vecTwo);
			glmResult = glm::reflect(glmOne, glm::normalize(glmTwo));

			CHECK_VECTOR2(result, glmResult);

			// Non-normalized normal
			result = ion::math::ReflectUnit(vecOne, vecTwo);
			glmResult = glm::reflect(glmOne, glmTwo);

			CHECK_VECTOR2(result, glmResult);

		}


	}


	SECTION("Static vectors")
	{
		CHECK_VECTOR2(ion::math::Vector2::One(), glm::vec2(1.f));
		CHECK_VECTOR2(ion::math::Vector2::Zero(), glm::vec2(0.f));

		CHECK_VECTOR2(ion::math::Vector2::Left(), glm::vec2(-1.f, 0.f));
		CHECK_VECTOR2(ion::math::Vector2::Right(), glm::vec2(1.f, 0.f));

		CHECK_VECTOR2(ion::math::Vector2::Up(), glm::vec2(0.f, 1.f));
		CHECK_VECTOR2(ion::math::Vector2::Down(), glm::vec2(0.f, -1.f));
	}


	SECTION("I/O and strings")
	{

		ion::math::Vector2		input(-1.4f, 5.6f);
		ion::math::Vector2		output;
		std::string			extra;

		std::stringstream	buffer;

		buffer << input;

		CHECK(buffer.str() == "{-1.4,5.6}");
		CHECK(input.String() == "{-1.4,5.6}");

		CHECK(input.StringLong() == "Vector2{ x:-1.4, y:5.6 }");

		buffer << " extra";

		buffer >> output;

		CHECK_VECTOR2(input, output);

		buffer >> extra;

		CHECK(extra == "extra");


	}


	SECTION("Operators")
	{
		ion::math::Vector2	vecOne(4.1f, 3.7f), vecTwo(1.1f, 5.1f);
		glm::vec2		glmOne(4.1f, 3.7f), glmTwo(1.1f, 5.1f);

		ion::math::Vector2	result = vecOne + vecTwo;
		glm::vec2		glmResult = glmOne + glmTwo;

		float			scalar = 3.5f;

		CHECK_VECTOR2(result, glmResult);

		result = vecOne - vecTwo;
		glmResult = glmOne - glmTwo;

		CHECK_VECTOR2(result, glmResult);

		result = vecOne * vecTwo;
		glmResult = glmOne * glmTwo;

		CHECK_VECTOR2(result, glmResult);

		result = vecOne / vecTwo;
		glmResult = glmOne / glmTwo;

		CHECK_VECTOR2(result, glmResult);

		result = vecOne * scalar;
		glmResult = glmOne * scalar;

		CHECK_VECTOR2(result, glmResult);


		result = vecOne / scalar;
		glmResult = glmOne / scalar;

		CHECK_VECTOR2(result, glmResult);

		result = vecOne;
		glmResult = glmOne;

		CHECK_VECTOR2(result, glmResult);

		result += vecTwo;
		glmResult += glmTwo;

		CHECK_VECTOR2(result, glmResult);

		result -= vecTwo;
		glmResult -= glmTwo;

		CHECK_VECTOR2(result, glmResult);

		result *= vecTwo;
		glmResult *= glmTwo;

		CHECK_VECTOR2(result, glmResult);

		result /= vecTwo;
		glmResult /= glmTwo;

		CHECK_VECTOR2(result, glmResult);


		result *= scalar;
		glmResult *= scalar;

		CHECK_VECTOR2(result, glmResult);

		result /= scalar;
		glmResult /= scalar;

		CHECK_VECTOR2(result, glmResult);

		CHECK(result == result);

		ion::math::Vector2			vecThree(154.f, 0.f);

		CHECK(vecThree != result);
		CHECK_FALSE(vecOne == vecThree);

	}

}