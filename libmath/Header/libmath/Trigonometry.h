#pragma once

#include "libmath/Angle.h"

namespace mth
{
	float		cos(const Radian& _rad);

	float		sin(const Radian& _rad);

	float		tan(const Radian& _rad);


	Radian		acos(float _cosine);
	Radian		asin(float _sine);
	Radian		atan(float _tangent);

	Radian		atan2(float _tangent);



	class Factorials
	{
	public:

				Factorials(void) = default;


		static const float		evenFacts[6];
	};
}