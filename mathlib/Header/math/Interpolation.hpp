#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__

#include "MathGeneric.hpp"

#include "Vector3.hpp"
#include "Vector2.hpp"

namespace math
{
	// Linear interpolation between a start, an end and a ratio
	// between 0 and 1
	template <CScalarType TValueType> inline
	TValueType		Lerp(TValueType low, TValueType high, TValueType ratio) noexcept;


	// Get the Lerp ratio from a lerp'd value and its bounds
	template <CScalarType TValueType> inline
	TValueType		InverseLerp(TValueType val, TValueType low, TValueType high) noexcept;







// ---- Implementation ----

	template <CScalarType TValueType> inline
	TValueType Lerp(TValueType low, TValueType high, TValueType ratio) noexcept
	{
		if (ratio == 0.f)
			return low;

		else if (ratio == 1.f)
			return high;

		// Use naive lerp formula
		return (static_cast<TValueType>(1) - ratio) * low + ratio * high;
	}


	template <CScalarType TValueType> inline
	TValueType InverseLerp(TValueType val, TValueType low, TValueType high) noexcept
	{
		// Reverse lerp formula to get ratio (commonly referred to as t)
		return (val - low) / (high - low);
	}

}


#endif