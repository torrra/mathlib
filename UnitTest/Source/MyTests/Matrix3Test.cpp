#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include "math/Arithmetic.hpp"
#include "math/Matrix3.hpp"

#include "Timer.h"


// Uncomment to display timer results
#define DISPLAY_MAT3

#pragma region timer_macros

#ifdef DISPLAY_MAT3

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


#define CHECK_MATRIX3(matA, matB)\
for (int row = 0; row < 3; ++row)\
{\
	for (int column = 0; column < 3; ++column)\
	{\
		CHECK(matA[row][column] == Catch::Approx(matB[row][column]));\
	}\
}

#define PRINT_MATRIX3(mat)\
for (int row = 0; row < 3; ++row)\
{\
	for (int column = 0; column < 3; ++column)\
	{\
		std::cout << mat[row][column] << ' ';\
	}\
\
	std::cout << '\n';\
}


TEST_CASE("Matrix 3", "[matrix][all]")
{
	constexpr float doubleArr[3][3] =
	{
		{ 1.2f, 4.5f, 75.f },
		{ 4.f, 0.4f, 12.f },
		{ 7.1f, 6.2f, 3.f }
	};

	constexpr float lineArr[9] =
	{
		1.2f, 4.5f, 75.f,
		4.f, 0.4f, 12.f,
		7.1f, 6.2f, 3.f
	};


	SECTION("Instanciation")
	{
		math::Matrix3f	zeroMat(0.f);
		math::Matrix3f	doubleArrMat(doubleArr);
		math::Matrix3f	lineArrMat(lineArr);

		glm::mat3		glmZero(0.f);
		glm::mat3		glmMatrix =
		{
			{ 1.2f, 4.5f, 75.f },
			{ 4.f, 0.4f, 12.f },
			{ 7.1f, 6.2f, 3.f }
		};


		CHECK_MATRIX3(zeroMat, glmZero);
		CHECK_MATRIX3(doubleArrMat, glmMatrix);
		CHECK_MATRIX3(doubleArrMat, lineArrMat);

	}


	SECTION("Matrix operations")
	{
		math::Matrix3f	zeroMat(0.f);
		math::Matrix3f	doubleArrMat(doubleArr);
		math::Matrix3f	lineArrMat(lineArr);

		glm::mat3		glmZero(0.f);
		glm::mat3		glmMatrix =
		{
			{ 1.2f, 4.5f, 75.f },
			{ 4.f, 0.4f, 12.f },
			{ 7.1f, 6.2f, 3.f }
		};


		glm::mat3		expectedCofactors =
		{
			{-73.2f, 73.2f, 21.96f },
			{ 451.5f, -528.9f, 24.51f },
			{ 24.f, 285.6f, -17.52f }
		};


		// Determinant - critical for other functions
		REQUIRE(doubleArrMat.Determinant() == glm::determinant(glmMatrix));
		REQUIRE(zeroMat.Determinant() == glm::determinant(glmZero));


		// Cofactor
		math::Matrix3f	cofactorsResults = doubleArrMat.Cofactor();
		CHECK_MATRIX3(cofactorsResults, expectedCofactors);


		// Adjugate - transposed cofactor matrix
		CHECK_MATRIX3(doubleArrMat.Adjugate(), glm::transpose(expectedCofactors));


		// Inverse
		CHECK_MATRIX3(doubleArrMat.Inverse(), glm::inverse(glmMatrix));

	}


	SECTION("Operators")
	{
		math::Matrix3f		zero(0.f);
		math::Matrix3f		mat1(0.f);

		float mat2Arr[][3] =
		{
			{-73.2f, 73.2f, 21.96f },
			{ 451.5f, -528.9f, 24.51f },
			{ 24.f, 285.6f, -17.52f }
		};
		math::Matrix3f		mat2 = mat2Arr;

		math::Matrix3f		doubleArrMat(doubleArr);
		math::Matrix3f		lineArrMat(lineArr);

		glm::mat3		glmMatrix =
		{
			{ 1.2f, 4.5f, 75.f },
			{ 4.f, 0.4f, 12.f },
			{ 7.1f, 6.2f, 3.f }
		};

		glm::mat3		glmMatrix2 =
		{
			{-73.2f, 73.2f, 21.96f },
			{ 451.5f, -528.9f, 24.51f },
			{ 24.f, 285.6f, -17.52f }
		};
		// Assignment
		mat1 = doubleArr;

		CHECK_MATRIX3(mat1, doubleArrMat);

		// Reset matrix
		mat1.Identity(0.f);

		CHECK_MATRIX3(mat1, zero);

		mat1 = lineArrMat;

		CHECK_MATRIX3(mat1, lineArrMat);


		// Boolean
		CHECK(mat1 == lineArrMat);
		CHECK(mat1 != zero);


		// Add, subtract and multiply
		math::Matrix3f		result = mat1 + mat1;
		glm::mat3			glmResult = glmMatrix + glmMatrix;

		CHECK_MATRIX3(result, glmResult);

		result = mat1 - mat1;
		glmResult = glmMatrix - glmMatrix;

		CHECK_MATRIX3(result, glmResult);

		result = mat1 * mat2;
		glmResult = glmMatrix * glmMatrix2;

		CHECK_MATRIX3(result, glmResult);


		result = mat1 * 2.f;
		glmResult = glmMatrix * 2.f;

		CHECK_MATRIX3(result, glmResult);

		result = mat1 / 2.f;
		glmResult = glmMatrix / 2.f;

		CHECK_MATRIX3(result, glmResult);


	}

}