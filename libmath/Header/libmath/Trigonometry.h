#pragma once

#include "libmath/Angle.h"

#define MIN_COS		-1.f
#define MAX_COS		1.f


namespace mth
{
	float		Cos(const Radian& _rad);

	float		Sin(const Radian& _rad);

	float		Tan(const Radian& _rad);


	Radian		Acos(float _cosine);
	Radian		Asin(float _sine);
	Radian		Atan(float _tangent);

	Radian		Atan2(float _y, float _x);



	class Factorials
	{
	public:

				Factorials(void) = default;


		static const float		m_evenFacts[6];
	};
}

namespace LibMath = mth;
namespace lm = mth;