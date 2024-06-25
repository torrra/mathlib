#include <stdexcept>
#include <sstream>

#include "libmath/Vector2.h"
#include "libmath/Vector4.h"

#include "libmath/Matrix4.h"

#include "libmath/Arithmetic.h"
#include "libmath/Trigonometry.h"


#ifndef FLT_EPSILON
#include <limits>
#define FLT_EPSILON 	std::numeric_limits<float>::epsilon()
#endif

namespace ion::math
{

	Vector4::Vector4(float _val)
		: m_x(_val), m_y(_val), m_z(_val), m_w(_val)
	{}

	Vector4::Vector4(float _x, float _y, float _z, float _w)
		: m_x(_x), m_y(_y), m_z(_z), m_w(_w)
	{}

	Vector4::Vector4(const Vector4 & _other)
		: m_x(_other.m_x), m_y(_other.m_y), m_z(_other.m_z), m_w(_other.m_w)
	{}

	Radian Vector4::AngleFrom(const Vector4 & _other) const
	{
		float		magnitudes = MagnitudeSquared() * _other.MagnitudeSquared();

		// Only run square root once
		magnitudes = SquareRoot(magnitudes);

		// Transform dot product equation to get cos angle,
		// then run acos
		return Acos(Dot(_other) / magnitudes);
	}

	Radian Vector4::AngleFromUnit(const Vector4& _other) const
	{
		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}

	float Vector4::DistanceFrom(const Vector4& _other) const
	{
		return SquareRoot(DistanceSquaredFrom(_other));
	}

	float Vector4::DistanceSquaredFrom(const Vector4& _other) const
	{
		// Find distance vector and get magnitude
		return (_other - *this).MagnitudeSquared();
	}

	float Vector4::Distance2DFrom(Vector4 const& _other) const
	{
		// Ignore z and w axes
		Vector2		self2D = { m_x, m_y };
		Vector2		other2D = { _other.m_x, _other.m_y};


		return self2D.DistanceFrom(other2D);
	}

	float Vector4::Distance2DSquaredFrom(Vector4 const& _other) const
	{
		// Ignore z and w axes
		Vector2		self2D = { m_x, m_y };
		Vector2		other2D = { _other.m_x, _other.m_y };


		return self2D.DistanceSquaredFrom(other2D);
	}

	float Vector4::Distance3DFrom(Vector4 const& _other) const
	{
		// Ignore w axis
		Vector3		self3D = { m_x, m_y, m_z };
		Vector3		other3D = { _other.m_x, _other.m_y, _other.m_z };


		return self3D.DistanceFrom(other3D);
	}

	float Vector4::Distance3DSquaredFrom(Vector4 const& _other) const
	{
		// Ignore w axis
		Vector3		self3D = { m_x, m_y, m_z };
		Vector3		other3D = { _other.m_x, _other.m_y, _other.m_z };


		return self3D.DistanceSquaredFrom(other3D);
	}

	float Vector4::Dot(const Vector4& _other) const
	{
		// Multiply components
		return (m_x * _other.m_x) + (m_y * _other.m_y) +
			   (m_z * _other.m_z) + (m_w * _other.m_w);
	}

	bool Vector4::IsLongerThan(const Vector4& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}

	bool Vector4::IsShorterThan(const Vector4& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}

	bool Vector4::IsUnitVector(void) const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}

	float Vector4::Magnitude(void) const
	{
		return SquareRoot(MagnitudeSquared());
	}

	float Vector4::MagnitudeSquared(void) const
	{
		// Square components
		return Dot(*this);
	}

	void Vector4::Normalize(void)
	{
		// Only divide once
		float		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, 0.f, FLT_EPSILON))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		else
			invMagnitude = 1.f / invMagnitude;


		m_x *= invMagnitude;
		m_y *= invMagnitude;
		m_z *= invMagnitude;
		m_w *= invMagnitude;
	}

	Vector4 Vector4::Normalized(void) const
	{
		Vector4		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}

	void Vector4::ProjectOnto(const Vector4& _other)
	{
		// Apply projection formula
		float		squareMagnitude = _other.MagnitudeSquared();
		float		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;
		m_z = _other.m_z * projFactor;
		m_w = _other.m_w * projFactor;
	}

	void Vector4::ReflectOnto(const Vector4& _axis)
	{
		// Only reflect onto unit vector
		Vector4		normal = ion::math::Normalize(_axis);

		*this -= normal * (Dot(normal) * 2.f);
	}

	void Vector4::ReflectOntoUnit(const Vector4& _axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= _axis * (Dot(_axis) * 2.f);
	}

	void Vector4::Rotate(Radian _angleX, Radian _angleY, Radian _angleZ)
	{
		Vector4		copy = *this;

		float		cosYaw = Cos(_angleZ), sinYaw = Sin(_angleZ);
		float		cosPitch = Cos(_angleX), sinPitch = Sin(_angleX);
		float		cosRoll = Cos(_angleY), sinRoll = Sin(_angleY);

		// Create rotation matrix
		float		rotation[][4] =
		{
			{
				cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
				-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
				sinYaw * cosPitch,
				0.f
			},


			{
				sinRoll * cosPitch,
				cosRoll * cosPitch,
				-sinPitch,
				0.f
			},


			{
				-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
				sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,
				cosYaw * cosPitch,
				0.f
			},

			{ 0.f, 0.f, 0.f, 1.f}
		};

		Matrix4		rotMatrix(rotation);

		// Multiply by rotation matrix
		*this = rotMatrix * copy;
	}

	void Vector4::Rotate(Radian _angle, const Vector3& _axis)
	{
		// Ignore w axis
		Vector3		self3D = { m_x, m_y, m_z };

		// Rotate without w
		self3D.Rotate(_angle, _axis);

		m_x = self3D.GetX();
		m_y = self3D.GetY();
		m_z = self3D.GetZ();
	}

	void Vector4::Scale(const Vector4& _other)
	{
		*this *= _other;
	}

	std::string Vector4::String(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << ',' << m_z << ',' << m_w << '}';

		return stream.str();
	}

	std::string Vector4::StringLong(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << "Vector4{ x:" << m_x << ", y:" << m_y << ", z:"
			   << m_z << ", w:" << m_w << " }";

		return stream.str();
	}

	void Vector4::Translate(const Vector4& _other)
	{
		*this += _other;
	}

	float& Vector4::X(void)
	{
		return m_x;
	}

	float& Vector4::Y(void)
	{
		return m_y;
	}

	float& Vector4::Z(void)
	{
		return m_z;
	}

	float& Vector4::W(void)
	{
		return m_w;
	}

	float Vector4::GetX(void) const
	{
		return m_x;
	}

	float Vector4::GetY(void) const
	{
		return m_y;
	}

	float Vector4::GetZ(void) const
	{
		return m_z;
	}

	float Vector4::GetW(void) const
	{
		return m_w;
	}

	Vector4& Vector4::operator=(const Vector4& _rhs)
	{
		// Copy assign
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;
		m_z = _rhs.m_z;
		m_w = _rhs.m_w;

		return *this;
	}

	float& Vector4::operator[](int _index)
	{
		switch (_index)
		{
		case 0:
			return m_x;
		case 1:
			return m_y;
		case 2:
			return m_z;
		case 3:
			return m_w;
		default:
			throw std::logic_error("Vector index out of range");
		}
	}

	float Vector4::operator[](int _index) const
	{
		switch (_index)
		{
		case 0:
			return m_x;
		case 1:
			return m_y;
		case 2:
			return m_z;
		case 3:
			return m_w;
		default:
			throw std::logic_error("Vector index out of range");
		}
	}

	bool Vector4::operator==(const Vector4& _rhs) const
	{
		// Compare all components
		return
			(
				AlmostEqual(m_x, _rhs.m_x) &&
				AlmostEqual(m_y, _rhs.m_y) &&
				AlmostEqual(m_z, _rhs.m_z) &&
				AlmostEqual(m_w, _rhs.m_w)

			);
	}

	bool Vector4::operator!=(const Vector4& _rhs) const
	{
		return !(*this == _rhs);
	}


	// Component-wise operators


	Vector4 Vector4::operator+(const Vector4& _rhs) const
	{
		return Vector4(m_x + _rhs.m_x, m_y + _rhs.m_y,
					  m_z + _rhs.m_z, m_w + _rhs.m_w);
	}

	Vector4 Vector4::operator-(const Vector4& _rhs) const
	{
		return Vector4(m_x - _rhs.m_x, m_y - _rhs.m_y,
					   m_z - _rhs.m_z, m_w - _rhs.m_w);
	}

	Vector4 Vector4::operator*(const Vector4& _rhs) const
	{
		return Vector4(m_x * _rhs.m_x, m_y * _rhs.m_y,
			           m_z * _rhs.m_z, m_w * _rhs.m_w);
	}

	Vector4 Vector4::operator/(const Vector4& _rhs) const
	{
		return Vector4(m_x / _rhs.m_x, m_y / _rhs.m_y,
					   m_z / _rhs.m_z, m_w / _rhs.m_w);
	}

	Vector4 Vector4::operator*(float _rhs) const
	{
		return Vector4(m_x * _rhs, m_y * _rhs,
					   m_z * _rhs, m_w * _rhs);
	}

	Vector4 Vector4::operator/(float _rhs) const
	{
		_rhs = 1.f / _rhs;

		return Vector4(m_x * _rhs, m_y * _rhs, m_z * _rhs, m_w * _rhs);
	}

	Vector4 Vector4::operator-(void) const
	{
		return Vector4(-m_x, -m_y, -m_z, -m_w);
	}

	Vector4& Vector4::operator+=(const Vector4& _rhs)
	{
		m_x += _rhs.m_x;
		m_y += _rhs.m_y;
		m_z += _rhs.m_z;
		m_w += _rhs.m_w;

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& _rhs)
	{
		m_x -= _rhs.m_x;
		m_y -= _rhs.m_y;
		m_z -= _rhs.m_z;
		m_w -= _rhs.m_w;

		return *this;
	}

	Vector4& Vector4::operator*=(const Vector4& _rhs)
	{
		m_x *= _rhs.m_x;
		m_y *= _rhs.m_y;
		m_z *= _rhs.m_z;
		m_w *= _rhs.m_w;

		return *this;
	}

	Vector4& Vector4::operator/=(const Vector4& _rhs)
	{
		m_x /= _rhs.m_x;
		m_y /= _rhs.m_y;
		m_z /= _rhs.m_z;
		m_w /= _rhs.m_w;

		return*this;
	}

	Vector4& Vector4::operator*=(float _rhs)
	{
		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;
		m_w *= _rhs;

		return *this;
	}

	Vector4& Vector4::operator/=(float _rhs)
	{
		_rhs = 1.f / _rhs;

		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;
		m_w *= _rhs;

		return *this;
	}


	// !Component-wise operators


	// Constants

	Vector4 Vector4::Zero(void)
	{
		return Vector4();
	}

	Vector4 Vector4::One(void)
	{
		return Vector4(1.f, 1.f, 1.f, 1.f);
	}

	Vector4 Vector4::Up(void)
	{
		return Vector4(0.f, 1.f, 0.f, 0.f);
	}

	Vector4 Vector4::Down(void)
	{
		return Vector4(0.f, -1.f, 0.f, 0.f);
	}

	Vector4 Vector4::Left(void)
	{
		return Vector4(-1.f, 0.f, 0.f, 0.f);
	}

	Vector4 Vector4::Right(void)
	{
		return Vector4(1.f, 0.f, 0.f, 0.f);
	}

	Vector4 Vector4::Back(void)
	{
		return Vector4(0.f, 0.f, -1.f, 0.f);
	}

	Vector4 Vector4::Front(void)
	{
		return Vector4(0.f, 0.f, 1.f, 0.f);
	}


	// !Constants

	float Dot(const Vector4& _first, const Vector4& _second)
	{
		return _first.Dot(_second);
	}

	Vector4 Reflect(const Vector4& _target, const Vector4& _ontoNormal)
	{
		Vector4		copy = _target;

		// Return reflected copy
		copy.ReflectOnto(_ontoNormal);

		return copy;
	}

	Vector4 ReflectUnit(const Vector4& _target, const Vector4& _ontoNormal)
	{
		Vector4		copy = _target;

		// Return reflected copy
		copy.ReflectOntoUnit(_ontoNormal);

		return copy;
	}

	Vector4 Project(const Vector4& _target, const Vector4& _ontoVector)
	{
		Vector4		copy = _target;

		// Return projected copy
		copy.ProjectOnto(_ontoVector);

		return copy;
	}

	Vector4 Normalize(const Vector4& _target)
	{
		// Return normalized copy
		return _target.Normalized();
	}

	float Distance(const Vector4& _start, const Vector4& _end)
	{
		return _start.DistanceFrom(_end);
	}

	float DistanceSquared(const Vector4& _start, const Vector4& _end)
	{
		return _start.DistanceSquaredFrom(_end);
	}

	Vector4 Rotate(const Vector4& _target, Radian _angleX, Radian _angleY, Radian _angleZ)
	{
		Vector4		copy = _target;

		// Return rotated copy
		copy.Rotate(_angleX, _angleY, _angleZ);

		return copy;
	}

	Vector4 Rotate(const Vector4& _target, Radian _angle, const Vector3& _axis)
	{
		Vector4		copy = _target;

		// Return rotated copy
		copy.Rotate(_angle, _axis);

		return copy;
	}

	std::ostream& operator<<(std::ostream& _os, Vector4 const& _vector)
	{
		// Pass components to stream
		_os << '{' << _vector.GetX() << ',' << _vector.GetY()
			<< ',' << _vector.GetZ() << ',' << _vector.GetW() << '}';

		return _os;
	}
	std::istream& operator>>(std::istream& _is, Vector4& _vector)
	{
		char	discard;

		// Get input from stream
		_is >> discard >> _vector.X() >> discard >> _vector.Y()
			>> discard >> _vector.Z() >> discard >> _vector.W() >> discard;

		return _is;
	}
}