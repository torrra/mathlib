#pragma once

#include "libmath/Angle.h"

namespace mth
{
	float		Cos(const Radian& _rad);

	float		Sin(const Radian& _rad);

	float		Tan(const Radian& _rad);


	Radian		Acos(float _cosine);
	Radian		Asin(float _sine);
	Radian		Atan(float _tangent);

	Radian		Atan2(float _tangent);



	class Factorials
	{
	public:

				Factorials(void) = default;


		static const float		m_evenFacts[6];
	};
}

namespace LibMath = mth;
namespace lm = mth;