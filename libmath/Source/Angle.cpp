#include "libmath/Angle.h"

#include "libmath/Arithmetic.h"

#define DEG_PRECISION		1.f
#define RAD_PRECISION		0.0001f

namespace mth
{
	Degree::Degree(float _val)
		: m_value(_val) {}

	Degree::Degree(const Degree& _other)
		: m_value(_other.m_value) {}

	Degree::operator Radian() const
	{
		return Radian(Rad(false));
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

	Degree& Degree::operator=(const Degree& _rhs)
	{
		m_value = _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator=(float _rhs)
	{
		m_value = _rhs;

		return *this;
	}

	Degree Degree::operator+(const Degree& _rhs) const
	{
		return Degree(m_value + _rhs.m_value);
	}

	Degree Degree::operator-(const Degree& _rhs) const
	{
		return Degree(m_value - _rhs.m_value);
	}

	Degree Degree::operator*(const Degree& _rhs) const
	{
		return Degree(m_value * _rhs.m_value);
	}

	Degree Degree::operator/(const Degree& _rhs) const
	{
		return Degree(m_value / _rhs.m_value);
	}

	Degree Degree::operator+(float _rhs) const
	{
		return Degree(m_value + _rhs);
	}

	Degree Degree::operator-(float _rhs) const
	{
		return Degree(m_value - _rhs);
	}

	Degree Degree::operator*(float _rhs) const
	{
		return Degree(m_value * _rhs);
	}

	Degree Degree::operator/(float _rhs) const
	{
		return Degree(m_value / _rhs);
	}

	Degree& Degree::operator+=(const Degree& _rhs)
	{
		m_value += _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator-=(const Degree& _rhs)
	{
		m_value -= _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator*=(const Degree& _rhs)
	{
		m_value *= _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator/=(const Degree& _rhs)
	{
		m_value /= _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator+=(float _rhs)
	{
		m_value += _rhs;

		return *this;
	}

	Degree& Degree::operator-=(float _rhs)
	{
		m_value -= _rhs;

		return *this;
	}

	Degree& Degree::operator*=(float _rhs)
	{
		m_value *= _rhs;

		return *this;
	}

	Degree& Degree::operator/=(float _rhs)
	{
		m_value /= _rhs;

		return *this;
	}

	bool Degree::operator==(const Degree& _rhs) const
	{
		return almostEqual(m_value, _rhs.m_value, DEG_PRECISION);
	}

	bool Degree::operator!=(const Degree& _rhs) const
	{
		return !(*this == _rhs);
	}

	bool Degree::operator==(float _rhs) const
	{
		return almostEqual(m_value, _rhs, DEG_PRECISION);
	}

	bool Degree::operator!=(float _rhs) const
	{
		return !(*this == _rhs);
	}

	Degree mth::Literal::operator""_deg(long double _val)
	{
		return Degree(static_cast<float>(_val));
	}

	Degree Literal::operator""_deg(unsigned long long int _val)
	{
		return Degree(static_cast<float>(_val));
	}

	Radian Literal::operator""_rad(long double _val)
	{
		return Radian(static_cast<float>(_val));
	}

	Radian Literal::operator""_rad(unsigned long long int _val)
	{
		return Radian(static_cast<float>(_val));
	}

	Radian::Radian(float _val)
		: m_value(_val) {}

	Radian::Radian(const Radian & _other)
	: m_value(_other.m_value) {}

	Radian::operator Degree(void) const
	{
		return Degree(Deg(false));
	}

	float Radian::Deg(bool _wrap180) const
	{
		if (_wrap180)
			return wrap(m_value * RAD2DEG, -180.f, 180.f);

		else
			return wrap(m_value * RAD2DEG, 0.f, 360.f);
	}

	float Radian::Rad(bool _wrapPi) const
	{
		if (_wrapPi)
			return wrap(m_value, -MTH_PI, MTH_PI);

		else
			return wrap(m_value, 0.f, RAD_CIRCLE);
	}

	float Radian::Raw() const
	{
		return m_value;
	}

	void Radian::Wrap(bool _wrap180)
	{
		m_value = Deg(_wrap180);
	}

}