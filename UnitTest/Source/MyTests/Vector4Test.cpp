#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/norm.hpp>

#include "Timer.h"

#include "math/Vector4.hpp"

#define CHECK_VECTOR4(vec1, vec2)\
for (int iteration = 0; iteration < 4; ++iteration)\
	CHECK(vec1[iteration] == Catch::Approx(vec2[iteration]))


TEST_CASE("Vector4f", "[all][vector]")
{
	SECTION("Instanciation")
	{
		math::Vector4f	empty;
		math::Vector4f	vec4Nums(4.f, 6.f, 5.6f, 4.5f);

		math::Vector4f	vec1Num = math::Vector4f::One();
		math::Vector4f	copy(vec4Nums);

		glm::vec4		glmZero(0.f);
		glm::vec4		glm2Nums(4.f, 6.f, 5.6f, 4.5f);
		glm::vec4		glm1Num(1.f);

		CHECK_VECTOR4(empty, glmZero);
		CHECK_VECTOR4(vec4Nums, glm2Nums);

		CHECK_VECTOR4(vec1Num, glm1Num);

		CHECK_VECTOR4(copy, vec4Nums);

		empty = vec4Nums;

		CHECK_VECTOR4(empty, vec4Nums);
	}


	SECTION("Accessors")
	{
		math::Vector4f			myVec(4.f, 6.f, 5.6f, 4.5f);
		glm::vec4				glmVec(4.f, 6.f, 5.6f, 4.5f);

		CHECK(myVec.X() == glmVec.x);
		CHECK(myVec.Y() == glmVec.y);

		CHECK(myVec.GetX() == glmVec.x);
		CHECK(myVec.GetY() == glmVec.y);

		CHECK(myVec[0] == glmVec[0]);
		CHECK(myVec[1] == glmVec[1]);


		// const tests
		const math::Vector4f		vec4(myVec);


		CHECK(vec4.GetX() == glmVec.x);
		CHECK(vec4.GetY() == glmVec.y);

		CHECK(vec4[0] == glmVec[0]);
		CHECK(vec4[1] == glmVec[1]);
	}


	SECTION("Magnitude and distance")
	{
		math::Vector4f	vec4Nums(4.f, 6.f, 5.6f, 4.5f);
		glm::vec4		glm2Nums(4.f, 6.f, 5.6f, 4.5f);

		math::Vector4f	belowOne(0.1f, 0.4f, 0.005f, 0.017f);
		glm::vec4		glmBelowOne(0.1f, 0.4f, 0.005f, 0.017f);

		math::Vector4f	otherBelowOne(0.6f, 0.f, 0.0001f, 0.f);
		glm::vec4		otherGlmBelowOne(0.6f, 0.f, 0.0001f, 0.f);

		CHECK(vec4Nums.Magnitude() == glm::length(glm2Nums));
		CHECK(vec4Nums.MagnitudeSquared() == glm::length2(glm2Nums));

		CHECK(belowOne.Magnitude() == glm::length(glmBelowOne));
		CHECK(belowOne.MagnitudeSquared() == glm::length2(glmBelowOne));

		CHECK(otherBelowOne.Magnitude() == glm::length(otherGlmBelowOne));
		CHECK(otherBelowOne.MagnitudeSquared() == glm::length2(otherGlmBelowOne));


		CHECK(belowOne.IsShorterThan(otherBelowOne));
		CHECK_FALSE(belowOne.IsLongerThan(vec4Nums));


		math::Vector4f	unit = math::Vector4f::Left();

		CHECK(unit.IsUnitVector());

		CHECK_FALSE(belowOne.IsUnitVector());
		CHECK_FALSE(vec4Nums.IsUnitVector());

		belowOne.Normalize();

		CHECK(belowOne.IsUnitVector());

		math::Vector4f	normalized = math::Normalize(vec4Nums);

		CHECK(normalized.IsUnitVector());

		belowOne = { 0.1f, 0.4f, 0.005f, 0.017f };

		float distance = belowOne.DistanceFrom(vec4Nums);

		float glmDistance = glm::distance(glmBelowOne, glm2Nums);

		CHECK(distance == glmDistance);

		CHECK(belowOne.DistanceSquaredFrom(vec4Nums) == Catch::Approx(distance * distance));

		CHECK(math::Distance(belowOne, vec4Nums) == glmDistance);
		CHECK(math::DistanceSquared(belowOne, vec4Nums) == Catch::Approx(glmDistance * glmDistance));


	}


	SECTION("Vector operations")
	{
		const	  math::Vector4f		vecOne(4.f, -6.f, 27.4f, 60.f);
		constexpr glm::vec4			glmOne(4.f, -6.f, 27.4f, 60.f);

		const	  math::Vector4f		vecTwo(3.f, 9.f, 45.6f, 4.f);
		constexpr glm::vec4			glmTwo(3.f, 9.f, 45.6f, 4.f);


		SECTION("Dot / Translate - scale")
		{


			float				objDot = vecOne.Dot(vecTwo);
			float				glmDot = glm::dot(glmOne, glmTwo);

			CHECK(objDot == glmDot);
			CHECK(math::Dot(vecOne, vecTwo) == objDot);

			math::Vector4f		result = vecOne;

			result.Translate(vecTwo);

			CHECK_VECTOR4(result, (glmOne + glmTwo));

			result = vecOne;

			result.Scale(vecTwo);

			CHECK_VECTOR4(result, (glmOne * glmTwo));
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

			math::Vector4f		normalOne = math::Normalize(vecOne);
			math::Vector4f		normalTwo = math::Normalize(vecTwo);

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
			float				angleX = 35.f * DEG2RAD;
			float				angleY = 22.f * DEG2RAD;
			float				angleZ = -1.f * DEG2RAD;

			glm::vec3			rotation{angleX, angleY, angleZ };


			math::Radian			xRad{ angleX }, yRad{ angleY }, zRad{ angleZ };
			glm::vec4			glmRotated = glm::orientate4(rotation) * glmOne;
			math::Vector4f		rotated = math::Rotate(vecOne, xRad, yRad, zRad);

			CHECK_VECTOR4(rotated, glmRotated);

			// Axis
			angleX = -2.f;
			xRad = -2.f;

			glm::vec3		glmAxis(13.f, 5.f, 5.f);
			math::Vector3f	axis(13.f, 5.f, 5.f);

			glmAxis = glm::normalize(glmAxis);

			glmRotated = glm::rotate(glmOne, angleX, glmAxis);
			rotated = math::Rotate(vecOne, xRad, axis);

			CHECK_VECTOR4(rotated, glmRotated);
		}



		SECTION("Projection / reflection")
		{
			math::Vector4f	result = math::Project(vecOne, vecTwo);
			glm::vec4		glmResult = glm::proj(glmOne, glmTwo);

			CHECK_VECTOR4(result, glmResult);

			result = math::Project(vecTwo, vecOne);
			glmResult = glm::proj(glmTwo, glmOne);

			CHECK_VECTOR4(result, glmResult);


			// Normalized normal
			result = math::Reflect(vecOne, vecTwo);
			glmResult = glm::reflect(glmOne, glm::normalize(glmTwo));

			CHECK_VECTOR4(result, glmResult);

			// Non-normalized normal
			result = math::ReflectUnit(vecOne, vecTwo);
			glmResult = glm::reflect(glmOne, glmTwo);

			CHECK_VECTOR4(result, glmResult);

		}


	}


	SECTION("Static vectors")
	{
		CHECK_VECTOR4(math::Vector4f::One(), glm::vec4(1.f));
		CHECK_VECTOR4(math::Vector4f::Zero(), glm::vec4(0.f));

		CHECK_VECTOR4(math::Vector4f::Left(), glm::vec4(-1.f, 0.f, 0.f, 0.f));
		CHECK_VECTOR4(math::Vector4f::Right(), glm::vec4(1.f, 0.f, 0.f, 0.f));

		CHECK_VECTOR4(math::Vector4f::Up(), glm::vec4(0.f, 1.f, 0.f, 0.f));
		CHECK_VECTOR4(math::Vector4f::Down(), glm::vec4(0.f, -1.f, 0.f, 0.f));

		CHECK_VECTOR4(math::Vector4f::Back(), glm::vec4(0.f, 0.f, -1.f, 0.f));
		CHECK_VECTOR4(math::Vector4f::Front(), glm::vec4(0.f, 0.f, 1.f, 0.f));
	}


	SECTION("I/O and strings")
	{

		math::Vector4f		input(-1.4f, 5.6f, 7.6f, 4.2f);
		math::Vector4f		output;
		std::string			extra;

		std::stringstream	buffer;

		buffer << input;

		CHECK(buffer.str() == "{-1.4,5.6,7.6,4.2}");
		CHECK(input.String() == "{-1.4,5.6,7.6,4.2}");

		CHECK(input.StringLong() == "Vector4{ x:-1.4, y:5.6, z:7.6, w:4.2 }");

		buffer << " extra";

		buffer >> output;

		CHECK_VECTOR4(input, output);

		buffer >> extra;

		CHECK(extra == "extra");


	}


	SECTION("Operators")
	{
		math::Vector4f	vecOne(4.1f, 3.7f, 45.3f, 5.f), vecTwo(1.1f, 5.1f, 22.f, 14.f);
		glm::vec4		glmOne(4.1f, 3.7f, 45.3f, 5.f), glmTwo(1.1f, 5.1f, 22.f, 14.f);

		math::Vector4f	result = vecOne + vecTwo;
		glm::vec4		glmResult = glmOne + glmTwo;

		float			scalar = 3.5f;

		CHECK_VECTOR4(result, glmResult);

		result = vecOne - vecTwo;
		glmResult = glmOne - glmTwo;

		CHECK_VECTOR4(result, glmResult);

		result = vecOne * vecTwo;
		glmResult = glmOne * glmTwo;

		CHECK_VECTOR4(result, glmResult);

		result = vecOne / vecTwo;
		glmResult = glmOne / glmTwo;

		CHECK_VECTOR4(result, glmResult);

		result = vecOne * scalar;
		glmResult = glmOne * scalar;

		CHECK_VECTOR4(result, glmResult);


		result = vecOne / scalar;
		glmResult = glmOne / scalar;

		CHECK_VECTOR4(result, glmResult);

		result = vecOne;
		glmResult = glmOne;

		CHECK_VECTOR4(result, glmResult);

		result += vecTwo;
		glmResult += glmTwo;

		CHECK_VECTOR4(result, glmResult);

		result -= vecTwo;
		glmResult -= glmTwo;

		CHECK_VECTOR4(result, glmResult);

		result *= vecTwo;
		glmResult *= glmTwo;

		CHECK_VECTOR4(result, glmResult);

		result /= vecTwo;
		glmResult /= glmTwo;

		CHECK_VECTOR4(result, glmResult);


		result *= scalar;
		glmResult *= scalar;

		CHECK_VECTOR4(result, glmResult);

		result /= scalar;
		glmResult /= scalar;

		CHECK_VECTOR4(result, glmResult);

		CHECK(result == result);

		math::Vector4f			vecThree(154.f, 0.f, 50.f, 45.f);

		CHECK(vecThree != result);
		CHECK_FALSE(vecOne == vecThree);

	}

}
