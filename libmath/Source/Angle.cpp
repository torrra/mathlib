#include "libmath/Angle.h"

#include "libmath/Arithmetic.h"

namespace mth
{
	Degree::Degree(float _val)
		: m_value(_val) {}

	Degree::Degree(const Degree& _other)
		: m_value(_other.m_value) {}

	Degree::operator Radian()
	{
		// TODO: Re-implement
		return Radian(/*Rad(false)*/);
	}

	float Degree::Deg(bool _wrap180) const
	{
		if (_wrap180)
			return wrap(m_value, -180.f, 180.f);

		else
			return wrap(m_value, 0.f, 360.f);
	}

	float Degree::Rad(bool _wrapPi) const
	{
		if (_wrapPi)
			return wrap(m_value * DEG2RAD, -MTH_PI, MTH_PI);

		else
			return wrap(m_value * DEG2RAD, 0.f, RAD_CIRCLE);
	}

	float Degree::Raw(void) const
	{
		return m_value;
	}

	void Degree::Wrap(bool _wrap180)
	{
		m_value = Deg(_wrap180);
	}

	Degree mth::Literal::operator""_deg(long double _val)
	{
		return Degree(static_cast<float>(_val));
	}

	Degree Literal::operator""_deg(unsigned long long int _val)
	{
		return Degree(static_cast<float>(_val));
	}

}