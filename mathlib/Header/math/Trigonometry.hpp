#ifndef __TRIGONOMETRY_H__
#define __TRIGONOMETRY_H__

#include <cmath>

#include "Angle.hpp"

// Number of times cos should run its loop
#define COS_IT		6u

#define MIN_COS		-1.f
#define MAX_COS		1.f


namespace math
{
	// Compute cosine of an angle in radians using
	// 6 iterations of Taylor's series
	template <CScalarType TValueType> inline
	TValueType		Cos(const Radian<TValueType>& rad);

	// Compute sine using Cos with a pi / 2 offset
	template <CScalarType TValueType> inline
	TValueType		Sin(const Radian<TValueType>& rad);

	// Compute tan using sin / cos
	template <CScalarType TValueType> inline
	TValueType		Tan(const Radian<TValueType>& rad);

	// Inverse trigonometry

	template <CScalarType TValueType> inline
	Radian<TValueType>		Acos(TValueType cosine);

	template <CScalarType TValueType> inline
	Radian<TValueType>		Asin(TValueType sine);

	template <CScalarType TValueType> inline
	Radian<TValueType>		Atan(TValueType tangent);

	// Compute arctangent by dividing y by x
	// Note: can handle x being equal to 0
	template <CScalarType TValueType> inline
	Radian<TValueType>		Atan2(TValueType y, TValueType x);


	// Class made to hold factorials for cos
	template <CScalarType TValueType>
	class Factorials
	{
	public:

				Factorials(void) = default;


		static const TValueType		m_evenFacts[6];
	};









	// Cos specifically made for sin to avoid constructing another Radian object
	template <CScalarType TValueType> inline
	static TValueType InternalCos(TValueType val)
	{
		TValueType	  powResult, cosResult = 0.f, itResult;

		// Wrap angle between -pi and pi as 6 iterations of
		// Taylor's series get less accurate as the angle approaches
		// -2 pi or +2pi
		TValueType	  radians = Wrap(val, -MTH_PI, MTH_PI);


		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			// Get numerator, angle raised to the power of
			// an even number
			powResult = Pow(radians, it * 2);

			// Divide result by factorial of said power * sign
			itResult = powResult * math::Factorials<TValueType>::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult;

		return cosResult;
	}

	template <CScalarType TValueType> inline
	static TValueType AtanZeroX(TValueType y)
	{
		// Return 90 degrees * sign of y

		if (y > 0.f)
			return PI_OVER_TWO;

		else if (y < 0.f)
			return -PI_OVER_TWO;

		return 0.f;
	}


	template <CScalarType TValueType> inline
	TValueType Cos(const Radian<TValueType>& rad)
	{
#ifdef MY_TRIG_IMPL
		// Wrap angle between -pi and pi as 6 iterations of
		// Taylor's series get less accurate as the angle approaches
		// -2 pi or +2pi
		TValueType	radians = rad.Rad(true);
		TValueType	powResult, cosResult = 0.f, itResult;

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			// Get numerator, angle raised to the power of
			// an even number
			powResult = Pow(radians, it * 2);

			// Divide result by factorial of said power * sign
			itResult = powResult * math::Factorials<TValueType>::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult;

		return cosResult;
#else
		return cos(rad.Raw());
#endif
	}


	template <CScalarType TValueType> inline
	TValueType Sin(const Radian<TValueType>& rad)
	{
#ifdef MY_TRIG_IMPL
		// Apply 90 degree offset
		// See: https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/1920px-Sine_cosine_one_period.svg.png
		constexpr TValueType		piOverTwo = 1.570796326794896619231f;

		// cos x == cos -x so get absolute value of angle to apply offset easily
		TValueType				cosine = InternalCos(Absolute(rad.Raw()) - piOverTwo);


		// Restore sign of angle as sine is an odd function,
		// which means sin -x == -sinx
		if (rad.Raw() < 0.f)
			return -cosine;

		else return cosine;

		// TODO: optimize
#else
		return sin(rad.Raw());
#endif
	}


	template <CScalarType TValueType> inline
	TValueType Tan(const Radian<TValueType>& rad)
	{
#ifdef MY_TRIG_IMPL
		// tan x = sin x / cos x
		return Sin(rad) / Cos(rad);
#else
		return tan(rad.Raw());
#endif
		// TODO: needs to be faster
	}

	// TODO: re-implement my own inverse trig functions

	template <CScalarType TValueType> inline
	Radian<TValueType> Acos(TValueType cosine)
	{
		return Radian(acos(cosine));
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Asin(TValueType sine)
	{
		return Radian(asin(sine));
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Atan(TValueType tangent)
	{
		return Radian(atan(tangent));
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Atan2(TValueType y, TValueType x)
	{
		// Handle x == 0 case
		if (AlmostEqual(x, 0.0f))
			return Radian(AtanZeroX(y));


		Radian		angle = Atan(y / x);

		// Find quadrant of point within trigonometric circle
		// and add offset to get correct angle

		if (x >= 0.f && y <= 0.f)
			angle += RAD_CIRCLE;

		else if (x < 0.f && y <= 0.f)
			angle += MTH_PI;

		else if (x < 0.f && y > 0.f)
			angle += MTH_PI;

		return angle;
	}


	template <CScalarType TValueType> inline
	const TValueType math::Factorials<TValueType>::m_evenFacts[] =
	{
		// Pre-compute even factorials and divisions
		// for faster cosine execution
		1.f / static_cast<TValueType>(Factorial(2)),
		-1.f / static_cast<TValueType>(Factorial(4)),
		1.f / static_cast<TValueType>(Factorial(6)),
		-1.f / static_cast<TValueType>(Factorial(8)),
		1.f / static_cast<TValueType>(Factorial(10)),
		-1.f / static_cast<TValueType>(Factorial(12))
	};




}

namespace LibMath = math;
namespace lm = math;

#endif