#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

#include <cmath>

#define COS_IT 6u

namespace mth
{
	static float cosFlt(float _val)
	{
		float powResult, cosResult = 0.f, itResult, radians = wrap(_val, -MTH_PI, MTH_PI);

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			powResult = pow(radians, it * 2);

			itResult = powResult * mth::Factorials::evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult;

		return cosResult;
	}

	float cos(const Radian& _rad)
	{
		float powResult, cosResult = 0.f, radians = _rad.Rad(true), itResult;

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			powResult = pow(radians, it * 2);

			itResult = powResult * mth::Factorials::evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult ;

		return cosResult;
	}

	float sin(const Radian& _rad)
	{
		// Apply 90 degree offset
		// See: https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/1920px-Sine_cosine_one_period.svg.png
		constexpr float		piOverTwo = 1.570796326794896619231f;

		float				cosine = cosFlt(absolute(_rad.Raw()) - piOverTwo);

		if (_rad.Raw() < 0.f)
			return -cosine;

		else return cosine;
	}

	float tan(const Radian& _rad)
	{
		// tan x = sin x / cos x
		return sin(_rad) / cos(_rad);
	}


	Radian acos(float _cosine)
	{
		float powResult, acosResult = 0.f, itResult;

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			powResult = pow(_cosine, it * 2);

			itResult = powResult * mth::Factorials::evenFacts[it - 1];

			acosResult += itResult;

		}

		acosResult = _cosine + acosResult;

		return Radian(acosResult);
	}

	const float mth::Factorials::evenFacts[] =
	{
			// Pre-compute even factorials and divisions for faster cosine execution
			1.f / static_cast<float>(factorial(2)),
			-1.f / static_cast<float>(factorial(4)),
			1.f / static_cast<float>(factorial(6)),
			-1.f / static_cast<float>(factorial(8)),
			1.f / static_cast<float>(factorial(10)),
			-1.f / static_cast<float>(factorial(12)),
	};

}

