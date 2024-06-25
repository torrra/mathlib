#include <cmath>
#include <sstream>

#include "libmath/Vector2.h"
#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

#define MIN_COS		-1.f
#define MAX_COS		1.f

namespace ion::math
{
	Vector2::Vector2(float _val)
		: m_x(_val), m_y(_val) {}

	Vector2::Vector2(float _x, float _y)
		: m_x(_x), m_y(_y) {}

	Vector2::Vector2(const Vector2& _other)
		: m_x(_other.m_x), m_y(_other.m_y) {}

	Radian Vector2::AngleFrom(const Vector2& _other) const
	{
		float		magnitudes = MagnitudeSquared() * _other.MagnitudeSquared();

		// Only run square root once
		magnitudes = SquareRoot(magnitudes);

		// Transform dot product equation to get cos angle,
		// then run acos
		return Acos(Dot(_other) / magnitudes);
	}

	Radian Vector2::AngleFromUnit(const Vector2& _other) const
	{
		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}


	float Vector2::Cross(const Vector2& _other) const
	{
		// Only compute result for result's  z component as
		// both x and y will be zero for vec2 cross product
		return (m_x * _other.m_y) - (m_y * _other.m_x);
	}


	float Vector2::DistanceFrom(const Vector2& _other) const
	{
		return SquareRoot(DistanceSquaredFrom(_other));
	}


	float Vector2::DistanceSquaredFrom(const Vector2& _other) const
	{
		// Find distance vector and get magnitude
		return (_other - *this).MagnitudeSquared();
	}


	float Vector2::Dot(const Vector2& _other) const
	{
		// Multiply components
		return (m_x * _other.m_x) + (m_y * _other.m_y);
	}


	bool Vector2::IsLongerThan(const Vector2& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}


	bool Vector2::IsShorterThan(const Vector2& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}


	bool Vector2::IsUnitVector() const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	float Vector2::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}


	float Vector2::MagnitudeSquared() const
	{
		// Square components
		return Dot(*this);
	}

	void Vector2::Normalize()
	{
		float		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, 0.f, FLT_EPSILON))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		// Only divide once
		else
			invMagnitude = 1.f / invMagnitude;

		m_x *= invMagnitude;
		m_y *= invMagnitude;
	}

	Vector2 Vector2::Normalized(void) const
	{
		Vector2		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}

	Vector2 Vector2::Normal(void) const
	{
		// Swap x and y and flip one sign (y here)
		return Vector2(-m_y, m_x);
	}


	void Vector2::ProjectOnto(const Vector2& _other)
	{
		// Apply projection formula
		float		squareMagnitude = _other.MagnitudeSquared();
		float		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;

	}


	void Vector2::ReflectOnto(const Vector2& _axis)
	{
		// Only reflect onto unit vector
		Vector2		normal = ion::math::Normalize(_axis);

		// Apply reflection formula
		*this -= normal * (Dot(normal) * 2.f);
	}

	void Vector2::ReflectOntoUnit(const Vector2& _axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= _axis * (Dot(_axis) * 2.f);
	}


	void Vector2::Rotate(Radian _angle)
	{
		float		cosAngle = Cos(_angle),
					sinAngle = Sin(_angle);

		// Copy x as base x value is needed for
		// both x and y results
		float		xCopy = m_x;

		// Manually multiply by 2x2 rotation matrix
		m_x = cosAngle * xCopy - m_y * sinAngle;
		m_y = sinAngle * xCopy + m_y * cosAngle;
	}


	void Vector2::Scale(const Vector2& _other)
	{
		*this *= _other;
	}

	std::string Vector2::String() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << '}';

		return stream.str();
	}


	std::string Vector2::StringLong() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream with some extra
		stream << "Vector2{ x:" << m_x << ", y:" << m_y << " }";

		return stream.str();
	}


	void Vector2::Translate(const Vector2& _other)
	{
		*this += _other;
	}


	float& Vector2::X()
	{
		return m_x;
	}


	float& Vector2::Y()
	{
		return m_y;
	}


	float Vector2::GetX() const
	{
		return m_x;
	}

	float Vector2::GetY() const
	{
		return m_y;
	}



	Vector2& Vector2::operator=(const Vector2& _rhs)
	{
		// Copy assign
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;

		return *this;
	}

	float& Vector2::operator[](int _index)
	{
		switch (_index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		default:
			throw std::logic_error("Index out of range");
		}
	}

	float Vector2::operator[](int _index) const
	{
		switch (_index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		default:
			throw std::logic_error("Index out of range");
		}
	}

	bool Vector2::operator==(const Vector2& _rhs) const
	{
		// Compare both components
		return
		(
			AlmostEqual(m_x, _rhs.m_x) &&
			AlmostEqual(m_y, _rhs.m_y)
		);
	}


	bool Vector2::operator!=(const Vector2& _rhs) const
	{
		return !(*this == _rhs);
	}


	float Dot(const Vector2& _first, const Vector2& _second)
	{
		return _first.Dot(_second);
	}

	float Cross(const Vector2& _first, const Vector2& _second)
	{
		return _first.Cross(_second);
	}

	Vector2 Reflect(const Vector2& _target, const Vector2& _ontoNormal)
	{
		Vector2		result = _target;

		// Return reflected copy
		result.ReflectOnto(_ontoNormal);

		return result;
	}

	Vector2 ReflectUnit(const Vector2& _target, const Vector2& _ontoNormal)
	{
		Vector2		result = _target;

		// Return reflected copy
		result.ReflectOntoUnit(_ontoNormal);

		return result;
	}

	Vector2 Project(const Vector2& _target, const Vector2& _ontoVector)
	{
		Vector2		result = _target;

		// Return projected copy
		result.ProjectOnto(_ontoVector);

		return result;
	}


	Vector2 Normalize(const Vector2& _target)
	{
		Vector2		result = _target;

		// Return normalized copy
		result.Normalize();

		return result;
	}

	float Distance(const Vector2& _start, const Vector2& _end)
	{
		return _start.DistanceFrom(_end);
	}

	float DistanceSquared(const Vector2& _start, const Vector2& _end)
	{
		return _start.DistanceSquaredFrom(_end);
	}

	Vector2 Rotate(const Vector2& _target, Radian _angle)
	{
		Vector2		result = _target;

		// Return rotated copy
		result.Rotate(_angle);

		return result;
	}


	// Component-wise operators

	Vector2 Vector2::operator+(const Vector2& _rhs) const
	{
		return Vector2(m_x + _rhs.m_x, m_y + _rhs.m_y);
	}

	Vector2 Vector2::operator-(const Vector2& _rhs) const
	{
		return Vector2(m_x - _rhs.m_x, m_y - _rhs.m_y);
	}


	Vector2 Vector2::operator*(const Vector2& _rhs) const
	{
		return Vector2(m_x * _rhs.m_x, m_y * _rhs.m_y);
	}

	Vector2 Vector2::operator/(const Vector2& _rhs) const
	{
		return Vector2(m_x /_rhs.m_x, m_y / _rhs.m_y);
	}


	Vector2 Vector2::operator*(float _rhs) const
	{
		return Vector2(m_x * _rhs, m_y * _rhs);
	}

	Vector2 Vector2::operator/(float _rhs) const
	{
		_rhs = 1.f / _rhs;

		return Vector2(m_x * _rhs, m_y * _rhs);
	}

	Vector2 Vector2::operator-(void) const
	{
		return Vector2(-m_x, -m_y);
	}

	Vector2& Vector2::operator+=(const Vector2& _rhs)
	{
		m_x += _rhs.m_x;
		m_y += _rhs.m_y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& _rhs)
	{
		m_x -= _rhs.m_x;
		m_y -= _rhs.m_y;

		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& _rhs)
	{
		m_x *= _rhs.m_x;
		m_y *= _rhs.m_y;

		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& _rhs)
	{
		m_x /= _rhs.m_x;
		m_y /= _rhs.m_y;

		return* this;
	}

	Vector2& Vector2::operator*=(float _rhs)
	{
		m_x *= _rhs;
		m_y *= _rhs;

		return *this;
	}

	Vector2& Vector2::operator/=(float _rhs)
	{
		_rhs = 1.f / _rhs;

		m_x *= _rhs;
		m_y *= _rhs;

		return *this;
	}

	// !Component-wise operators


	// Constants

	Vector2 Vector2::Zero(void)
	{
		return Vector2();
	}


	Vector2 Vector2::One(void)
	{
		return Vector2(1.f, 1.f);
	}

	Vector2 Vector2::Up(void)
	{
		return Vector2(0.f, 1.f);
	}

	Vector2 Vector2::Down(void)
	{
		return Vector2(0.f, -1.f);
	}

	Vector2 Vector2::Left(void)
	{
		return Vector2(-1.f, 0.f);
	}

	Vector2 Vector2::Right(void)
	{
		return Vector2(1.f, 0.f);
	}

	// !Constants


	std::ostream& operator<<(std::ostream& _os, Vector2 const& _vector)
	{
		// Pass components to stream
		_os << '{' << _vector.GetX() << ',' << _vector.GetY() << '}';

		return _os;
	}

	std::istream& operator>>(std::istream& _is, Vector2& _vector)
	{
		char	discard;

		// Get input from stream
		_is >> discard >> _vector.X() >> discard >> _vector.Y() >> discard;

		return _is;
	}



}