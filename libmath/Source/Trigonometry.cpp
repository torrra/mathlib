#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

#include <cmath>

// Number of times cos should run its loop
#define COS_IT		6u

namespace mth
{
	// Cos specifically made for sin to avoid constructing another Radian object
	static float InternalCos(float _val)
	{
		float	  powResult, cosResult = 0.f, itResult;

		// Wrap angle between -pi and pi as 6 iterations of
		// Taylor's series get less accurate as the angle approaches
		// -2 pi or +2pi
		float	  radians = Wrap(_val, -MTH_PI, MTH_PI);


		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			// Get numerator, angle raised to the power of
			// an even number
			powResult = Pow(radians, it * 2);

			// Divide result by factorial of said power * sign
			itResult = powResult * mth::Factorials::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult;

		return cosResult;
	}


	static float AtanZeroX(float _y)
	{
		// Return 90 degrees * sign of _y

		if (_y > 0.f)
			return PI_OVER_TWO;

		else if (_y < 0.f)
			return -PI_OVER_TWO;

		return 0.f;
	}


	float Cos(const Radian& _rad)
	{
		// Wrap angle between -pi and pi as 6 iterations of
		// Taylor's series get less accurate as the angle approaches
		// -2 pi or +2pi
		float	radians = _rad.Rad(true);
		float	powResult, cosResult = 0.f, itResult;

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			// Get numerator, angle raised to the power of
			// an even number
			powResult = Pow(radians, it * 2);

			// Divide result by factorial of said power * sign
			itResult = powResult * mth::Factorials::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult ;

		return cosResult;

		// TODO: use local vars instead of static (cache locality)
		// TODO: implement a more standard algorithm, maybe degree 14 instead of 6 ?
	}

	float Sin(const Radian& _rad)
	{
		// Apply 90 degree offset
		// See: https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/1920px-Sine_cosine_one_period.svg.png
		constexpr float		piOverTwo = 1.570796326794896619231f;

		// cos x == cos -x so get absolute value of angle to apply offset easily
		float				cosine = InternalCos(Absolute(_rad.Raw()) - piOverTwo);


		// Restore sign of angle as sine is an odd function,
		// which means sin -x == -sinx
		if (_rad.Raw() < 0.f)
			return -cosine;

		else return cosine;

		// TODO: optimize
	}

	float Tan(const Radian& _rad)
	{
		// tan x = sin x / cos x
		return Sin(_rad) / Cos(_rad);

		// TODO: needs to be faster
	}

	// TODO: re-implement my own inverse trig functions

	Radian Acos(float _cosine)
	{
		return Radian(std::acosf(_cosine));
	}

	Radian Asin(float _sine)
	{
		return Radian(std::asinf(_sine));
	}

	Radian Atan(float _tangent)
	{
		return Radian(std::atanf(_tangent));
	}

	Radian Atan2(float _y, float _x)
	{
		// Handle x == 0 case
		if (AlmostEqual(_x, 0.0f))
			return Radian(AtanZeroX(_y));


		Radian		angle = Atan(_y / _x);

		// Find quadrant of point within trigonometric circle
		// and add offset to get correct angle

		if (_x >= 0.f && _y <= 0.f)
			angle += RAD_CIRCLE;

		else if (_x < 0.f && _y <= 0.f)
			angle += MTH_PI;

		else if (_x < 0.f && _y > 0.f)
			angle += MTH_PI;

		return angle;
	}

	const float mth::Factorials::m_evenFacts[] =
	{
			// Pre-compute even factorials and divisions
			// for faster cosine execution
			1.f / static_cast<float>(Factorial(2)),
			-1.f / static_cast<float>(Factorial(4)),
			1.f / static_cast<float>(Factorial(6)),
			-1.f / static_cast<float>(Factorial(8)),
			1.f / static_cast<float>(Factorial(10)),
			-1.f / static_cast<float>(Factorial(12))
	};

}

