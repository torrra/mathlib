#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include "math/Arithmetic.hpp"
#include "math/Matrix4.hpp"

#include "Timer.h"


// Uncomment to display timer results
#define DISPLAY_MAT4

#pragma region timer_macros

#ifdef DISPLAY_MAT4

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


#define CHECK_MATRIX4(matA, matB)\
for (int row = 0; row < 4; ++row)\
{\
	for (int column = 0; column < 4; ++column)\
	{\
		CHECK(matA[row][column] == Catch::Approx(matB[row][column]));\
	}\
}

#define PRINT_MATRIX4(mat)\
for (int row = 0; row < 4; ++row)\
{\
	for (int column = 0; column < 4; ++column)\
	{\
		std::cout << mat[row][column] << ' ';\
	}\
\
	std::cout << '\n';\
}

#define DEBUG_MATRIX4(toDebug, control)\
for (int row = 0; row < 4; ++row)\
{\
	for (int column = 0; column < 4; ++column)\
	{\
		if(!matA[row][column] == Catch::Approx(matB[row][column]))\
			std::cout << "\nUNEQUAL: " << toDebug[row][column] << " != " << control[row][column] << '\n';\
	}\
}


TEST_CASE("Matrix 4", "[matrix][all]")
{
	constexpr float doubleArr[4][4] =
	{
		{ 1.2f, 4.5f, 75.f, 5.7f },
		{ 4.f, 0.4f, 12.f, 20.f },
		{ 7.1f, 6.2f, 4.f, 2.1f },
		{ 6.2f, 45.f, 36.f, 11.f}
	};

	constexpr float lineArr[16] =
	{
		1.2f, 4.5f, 75.f, 5.7f,
		4.f, 0.4f, 12.f, 20.f,
		7.1f, 6.2f, 4.f, 2.1f,
		6.2f, 45.f, 36.f, 11.f
	};


	SECTION("Instanciation")
	{
		ion::math::Matrix4<float>	zeroMat;
		ion::math::Matrix4<float>	doubleArrMat(doubleArr);
		ion::math::Matrix4<float>	lineArrMat(lineArr);

		glm::mat4		glmZero(0.f);
		glm::mat4		glmMatrix =
		{
			{ 1.2f, 4.5f, 75.f, 5.7f },
			{ 4.f, 0.4f, 12.f, 20.f },
			{ 7.1f, 6.2f, 4.f, 2.1f },
			{ 6.2f, 45.f, 36.f, 11.f}
		};


		CHECK_MATRIX4(zeroMat, glmZero);
		CHECK_MATRIX4(doubleArrMat, glmMatrix);
		CHECK_MATRIX4(doubleArrMat, lineArrMat);

	}


	SECTION("Matrix operations")
	{
		ion::math::Matrix4<float>	zeroMat;
		ion::math::Matrix4<float>	doubleArrMat(doubleArr);
		ion::math::Matrix4<float>	lineArrMat(lineArr);

		glm::mat4		glmZero(0.f);
		glm::mat4		glmMatrix =
		{
			{ 1.2f, 4.5f, 75.f, 5.7f },
		{ 4.f, 0.4f, 12.f, 20.f },
		{ 7.1f, 6.2f, 4.f, 2.1f },
		{ 6.2f, 45.f, 36.f, 11.f}
		};


		glm::mat4		expectedCofactors =
		{
			{ 1166.96f, -3708.64f, 5489.968f, -3453.2f },
			{ -2076.54f, -3603.36f, -1277.622f, 20092.74f },
			{ 61528.08f, -5691.12f, 297.144f, -12370.08f },
			{ -8575.44f, 9559.8f, -578.58f, 1871.04f }
		};


		// Determinant - critical for other functions
		REQUIRE(doubleArrMat.Determinant() == Catch::Approx(glm::determinant(glmMatrix)));
		REQUIRE(zeroMat.Determinant() == glm::determinant(glmZero));


		// Cofactor
		ion::math::Matrix4<float>	cofactorsResults = doubleArrMat.Cofactor();
		CHECK_MATRIX4(cofactorsResults, expectedCofactors);

		// Adjugate - transposed cofactor matrix
		CHECK_MATRIX4(doubleArrMat.Adjugate(), glm::transpose(expectedCofactors));


		// Inverse
		CHECK_MATRIX4(doubleArrMat.Inverse(), glm::inverse(glmMatrix));

	}


	SECTION("Operators")
	{
		ion::math::Matrix4<float>    zero;
		ion::math::Matrix4<float>	mat1;
		ion::math::Matrix4<float>	doubleArrMat(doubleArr);
		ion::math::Matrix4<float>	lineArrMat(lineArr);

		glm::mat4		glmMatrix =
		{
			{ 1.2f, 4.5f, 75.f, 5.7f },
			{ 4.f, 0.4f, 12.f, 20.f },
			{ 7.1f, 6.2f, 4.f, 2.1f },
			{ 6.2f, 45.f, 36.f, 11.f}
		};

		// Assignment
		mat1 = doubleArr;

		CHECK_MATRIX4(mat1, doubleArrMat);

		// Reset matrix
		mat1.Identity(0.f);

		CHECK_MATRIX4(mat1, zero);

		mat1 = lineArrMat;

		CHECK_MATRIX4(mat1, lineArrMat);


		// Boolean
		CHECK(mat1 == lineArrMat);
		CHECK(mat1 != zero);


		// Add, subtract and multiply
		ion::math::Matrix4<float>		result = mat1 + mat1;
		glm::mat4			glmResult = glmMatrix + glmMatrix;

		CHECK_MATRIX4(result, glmResult);

		result = mat1 - mat1;
		glmResult = glmMatrix - glmMatrix;

		CHECK_MATRIX4(result, glmResult);

		result = mat1 * mat1;
		glmResult = glmMatrix * glmMatrix;

		CHECK_MATRIX4(result, glmResult);


		result = mat1 * 2.f;
		glmResult = glmMatrix * 2.f;

		CHECK_MATRIX4(result, glmResult);

		result = mat1 / 2.f;
		glmResult = glmMatrix / 2.f;

		CHECK_MATRIX4(result, glmResult);


	}

}