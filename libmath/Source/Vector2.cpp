#include <cmath>
#include <sstream>

#include "libmath/Vector2.h"
#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

#define MIN_COS		-1.f
#define MAX_COS		1.f

namespace mth
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

		magnitudes = SquareRoot(magnitudes);


		return Acos(Dot(_other) / magnitudes);
	}

	Radian Vector2::AngleFromUnit(const Vector2& _other) const
	{
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}


	float Vector2::Cross(const Vector2& _other) const
	{
		return (m_x * _other.m_y) - (m_y * _other.m_x);
	}


	float Vector2::DistanceFrom(const Vector2& _other) const
	{
		return SquareRoot(DistanceSquaredFrom(_other));
	}


	float Vector2::DistanceSquaredFrom(const Vector2& _other) const
	{
		return (_other - *this).MagnitudeSquared();
	}


	float Vector2::Dot(const Vector2& _other) const
	{
		return (m_x * _other.m_x) + (m_y * _other.m_y);
	}


	bool Vector2::IsLongerThan(const Vector2& _other) const
	{
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}


	bool Vector2::IsShorterThan(const Vector2& _other) const
	{
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}


	bool Vector2::IsUnitVector() const
	{
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	float Vector2::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}


	float Vector2::MagnitudeSquared() const
	{
		return Dot(*this);
	}

	void Vector2::Normalize()
	{
		float		invMagnitude = 1.f / Magnitude();

		m_x *= invMagnitude;
		m_y *= invMagnitude;
	}

	Vector2 Vector2::Normalized(void) const
	{
		Vector2		result = *this;

		result.Normalize();

		return result;
	}


	void Vector2::ProjectOnto(const Vector2& _other)
	{

		float		squareMagnitude = _other.MagnitudeSquared();
		float		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;

	}


	void Vector2::ReflectOnto(const Vector2& _axis)
	{
		Vector2		normal = mth::Normalize(_axis);

		*this -= normal * (Dot(normal) * 2.f);
	}

	void Vector2::ReflectOntoUnit(const Vector2& _axis)
	{
		*this -= _axis * (Dot(_axis) * 2.f);
	}


	void Vector2::Rotate(Radian _angle)
	{
		float		cosAngle = Cos(_angle), sinAngle = Sin(_angle);
		float		xCopy = m_x;


		m_x = cosAngle * xCopy - m_y * sinAngle;
		m_y = sinAngle * xCopy + m_y * cosAngle;
	}


	void Vector2::Scale(const Vector2& _other)
	{
		*this *= _other;
	}

	std::string Vector2::String() const
	{
		std::stringstream		stream;

		stream << '{' << m_x << ',' << m_y << '}';

		return stream.str();
	}


	std::string Vector2::StringLong() const
	{
		std::stringstream		stream;

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
		default:
			return m_y;
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
			return 0.f;
		}
	}

	bool Vector2::operator==(const Vector2& _rhs) const
	{
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

		result.ReflectOnto(_ontoNormal);

		return result;
	}

	Vector2 ReflectUnit(const Vector2& _target, const Vector2& _ontoNormal)
	{
		Vector2		result = _target;

		result.ReflectOntoUnit(_ontoNormal);

		return result;
	}

	Vector2 Project(const Vector2& _target, const Vector2& _ontoVector)
	{
		Vector2		result = _target;

		result.ProjectOnto(_ontoVector);

		return result;
	}


	Vector2 Normalize(const Vector2& _target)
	{
		Vector2		result = _target;

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

		result.Rotate(_angle);

		return result;
	}

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



	std::ostream& operator<<(std::ostream& _os, Vector2 const& _vector)
	{
		_os << '{' << _vector.GetX() << ',' << _vector.GetY() << '}';

		return _os;
	}

	std::istream& operator>>(std::istream& _is, Vector2& _vector)
	{
		char	discard;

		_is >> discard >> _vector.X() >> discard >> _vector.Y() >> discard;

		return _is;
	}



}