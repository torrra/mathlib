#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

#include <cmath>

#define COS_IT		6u

namespace mth
{
	static float cosFlt(float _val)
	{
		float powResult, cosResult = 0.f, itResult, radians = Wrap(_val, -MTH_PI, MTH_PI);

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			powResult = Pow(radians, it * 2);

			itResult = powResult * mth::Factorials::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult;

		return cosResult;
	}

	float Cos(const Radian& _rad)
	{
		float powResult, cosResult = 0.f, radians = _rad.Rad(true), itResult;

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			powResult = Pow(radians, it * 2);

			itResult = powResult * mth::Factorials::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult ;

		return cosResult;
	}

	float Sin(const Radian& _rad)
	{
		// Apply 90 degree offset
		// See: https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/1920px-Sine_cosine_one_period.svg.png
		constexpr float		piOverTwo = 1.570796326794896619231f;

		float				cosine = cosFlt(Absolute(_rad.Raw()) - piOverTwo);

		if (_rad.Raw() < 0.f)
			return -cosine;

		else return cosine;
	}

	float Tan(const Radian& _rad)
	{
		// tan x = sin x / cos x
		return Sin(_rad) / Cos(_rad);
	}

	// TODO: re-implement my own inverse tring functions

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

	const float mth::Factorials::m_evenFacts[] =
	{
			// Pre-compute even factorials and divisions for faster cosine execution
			1.f / static_cast<float>(Factorial(2)),
			-1.f / static_cast<float>(Factorial(4)),
			1.f / static_cast<float>(Factorial(6)),
			-1.f / static_cast<float>(Factorial(8)),
			1.f / static_cast<float>(Factorial(10)),
			-1.f / static_cast<float>(Factorial(12))
	};



}

