#pragma once

#include "libmath/Vector3.hpp"
#include "libmath/Vector2.hpp"

namespace ion::math
{
	// Linear interpolation bewtween a start, an end and a ratio
	// between 0 and 1
	float		Lerp(float _low, float _high, float _ratio);


	// Get the Lerp ratio from a lerp'ed value and its bounds
	float		InverseLerp(float _val, float _low, float _high);
}