#pragma once

#include "libmath/Angle.h"

#define MIN_COS		-1.f
#define MAX_COS		1.f


namespace ion::math
{
	// Compute cosine of an angle in radians using
	// 6 iterations of Taylor's series
	float		Cos(const Radian& _rad);

	// Compute sine using Cos with a pi / 2 offset
	float		Sin(const Radian& _rad);

	// Compute tan using sin / cos
	float		Tan(const Radian& _rad);

	// Inverse trigonometry

	Radian		Acos(float _cosine);
	Radian		Asin(float _sine);
	Radian		Atan(float _tangent);

	// Compute arctangent by dividing y by x
	// Note: can handle x being equal to 0
	Radian		Atan2(float _y, float _x);


	// Class made to hold factorials for cos
	class Factorials
	{
	public:

				Factorials(void) = default;


		static const float		m_evenFacts[6];
	};
}

namespace LibMath = ion::math;
namespace lm = ion::math;