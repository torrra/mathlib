#include "libmath/Interpolation.h"

namespace mth
{
	float Lerp(float _low, float _high, float _ratio)
	{
		if (_ratio == 0.f)
			return _low;

		else if (_ratio == 1.f)
			return _high;

		// Use naive lerp formula
		return (1.f - _ratio) * _low + _ratio * _high;
	}

	float InverseLerp(float _val, float _low, float _high)
	{
		// Reverse lerp formula to get ratio (commonly refered to as t)
		return (_val - _low) / (_high - _low);
	}

}