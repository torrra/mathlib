#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

namespace mth
{
	float cos(const Radian& _rad, unsigned int _maxIterations)
	{
		float powResult, cosResult = 0.f, radians = _rad.Rad(true), itResult;

		for (unsigned int it = 1; it <= _maxIterations; ++it)
		{
				powResult = pow(radians, it * 2);

				if (it <= 6)
					itResult = powResult * mth::Factorials::evenFacts[it - 1];
				else if (it % 2)
					itResult = powResult / factorial(it * 2);
				else
					itResult = - powResult / factorial(it * 2);

				cosResult += itResult;

		}

		cosResult = 1.f - cosResult ;

		return cosResult;
	}



	const float mth::Factorials::evenFacts[] =
	{
			1.f / static_cast<float>(factorial(2)),
			-1.f / static_cast<float>(factorial(4)),
			1.f / static_cast<float>(factorial(6)),
			-1.f / static_cast<float>(factorial(8)),
			1.f / static_cast<float>(factorial(10)),
			-1.f / static_cast<float>(factorial(12)),
	};

	const float mth::Factorials::oddFacts[] =
	{
			1.f / static_cast<float>(factorial(3)),
			-1.f / static_cast<float>(factorial(5)),
			1.f / static_cast<float>(factorial(7)),
			-1.f / static_cast<float>(factorial(9)),
			1.f / static_cast<float>(factorial(11)),
			-1.f / static_cast<float>(factorial(13)),
	};

}