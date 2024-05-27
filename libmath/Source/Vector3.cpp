#include <cmath>
#include <sstream>

#include "libmath/Matrix3.h"
#include "libmath/Matrix4.h"
#include "libmath/Vector3.h"
#include "libmath/Vector2.h"
#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"

#define MIN_COS		-1.f
#define MAX_COS		1.f

namespace mth
{
	Vector3::Vector3(float _val)
		: m_x(_val), m_y(_val), m_z(_val) {}

	Vector3::Vector3(float _x, float _y, float _z)
		: m_x(_x), m_y(_y), m_z(_z) {}

	Vector3::Vector3(const Vector3& _other)
		: m_x(_other.m_x), m_y(_other.m_y), m_z(_other.m_z) {}

	Radian Vector3::AngleFrom(const Vector3& _other) const
	{

		float		magnitudes = MagnitudeSquared() * _other.MagnitudeSquared();

		magnitudes = SquareRoot(magnitudes);


		return Acos(Dot(_other) / magnitudes);
	}

	Radian Vector3::AngleFromUnit(const Vector3& _other) const
	{
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}


	Vector3 Vector3::Cross(const Vector3& _other) const
	{
		// TODO: 3d
		return Vector3
		(
			(m_y * _other.m_z) - (m_z * _other.m_y),
			(m_z * _other.m_x) - (m_x * _other.m_z),
			(m_x * _other.m_y) - (m_y * _other.m_x)
		);

	}

	float Vector3::DistanceFrom(const Vector3& _other) const
	{
		return SquareRoot(DistanceSquaredFrom(_other));
	}


	float Vector3::DistanceSquaredFrom(const Vector3& _other) const
	{
		return (_other - *this).MagnitudeSquared();
	}

	float Vector3::Distance2DFrom(const Vector3& _other) const
	{
		return SquareRoot(Distance2DSquaredFrom(_other));
	}

	float Vector3::Distance2DSquaredFrom(const Vector3& _other) const
	{
		Vector2 dist2D =
		{
			_other.m_x - m_x,
			_other.m_y - m_y
		};

		return dist2D.MagnitudeSquared();
	}


	float Vector3::Dot(const Vector3& _other) const
	{
		return (m_x * _other.m_x) + (m_y * _other.m_y) + (m_z * _other.m_z);
	}


	bool Vector3::IsLongerThan(const Vector3& _other) const
	{
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}


	bool Vector3::IsShorterThan(const Vector3& _other) const
	{
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}


	bool Vector3::IsUnitVector() const
	{
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	float Vector3::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}


	float Vector3::MagnitudeSquared() const
	{
		return Dot(*this);
	}

	void Vector3::Normalize()
	{
		float		invMagnitude = 1.f / Magnitude();

		m_x *= invMagnitude;
		m_y *= invMagnitude;
		m_z *= invMagnitude;
	}

	Vector3 Vector3::Normalized(void) const
	{
		Vector3		result = *this;

		result.Normalize();

		return result;
	}


	void Vector3::ProjectOnto(const Vector3& _other)
	{

		float		squareMagnitude = _other.MagnitudeSquared();
		float		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;
		m_z = _other.m_z * projFactor;

	}


	void Vector3::ReflectOnto(const Vector3& _axis)
	{
		Vector3		normal = mth::Normalize(_axis);

		*this -= normal * (Dot(normal) * 2.f);
	}

	void Vector3::ReflectOntoUnit(const Vector3& _axis)
	{
		*this -= _axis * (Dot(_axis) * 2.f);
	}


	void Vector3::Rotate(Radian _angleX, Radian _angleY, Radian _angleZ)
	{
		Vector3		copy = *this;

		float		cosYaw = Cos(_angleZ), sinYaw = Sin(_angleZ);
		float		cosPitch = Cos(_angleX), sinPitch = Sin(_angleX);
		float		cosRoll = Cos(_angleY), sinRoll = Sin(_angleY);


		float		rotation[][3] =
		{
			{
				cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
				-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
				sinYaw * cosPitch
			},


			{
				sinRoll * cosPitch,
				cosRoll * cosPitch,
				-sinPitch
			},


			{
				-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
				sinRoll* sinYaw + cosYaw * sinPitch * cosRoll,
				cosYaw* cosPitch
			}
		};

		Matrix3		rotMatrix(rotation);


		*this = rotMatrix * copy;



	}

	void Vector3::Rotate(Radian _angle, const Vector3& _axis)
	{
		const Vector3		normalizedAxis = mth::Normalize(_axis);
		const float			xCpy = m_x, yCpy = m_y, zCpy = m_z;

		// lib math trig functions are not precise enough,
		// use the standard ones instead :(
		const float			cosAngle = std::cos(_angle.Raw());
		const float			sinAngle = std::sin(_angle.Raw());

		const float			oneMinCos = 1.f - cosAngle;

		// Perform matrix multiplication
		float				factorX = cosAngle + normalizedAxis.m_x *
									  normalizedAxis.m_x * oneMinCos;

		float				factorY = normalizedAxis.m_x * normalizedAxis.m_y *
									  oneMinCos - normalizedAxis.m_z * sinAngle;
		float				factorZ = normalizedAxis.m_x * normalizedAxis.m_z *
									  oneMinCos + normalizedAxis.m_y * sinAngle;

		m_x = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = normalizedAxis.m_y * normalizedAxis.m_x *
				  oneMinCos + normalizedAxis.m_z * sinAngle;

		factorY = cosAngle + normalizedAxis.m_y *
				  normalizedAxis.m_y * oneMinCos;

		factorZ = normalizedAxis.m_y * normalizedAxis.m_z *
			      oneMinCos - normalizedAxis.m_x * sinAngle;

		m_y = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = normalizedAxis.m_z * normalizedAxis.m_x *
				  oneMinCos - normalizedAxis.m_y * sinAngle;

		factorY = normalizedAxis.m_z * normalizedAxis.m_y *
				  oneMinCos + normalizedAxis.m_x * sinAngle;

		factorZ = cosAngle + normalizedAxis.m_z *
				  normalizedAxis.m_z * oneMinCos;

		m_z = xCpy * factorX + yCpy * factorY + factorZ * zCpy;
	}


	void Vector3::Scale(const Vector3& _other)
	{
		*this *= _other;
	}

	std::string Vector3::String() const
	{
		std::stringstream		stream;

		stream << '{' << m_x << ',' << m_y << ',' << m_z << '}';

		return stream.str();
	}


	std::string Vector3::StringLong() const
	{
		std::stringstream		stream;

		stream << "Vector3{ x:" << m_x << ", y:" << m_y << ", z:" << m_z << " }";

		return stream.str();
	}


	void Vector3::Translate(const Vector3& _other)
	{
		*this += _other;
	}


	float& Vector3::X()
	{
		return m_x;
	}


	float& Vector3::Y()
	{
		return m_y;
	}

	float& Vector3::Z()
	{
		return m_z;
	}


	float Vector3::GetX() const
	{
		return m_x;
	}

	float Vector3::GetY() const
	{
		return m_y;
	}


	float Vector3::GetZ() const
	{
		return m_z;
	}


	Vector3& Vector3::operator=(const Vector3& _rhs)
	{
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;
		m_z = _rhs.m_z;

		return *this;
	}

	float& Vector3::operator[](int _index)
	{
		switch (_index)
		{
		case 0:
			return m_x;
		case 1:
			return m_y;
		case 2:
			return m_z;
		default:
			throw std::logic_error("Vector index out of range");
		}
	}

	float Vector3::operator[](int _index) const
	{
		switch (_index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		case 2:
			return m_z;

		default:
			throw std::logic_error("Vector index out of range");
		}
	}


	bool Vector3::operator==(const Vector3& _rhs) const
	{
		return
		(
			AlmostEqual(m_x, _rhs.m_x) &&
			AlmostEqual(m_y, _rhs.m_y) &&
			AlmostEqual(m_z, _rhs.m_z)
		);
	}


	bool Vector3::operator!=(const Vector3& _rhs) const
	{
		return !(*this == _rhs);
	}


	float Dot(const Vector3& _first, const Vector3& _second)
	{
		return _first.Dot(_second);
	}

	Vector3 Cross(const Vector3& _first, const Vector3& _second)
	{
		return _first.Cross(_second);
	}

	Vector3 Reflect(const Vector3& _target, const Vector3& _ontoNormal)
	{
		Vector3		result = _target;

		result.ReflectOnto(_ontoNormal);

		return result;
	}

	Vector3 ReflectUnit(const Vector3& _target, const Vector3& _ontoNormal)
	{
		Vector3		result = _target;

		result.ReflectOntoUnit(_ontoNormal);

		return result;
	}

	Vector3 Project(const Vector3& _target, const Vector3& _ontoVector)
	{
		Vector3		result = _target;

		result.ProjectOnto(_ontoVector);

		return result;
	}


	Vector3 Normalize(const Vector3& _target)
	{
		Vector3		result = _target;

		result.Normalize();

		return result;
	}

	float Distance(const Vector3& _start, const Vector3& _end)
	{
		return _start.DistanceFrom(_end);
	}

	float DistanceSquared(const Vector3& _start, const Vector3& _end)
	{
		return _start.DistanceSquaredFrom(_end);
	}

	Vector3 Rotate(const Vector3& _target, Radian _x, Radian _y, Radian _z)
	{
		Vector3		result = _target;

		result.Rotate(_x, _y, _z);

		return result;
	}

	Vector3 Rotate(const Vector3& _target, Radian _angle, const Vector3& _axis)
	{
		Vector3		result = _target;

		result.Rotate(_angle, _axis);

		return result;
	}

	Vector3 Vector3::operator+(const Vector3& _rhs) const
	{
		return Vector3(m_x + _rhs.m_x, m_y + _rhs.m_y, m_z + _rhs.m_z);
	}

	Vector3 Vector3::operator-(const Vector3& _rhs) const
	{
		return Vector3(m_x - _rhs.m_x, m_y - _rhs.m_y, m_z - _rhs.m_z);
	}


	Vector3 Vector3::operator*(const Vector3& _rhs) const
	{
		return Vector3(m_x * _rhs.m_x, m_y * _rhs.m_y, m_z * _rhs.m_z);
	}

	Vector3 Vector3::operator/(const Vector3& _rhs) const
	{
		return Vector3(m_x / _rhs.m_x, m_y / _rhs.m_y, m_z / _rhs.m_z);
	}


	Vector3 Vector3::operator*(float _rhs) const
	{
		return Vector3(m_x * _rhs, m_y * _rhs, m_z * _rhs);
	}

	Vector3 Vector3::operator/(float _rhs) const
	{
		_rhs = 1.f / _rhs;

		return Vector3(m_x * _rhs, m_y * _rhs, m_z / _rhs);
	}

	Vector3 Vector3::operator-(void) const
	{
		return Vector3(-m_x, -m_y, -m_z);
	}

	Vector3& Vector3::operator+=(const Vector3& _rhs)
	{
		m_x += _rhs.m_x;
		m_y += _rhs.m_y;
		m_z += _rhs.m_z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& _rhs)
	{
		m_x -= _rhs.m_x;
		m_y -= _rhs.m_y;
		m_z -= _rhs.m_z;

		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& _rhs)
	{
		m_x *= _rhs.m_x;
		m_y *= _rhs.m_y;
		m_z *= _rhs.m_z;

		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& _rhs)
	{
		m_x /= _rhs.m_x;
		m_y /= _rhs.m_y;
		m_z /= _rhs.m_z;

		return*this;
	}

	Vector3& Vector3::operator*=(float _rhs)
	{
		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;

		return *this;
	}

	Vector3& Vector3::operator/=(float _rhs)
	{
		_rhs = 1.f / _rhs;

		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;

		return *this;
	}

	Vector3 Vector3::Zero(void)
	{
		return Vector3();
	}


	Vector3 Vector3::One(void)
	{
		return Vector3(1.f, 1.f, 1.f);
	}

	Vector3 Vector3::Up(void)
	{
		return Vector3(0.f, 1.f, 0.f);
	}

	Vector3 Vector3::Down(void)
	{
		return Vector3(0.f, -1.f, 0.f);
	}

	Vector3 Vector3::Left(void)
	{
		return Vector3(-1.f, 0.f, 0.f);
	}

	Vector3 Vector3::Right(void)
	{
		return Vector3(1.f, 0.f, 0.f);
	}

	Vector3 Vector3::Back(void)
	{
		return Vector3(0.f, 0.f, -1.f);
	}

	Vector3 Vector3::Front(void)
	{
		return Vector3(0.f, 0.f, 1.f);
	}



	std::ostream& operator<<(std::ostream& _os, Vector3 const& _vector)
	{
		_os << '{' << _vector.GetX() << ',' << _vector.GetY() << ',' << _vector.GetZ() << '}';

		return _os;
	}

	std::istream& operator>>(std::istream& _is, Vector3& _vector)
	{
		char	discard;

		_is >> discard >> _vector.X() >> discard >> _vector.Y() >> discard >> _vector.Z() >> discard;

		return _is;
	}



}