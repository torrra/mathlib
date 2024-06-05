#include "libmath/Angle.h"

#include "libmath/Arithmetic.h"

#define DEG_PRECISION		1.f
#define RAD_PRECISION		0.0001f

#define HALF_CIRCLE_DEG		180.f
#define FULL_CIRCLE_DEG		360.f

namespace mth
{
	Degree::Degree(float _val)
		: m_value(_val) {}

	Degree::Degree(const Degree& _other)
		: m_value(_other.m_value) {}

	Degree::operator Radian() const
	{
		// Convert deg value to rad
		return Radian(Rad(false));
	}

	float Degree::Deg(bool _wrap180) const
	{
		// Wrap value depending on argument

		if (_wrap180)
			return mth::Wrap(m_value, -HALF_CIRCLE_DEG, HALF_CIRCLE_DEG);

		else
			return mth::Wrap(m_value, 0.f, FULL_CIRCLE_DEG);
	}

	float Degree::Rad(bool _wrapPi) const
	{
		// Wrap value depending on argument

		if (_wrapPi)
			return mth::Wrap(m_value * DEG2RAD, -MTH_PI, MTH_PI);

		else
			return mth::Wrap(m_value * DEG2RAD, 0.f, RAD_CIRCLE);
	}

	float Degree::Raw(void) const
	{
		return m_value;
	}

	void Degree::Wrap(bool _wrap180)
	{
		// Assign wrapped value to raw value
		m_value = Deg(_wrap180);
	}

	Degree& Degree::operator=(const Degree& _rhs)
	{
		// Copy assignment

		m_value = _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator=(float _rhs)
	{
		// Copy assignment

		m_value = _rhs;

		return *this;
	}

	Degree Degree::operator+(const Degree& _rhs) const
	{
		// Addition

		return Degree(m_value + _rhs.m_value);
	}

	Degree Degree::operator-(const Degree& _rhs) const
	{
		// Subtraction

		return Degree(m_value - _rhs.m_value);
	}

	Degree Degree::operator*(const Degree& _rhs) const
	{
		// Multiplication

		return Degree(m_value * _rhs.m_value);
	}

	Degree Degree::operator/(const Degree& _rhs) const
	{
		// Division

		return Degree(m_value / _rhs.m_value);
	}

	Degree Degree::operator+(float _rhs) const
	{
		// Addition

		return Degree(m_value + _rhs);
	}

	Degree Degree::operator-(float _rhs) const
	{
		// Subtraction

		return Degree(m_value - _rhs);
	}

	Degree Degree::operator*(float _rhs) const
	{
		// Multiplication
		return Degree(m_value * _rhs);
	}

	Degree Degree::operator/(float _rhs) const
	{
		// Division
		return Degree(m_value / _rhs);
	}

	Degree& Degree::operator+=(const Degree& _rhs)
	{
		// Addition assignment

		m_value += _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator-=(const Degree& _rhs)
	{
		// Subtraction assignment

		m_value -= _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator*=(const Degree& _rhs)
	{
		// Multiplication assignment

		m_value *= _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator/=(const Degree& _rhs)
	{
		// Division assignment

		m_value /= _rhs.m_value;

		return *this;
	}

	Degree& Degree::operator+=(float _rhs)
	{
		// Addition assignment

		m_value += _rhs;

		return *this;
	}

	Degree& Degree::operator-=(float _rhs)
	{
		// Subtraction assignment

		m_value -= _rhs;

		return *this;
	}

	Degree& Degree::operator*=(float _rhs)
	{
		// Multiplication assignment

		m_value *= _rhs;

		return *this;
	}

	Degree& Degree::operator/=(float _rhs)
	{
		// Division assignment

		m_value /= _rhs;

		return *this;
	}

	Degree Degree::operator-(void) const
	{
		// Flip sign

		return Degree(-m_value);
	}

	bool Degree::operator==(const Degree& _rhs) const
	{
		return AlmostEqual
		(
			Deg(false),
			_rhs.Deg(false),
			DEG_PRECISION
		);
	}

	bool Degree::operator!=(const Degree& _rhs) const
	{
		// Not equal
		return !(*this == _rhs);
	}

	bool Degree::operator==(float _rhs) const
	{
		return AlmostEqual
		(
			Deg(false),
			_rhs,
			DEG_PRECISION
		);
	}

	bool Degree::operator!=(float _rhs) const
	{
		// Not equal
		return !(*this == _rhs);
	}

	Degree mth::Literal::operator""_deg(long double _val)
	{
		// Get numeric value from literal
		return Degree(static_cast<float>(_val));
	}

	Degree Literal::operator""_deg(unsigned long long int _val)
	{
		// Get numeric value from literal
		return Degree(static_cast<float>(_val));
	}

	Radian Literal::operator""_rad(long double _val)
	{
		// Get numeric value from literal
		return Radian(static_cast<float>(_val));
	}

	Radian Literal::operator""_rad(unsigned long long int _val)
	{
		// Get numeric value from literal
		return Radian(static_cast<float>(_val));
	}

	Radian::Radian(float _val)
		: m_value(_val) {}

	Radian::Radian(const Radian & _other)
	: m_value(_other.m_value) {}

	Radian::operator Degree(void) const
	{
		// Converti value to radians and construct object
		return Degree(Deg(false));
	}

	float Radian::Deg(bool _wrap180) const
	{
		// Wrap value depending on argument
		if (_wrap180)
			return mth::Wrap(m_value * RAD2DEG, -HALF_CIRCLE_DEG, HALF_CIRCLE_DEG);

		else
			return mth::Wrap(m_value * RAD2DEG, 0.f, FULL_CIRCLE_DEG);
	}

	float Radian::Rad(bool _wrapPi) const
	{
		// Use custom wrap as libmath wrap is not precise enough

		// Treat value as positive
		float			absValue = Absolute(m_value);

		// Wrap around unit circle
		if (absValue >= RAD_CIRCLE)
		{
			float	circleCount = Floor(absValue / RAD_CIRCLE);

			absValue -= circleCount * RAD_CIRCLE;
		}

		// Wrap again if range is -pi, pi
		if (_wrapPi)
		{
			if (absValue >= MTH_PI)
				absValue -= RAD_CIRCLE;

			// Restore sign
			if (m_value < 0.f && absValue > 0.f)
				absValue = -absValue;

		}

		// Add negative value to circle if range is 0, 2pi
		else if (m_value < 0.f)
		{
			absValue = RAD_CIRCLE - absValue;
		}

		return absValue;


	}

	float Radian::Raw() const
	{
		return m_value;
	}

	void Radian::Wrap(bool _wrap180)
	{
		// Set raw value to wrapped value
		m_value = Rad(_wrap180);
	}

	Radian& Radian::operator=(const Radian& _rhs)
	{
		// Copy assignment

		m_value = _rhs.m_value;

		return *this;
	}

	Radian& Radian::operator=(float _rhs)
	{
		// Copy assignment

		m_value = _rhs;

		return *this;
	}

	Radian Radian::operator+(const Radian& _rhs) const
	{
		// Addition

		return Radian(m_value + _rhs.m_value);
	}

	Radian Radian::operator-(const Radian& _rhs) const
	{
		// Subtraction
		return Radian(m_value - _rhs.m_value);
	}

	Radian Radian::operator*(const Radian& _rhs) const
	{
		// Multiplication
		return Radian(m_value * _rhs.m_value);
	}

	Radian Radian::operator/(const Radian& _rhs) const
	{
		// Division
		return Radian(m_value / _rhs.m_value);
	}

	Radian& Radian::operator+=(const Radian& _rhs)
	{
		// Addition assignment
		m_value += _rhs.m_value;

		return *this;
	}

	Radian& Radian::operator-=(const Radian& _rhs)
	{
		// Subtraction assignment
		m_value -= _rhs.m_value;

		return *this;
	}

	Radian& Radian::operator*=(const Radian& _rhs)
	{
		// Multiplication assignment
		m_value *= _rhs.m_value;

		return *this;
	}

	Radian& Radian::operator/=(const Radian& _rhs)
	{
		// Division assignment
		m_value /= _rhs.m_value;

		return *this;
	}

	Radian Radian::operator+(float _rhs) const
	{
		// Addition
		return Radian(m_value + _rhs);
	}

	Radian Radian::operator-(float _rhs) const
	{
		// Subtraction
		return Radian(m_value - _rhs);
	}

	Radian Radian::operator*(float _rhs) const
	{
		// Multiplication
		return Radian(m_value * _rhs);
	}

	Radian Radian::operator/(float _rhs) const
	{
		// Divition
		return Radian(m_value / _rhs);
	}

	Radian& Radian::operator+=(float _rhs)
	{
		// Addition assignment
		m_value += _rhs;

		return *this;
	}

	Radian& Radian::operator-=(float _rhs)
	{
		// Subtrction assignment
		m_value -= _rhs;

		return *this;
	}

	Radian& Radian::operator*=(float _rhs)
	{
		// Multiplication assignment
		m_value *= _rhs;

		return *this;
	}

	Radian& Radian::operator/=(float _rhs)
	{
		// Division assignment
		m_value /= _rhs;

		return *this;
	}

	Radian Radian::operator-(void) const
	{
		// Flip sign
		return Radian(-m_value);
	}

	bool Radian::operator==(const Radian& _rhs) const
	{
		return AlmostEqual
		(
			Rad(false),
			_rhs.Rad(false),
			RAD_PRECISION
		);
	}


	bool Radian::operator!=(const Radian& _rhs) const
	{
		// Not equal
		return !(*this == _rhs);
	}

	bool Radian::operator==(float _rhs) const
	{
		return AlmostEqual
		(
			Rad(false),
			_rhs,
			RAD_PRECISION
		);
	}

	bool Radian::operator!=(float _rhs) const
	{
		// Not equal
		return !(*this == _rhs);
	}


}