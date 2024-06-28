#pragma once

#include "libmath/MathGeneric.hpp"

#include "libmath/Vector3.hpp"
#include "libmath/Vector2.hpp"

namespace ion::math
{
	// Linear interpolation between a start, an end and a ratio
	// between 0 and 1
	template <CScalarType TValueType> inline
	TValueType		Lerp(TValueType _low, TValueType _high, TValueType _ratio) noexcept;


	// Get the Lerp ratio from a lerp'd value and its bounds
	template <CScalarType TValueType> inline
	TValueType		InverseLerp(TValueType _val, TValueType _low, TValueType _high) noexcept;







// ---- Implementation ----

	template <CScalarType TValueType> inline
	TValueType Lerp(TValueType _low, TValueType _high, TValueType _ratio) noexcept
	{
		if (_ratio == 0.f)
			return _low;

		else if (_ratio == 1.f)
			return _high;

		// Use naive lerp formula
		return (static_cast<TValueType>(1) - _ratio) * _low + _ratio * _high;
	}


	template <CScalarType TValueType> inline
	TValueType InverseLerp(TValueType _val, TValueType _low, TValueType _high) noexcept
	{
		// Reverse lerp formula to get ratio (commonly referred to as t)
		return (_val - _low) / (_high - _low);
	}

}