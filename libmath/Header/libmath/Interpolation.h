#pragma once

#include "libmath/Vector3.h"
#include "libmath/Vector2.h"

namespace mth
{
	float		Lerp(float _low, float _high, float _ratio);

	float		InverseLerp(float _val, float _low, float _high);
}