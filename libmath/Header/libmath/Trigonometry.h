#pragma once

#include "libmath/Angle.h"

namespace mth
{
	float  cos(const Radian& _rad, unsigned int _maxIterations = 6);

	float  sin(const Radian& _rad, unsigned int _maxIterations = 6);

	float  tan(const Radian& _rad, unsigned int _maxIterations = 6);


	Radian acos(float _cosine);
	Radian asin(float _sine);
	Radian atan(float _tangent);

	Radian atan2(float _tangent);



	class Factorials
	{
	public:
		Factorials(void) = default;

		static const float evenFacts[6];
		static const float oddFacts[6];
	};
}