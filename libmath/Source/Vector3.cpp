#include <cmath>
#include <sstream>

#include "libmath/Matrix3.h"
#include "libmath/Matrix4.h"
#include "libmath/Vector3.h"
#include "libmath/Vector2.h"
#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"


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

		// Only run square root once
		magnitudes = SquareRoot(magnitudes);

		// Transform dot product equation to get cos angle,
		// then run acos
		return Acos(Dot(_other) / magnitudes);
	}

	Radian Vector3::AngleFromUnit(const Vector3& _other) const
	{
		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}


	Vector3 Vector3::Cross(const Vector3& _other) const
	{
		// Compute cross product
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
		// Find distance vector and get magnitude
		return (_other - *this).MagnitudeSquared();
	}

	float Vector3::Distance2DFrom(const Vector3& _other) const
	{
		return SquareRoot(Distance2DSquaredFrom(_other));
	}

	float Vector3::Distance2DSquaredFrom(const Vector3& _other) const
	{
		// Ignore z axis
		Vector2		dist2D =
		{
			_other.m_x - m_x,
			_other.m_y - m_y
		};

		// Find distance vector and get magnitude
		return dist2D.MagnitudeSquared();
	}


	float Vector3::Dot(const Vector3& _other) const
	{
		// Multiply components
		return (m_x * _other.m_x) + (m_y * _other.m_y) + (m_z * _other.m_z);
	}


	bool Vector3::IsLongerThan(const Vector3& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}


	bool Vector3::IsShorterThan(const Vector3& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}


	bool Vector3::IsUnitVector() const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	float Vector3::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}


	float Vector3::MagnitudeSquared() const
	{
		// Square components
		return Dot(*this);
	}

	void Vector3::Normalize()
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
		m_z *= invMagnitude;
	}

	Vector3 Vector3::Normalized(void) const
	{
		Vector3		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}


	void Vector3::ProjectOnto(const Vector3& _other)
	{
		// Apply projection formula
		float		squareMagnitude = _other.MagnitudeSquared();
		float		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;
		m_z = _other.m_z * projFactor;

	}


	void Vector3::ReflectOnto(const Vector3& _axis)
	{
		// Only reflect onto unit vector
		Vector3		normal = mth::Normalize(_axis);

		// Apply reflection formula
		*this -= normal * (Dot(normal) * 2.f);
	}

	void Vector3::ReflectOntoUnit(const Vector3& _axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= _axis * (Dot(_axis) * 2.f);
	}


	void Vector3::Rotate(Radian _angleX, Radian _angleY, Radian _angleZ)
	{
		Vector3		copy = *this;

		float		cosYaw = Cos(_angleZ), sinYaw = Sin(_angleZ);
		float		cosPitch = Cos(_angleX), sinPitch = Sin(_angleX);
		float		cosRoll = Cos(_angleY), sinRoll = Sin(_angleY);


		// Create rotation matrix
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

		// Multiply by rotation matrix
		*this = rotMatrix * copy;



	}

	void Vector3::Rotate(Radian _angle, const Vector3& _axis)
	{
		const Vector3		norm = mth::Normalize(_axis);
		const float			xCpy = m_x, yCpy = m_y, zCpy = m_z;

		// lib math trig functions are not precise enough,
		// use the standard ones instead :(
		const float			cosAngle = std::cos(_angle.Raw());
		const float			sinAngle = std::sin(_angle.Raw());

		const float			oneMinCos = 1.f - cosAngle;
		const Vector3		oneMinAxis = norm * oneMinCos;

		// Create multiplication matrix and multiply manually
		float				factorX = cosAngle + norm.m_x *
									  norm.m_x * oneMinCos;

		float				factorY = norm.m_x * norm.m_y *
									  oneMinCos - norm.m_z * sinAngle;
		float				factorZ = norm.m_x * norm.m_z *
									  oneMinCos + norm.m_y * sinAngle;

		m_x = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = norm.m_y * norm.m_x *
				  oneMinCos + norm.m_z * sinAngle;

		factorY = cosAngle + norm.m_y *
				  norm.m_y * oneMinCos;

		factorZ = norm.m_y * norm.m_z *
			      oneMinCos - norm.m_x * sinAngle;

		m_y = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = norm.m_z * norm.m_x *
				  oneMinCos - norm.m_y * sinAngle;

		factorY = norm.m_z * norm.m_y *
				  oneMinCos + norm.m_x * sinAngle;

		factorZ = cosAngle + norm.m_z *
				  norm.m_z * oneMinCos;

		m_z = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

	}


	void Vector3::Scale(const Vector3& _other)
	{
		*this *= _other;
	}

	std::string Vector3::String() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << ',' << m_z << '}';

		return stream.str();
	}


	std::string Vector3::StringLong() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
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
		// Copy assign
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
		// Compare all components
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

		// Return reflected copy
		result.ReflectOnto(_ontoNormal);

		return result;
	}

	Vector3 ReflectUnit(const Vector3& _target, const Vector3& _ontoNormal)
	{
		Vector3		result = _target;

		// Return reflected copy
		result.ReflectOntoUnit(_ontoNormal);

		return result;
	}

	Vector3 Project(const Vector3& _target, const Vector3& _ontoVector)
	{
		Vector3		result = _target;

		// Return projected copy
		result.ProjectOnto(_ontoVector);

		return result;
	}


	Vector3 Normalize(const Vector3& _target)
	{
		Vector3		result = _target;

		// Return normalized copy
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

		// Return rotated copy
		result.Rotate(_x, _y, _z);

		return result;
	}

	Vector3 Rotate(const Vector3& _target, Radian _angle, const Vector3& _axis)
	{
		Vector3		result = _target;

		// Return rotated copy
		result.Rotate(_angle, _axis);

		return result;
	}


	// Component-wise operators


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

		return Vector3(m_x * _rhs, m_y * _rhs, m_z * _rhs);
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


	// !Component-wise operators


	// Constants

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

	// !Constants

	std::ostream& operator<<(std::ostream& _os, Vector3 const& _vector)
	{
		// Pass components to stream
		_os << '{' << _vector.GetX() << ',' << _vector.GetY() << ',' <<
		_vector.GetZ() << '}';

		return _os;
	}

	std::istream& operator>>(std::istream& _is, Vector3& _vector)
	{
		char	discard;

		// Get input from stream
		_is >> discard >> _vector.X() >> discard >> _vector.Y()
			>> discard >> _vector.Z() >> discard;

		return _is;
	}



}