#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/norm.hpp>

#include "Timer.h"

#include "libmath/Vector4.h"

#define CHECK_VECTOR4(vec1, vec2)\
for (int iteration = 0; iteration < 4; ++iteration)\
	CHECK(vec1[iteration] == Catch::Approx(vec2[iteration]))


TEST_CASE("Vector4", "[all][vector]")
{
	SECTION("Instanciation")
	{
		mth::Vector4	empty;
		mth::Vector4	vec4Nums(4.f, 6.f, 5.6f, 4.5f);

		mth::Vector4	vec1Num = mth::Vector4::One();
		mth::Vector4	copy(vec4Nums);

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
		mth::Vector4			myVec(4.f, 6.f, 5.6f, 4.5f);
		glm::vec4				glmVec(4.f, 6.f, 5.6f, 4.5f);

		CHECK(myVec.X() == glmVec.x);
		CHECK(myVec.Y() == glmVec.y);

		CHECK(myVec.GetX() == glmVec.x);
		CHECK(myVec.GetY() == glmVec.y);

		CHECK(myVec[0] == glmVec[0]);
		CHECK(myVec[1] == glmVec[1]);


		// const tests
		const mth::Vector4		vec4(myVec);


		CHECK(vec4.GetX() == glmVec.x);
		CHECK(vec4.GetY() == glmVec.y);

		CHECK(vec4[0] == glmVec[0]);
		CHECK(vec4[1] == glmVec[1]);
	}


	SECTION("Magnitude and distance")
	{
		mth::Vector4	vec4Nums(4.f, 6.f, 5.6f, 4.5f);
		glm::vec4		glm2Nums(4.f, 6.f, 5.6f, 4.5f);

		mth::Vector4	belowOne(0.1f, 0.4f, 0.005f, 0.017f);
		glm::vec4		glmBelowOne(0.1f, 0.4f, 0.005f, 0.017f);

		mth::Vector4	otherBelowOne(0.6f, 0.f, 0.0001f, 0.f);
		glm::vec4		otherGlmBelowOne(0.6f, 0.f, 0.0001f, 0.f);

		CHECK(vec4Nums.Magnitude() == glm::length(glm2Nums));
		CHECK(vec4Nums.MagnitudeSquared() == glm::length2(glm2Nums));

		CHECK(belowOne.Magnitude() == glm::length(glmBelowOne));
		CHECK(belowOne.MagnitudeSquared() == glm::length2(glmBelowOne));

		CHECK(otherBelowOne.Magnitude() == glm::length(otherGlmBelowOne));
		CHECK(otherBelowOne.MagnitudeSquared() == glm::length2(otherGlmBelowOne));


		CHECK(belowOne.IsShorterThan(otherBelowOne));
		CHECK_FALSE(belowOne.IsLongerThan(vec4Nums));


		mth::Vector4	unit = mth::Vector4::Left();

		CHECK(unit.IsUnitVector());

		CHECK_FALSE(belowOne.IsUnitVector());
		CHECK_FALSE(vec4Nums.IsUnitVector());

		belowOne.Normalize();

		CHECK(belowOne.IsUnitVector());

		mth::Vector4	normalized = mth::Normalize(vec4Nums);

		CHECK(normalized.IsUnitVector());

		belowOne = { 0.1f, 0.4f, 0.005f, 0.017f };

		float distance = belowOne.DistanceFrom(vec4Nums);

		float glmDistance = glm::distance(glmBelowOne, glm2Nums);

		CHECK(distance == glmDistance);

		CHECK(belowOne.DistanceSquaredFrom(vec4Nums) == Catch::Approx(distance * distance));

		CHECK(mth::Distance(belowOne, vec4Nums) == glmDistance);
		CHECK(mth::DistanceSquared(belowOne, vec4Nums) == Catch::Approx(glmDistance * glmDistance));


	}


	SECTION("Vector operations")
	{
		const	  mth::Vector4		vecOne(4.f, -6.f, 27.4f, 60.f);
		constexpr glm::vec4			glmOne(4.f, -6.f, 27.4f, 60.f);

		const	  mth::Vector4		vecTwo(3.f, 9.f, 45.6f, 4.f);
		constexpr glm::vec4			glmTwo(3.f, 9.f, 45.6f, 4.f);


		SECTION("Dot / Translate - scale")
		{


			float				objDot = vecOne.Dot(vecTwo);
			float				glmDot = glm::dot(glmOne, glmTwo);

			CHECK(objDot == glmDot);
			CHECK(mth::Dot(vecOne, vecTwo) == objDot);

			mth::Vector4		result = vecOne;

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

			mth::Vector4		normalOne = mth::Normalize(vecOne);
			mth::Vector4		normalTwo = mth::Normalize(vecTwo);

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


			mth::Radian			xRad{ angleX }, yRad{ angleY }, zRad{ angleZ };
			glm::vec4			glmRotated = glm::orientate4(rotation) * glmOne;
			mth::Vector4		rotated = mth::Rotate(vecOne, xRad, yRad, zRad);

			CHECK_VECTOR4(rotated, glmRotated);

			// Axis
			angleX = -2.f;
			xRad = -2.f;

			glm::vec3		glmAxis(13.f, 5.f, 5.f);
			mth::Vector3	axis(13.f, 5.f, 5.f);

			glmAxis = glm::normalize(glmAxis);

			glmRotated = glm::rotate(glmOne, angleX, glmAxis);
			rotated = mth::Rotate(vecOne, xRad, axis);

			CHECK_VECTOR4(rotated, glmRotated);
		}



		SECTION("Projection / reflection")
		{
			mth::Vector4	result = mth::Project(vecOne, vecTwo);
			glm::vec4		glmResult = glm::proj(glmOne, glmTwo);

			CHECK_VECTOR4(result, glmResult);

			result = mth::Project(vecTwo, vecOne);
			glmResult = glm::proj(glmTwo, glmOne);

			CHECK_VECTOR4(result, glmResult);


			// Normalized normal
			result = mth::Reflect(vecOne, vecTwo);
			glmResult = glm::reflect(glmOne, glm::normalize(glmTwo));

			CHECK_VECTOR4(result, glmResult);

			// Non-normalized normal
			result = mth::ReflectUnit(vecOne, vecTwo);
			glmResult = glm::reflect(glmOne, glmTwo);

			CHECK_VECTOR4(result, glmResult);

		}


	}


	SECTION("Static vectors")
	{
		CHECK_VECTOR4(mth::Vector4::One(), glm::vec4(1.f));
		CHECK_VECTOR4(mth::Vector4::Zero(), glm::vec4(0.f));

		CHECK_VECTOR4(mth::Vector4::Left(), glm::vec4(-1.f, 0.f, 0.f, 0.f));
		CHECK_VECTOR4(mth::Vector4::Right(), glm::vec4(1.f, 0.f, 0.f, 0.f));

		CHECK_VECTOR4(mth::Vector4::Up(), glm::vec4(0.f, 1.f, 0.f, 0.f));
		CHECK_VECTOR4(mth::Vector4::Down(), glm::vec4(0.f, -1.f, 0.f, 0.f));

		CHECK_VECTOR4(mth::Vector4::Back(), glm::vec4(0.f, 0.f, -1.f, 0.f));
		CHECK_VECTOR4(mth::Vector4::Front(), glm::vec4(0.f, 0.f, 1.f, 0.f));
	}


	SECTION("I/O and strings")
	{

		mth::Vector4		input(-1.4f, 5.6f, 7.6f, 4.2f);
		mth::Vector4		output;
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
		mth::Vector4	vecOne(4.1f, 3.7f, 45.3f, 5.f), vecTwo(1.1f, 5.1f, 22.f, 14.f);
		glm::vec4		glmOne(4.1f, 3.7f, 45.3f, 5.f), glmTwo(1.1f, 5.1f, 22.f, 14.f);

		mth::Vector4	result = vecOne + vecTwo;
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

		mth::Vector4			vecThree(154.f, 0.f, 50.f, 45.f);

		CHECK(vecThree != result);
		CHECK_FALSE(vecOne == vecThree);

	}

}
