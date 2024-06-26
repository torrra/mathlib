#include <cmath>
#include <sstream>

#include "libmath/Matrix3.h"
#include "libmath/Matrix4.h"
#include "libmath/Vector3.h"
#include "libmath/Vector2.h"
#include "libmath/Trigonometry.h"
#include "libmath/Arithmetic.h"


#ifndef FLT_EPSILON
#include <limits>
#define FLT_EPSILON 	std::numeric_limits<TValueType>::epsilon()
#endif

namespace ion::math
{
	//template <CScalarType TValueType> inline
	//Vector3<TValueType>::Vector3<TValueType>(TValueType _val)
	//	: m_x(_val), m_y(_val), m_z(_val) {}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>::Vector3<TValueType>(TValueType _x, TValueType _y, TValueType _z)
	//	: m_x(_x), m_y(_y), m_z(_z) {}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>::Vector3<TValueType>(const Vector3<TValueType>& _other)
	//	: m_x(_other.m_x), m_y(_other.m_y), m_z(_other.m_z) {}


	//template <CScalarType TValueType> inline
	//Radian<TValueType> Vector3<TValueType>::AngleFrom(const Vector3<TValueType>& _other) const
	//{

	//	TValueType		magnitudes = MagnitudeSquared() * _other.MagnitudeSquared();

	//	// Only run square root once
	//	magnitudes = SquareRoot(magnitudes);

	//	// Transform dot product equation to get cos angle,
	//	// then run acos
	//	return Acos(Dot(_other) / magnitudes);
	//}


	//template <CScalarType TValueType> inline
	//Radian<TValueType> Vector3<TValueType>::AngleFromUnit(const Vector3<TValueType>& _other) const
	//{
	//	// Clamp dot to avoid acos domain error (NaN result)
	//	// and call acos as both vectors are assumed to be
	//	// unit vectors
	//	return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Cross(const Vector3<TValueType>& _other) const
	//{
	//	// Compute cross product
	//	return Vector3<TValueType>
	//	(
	//		(m_y * _other.m_z) - (m_z * _other.m_y),
	//		(m_z * _other.m_x) - (m_x * _other.m_z),
	//		(m_x * _other.m_y) - (m_y * _other.m_x)
	//	);

	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::DistanceFrom(const Vector3<TValueType>& _other) const
	//{
	//	return SquareRoot(DistanceSquaredFrom(_other));
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::DistanceSquaredFrom(const Vector3<TValueType>& _other) const
	//{
	//	// Find distance vector and get magnitude
	//	return (_other - *this).MagnitudeSquared();
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::Distance2DFrom(const Vector3<TValueType>& _other) const
	//{
	//	return SquareRoot(Distance2DSquaredFrom(_other));
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::Distance2DSquaredFrom(const Vector3<TValueType>& _other) const
	//{
	//	// Ignore z axis
	//	Vector2		dist2D =
	//	{
	//		_other.m_x - m_x,
	//		_other.m_y - m_y
	//	};

	//	// Find distance vector and get magnitude
	//	return dist2D.MagnitudeSquared();
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::Dot(const Vector3<TValueType>& _other) const
	//{
	//	// Multiply components
	//	return (m_x * _other.m_x) + (m_y * _other.m_y) + (m_z * _other.m_z);
	//}



	//template <CScalarType TValueType> inline
	//bool Vector3<TValueType>::IsLongerThan(const Vector3<TValueType>& _other) const
	//{
	//	// Compare squared magnitudes to avoid two sqrt calls
	//	return MagnitudeSquared() > _other.MagnitudeSquared();
	//}


	//template <CScalarType TValueType> inline
	//bool Vector3<TValueType>::IsShorterThan(const Vector3<TValueType>& _other) const
	//{
	//	// Compare squared magnitudes to avoid two sqrt calls
	//	return MagnitudeSquared() < _other.MagnitudeSquared();
	//}


	//template <CScalarType TValueType> inline
	//bool Vector3<TValueType>::IsUnitVector() const
	//{
	//	// 1 squared == 1 so avoiding sqrt call is possible
	//	return AlmostEqual(MagnitudeSquared(), 1.f);
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::Magnitude() const
	//{
	//	return SquareRoot(MagnitudeSquared());
	//}



	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::MagnitudeSquared() const
	//{
	//	// Square components
	//	return Dot(*this);
	//}



	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::Normalize()
	//{
	//	TValueType		invMagnitude = Magnitude();

	//	if (AlmostEqual(invMagnitude, 0.f, FLT_EPSILON))
	//	{
	//		throw std::logic_error("Cannot divide by zero magnitude");
	//	}

	//	// Only divide once
	//	else
	//		invMagnitude = 1.f / invMagnitude;


	//	m_x *= invMagnitude;
	//	m_y *= invMagnitude;
	//	m_z *= invMagnitude;
	//}



	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Normalized(void) const
	//{
	//	Vector3<TValueType>		result = *this;

	//	result.Normalize();

	//	// Return normalized copy
	//	return result;
	//}



	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::ProjectOnto(const Vector3<TValueType>& _other)
	//{
	//	// Apply projection formula
	//	TValueType		squareMagnitude = _other.MagnitudeSquared();
	//	TValueType		projFactor = Dot(_other) / squareMagnitude;

	//	m_x = _other.m_x * projFactor;
	//	m_y = _other.m_y * projFactor;
	//	m_z = _other.m_z * projFactor;

	//}



	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::ReflectOnto(const Vector3<TValueType>& _axis)
	//{
	//	// Only reflect onto unit vector
	//	Vector3<TValueType>		normal = ion::math::Normalize(_axis);

	//	// Apply reflection formula
	//	*this -= normal * (Dot(normal) * 2.f);
	//}


	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::ReflectOntoUnit(const Vector3<TValueType>& _axis)
	//{
	//	// Assume normal is already unit vector and skip normalize call
	//	*this -= _axis * (Dot(_axis) * 2.f);
	//}


	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::Rotate(Radian<TValueType> _angleX, Radian<TValueType> _angleY, Radian<TValueType> _angleZ)
	//{
	//	Vector3<TValueType>		copy = *this;

	//	TValueType		cosYaw = Cos(_angleZ), sinYaw = Sin(_angleZ);
	//	TValueType		cosPitch = Cos(_angleX), sinPitch = Sin(_angleX);
	//	TValueType		cosRoll = Cos(_angleY), sinRoll = Sin(_angleY);


	//	// Create rotation matrix
	//	TValueType		rotation[][3] =
	//	{
	//		{
	//			cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
	//			-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
	//			sinYaw * cosPitch
	//		},


	//		{
	//			sinRoll * cosPitch,
	//			cosRoll * cosPitch,
	//			-sinPitch
	//		},


	//		{
	//			-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
	//			sinRoll* sinYaw + cosYaw * sinPitch * cosRoll,
	//			cosYaw* cosPitch
	//		}
	//	};

	//	Matrix3		rotMatrix(rotation);

	//	// Multiply by rotation matrix
	//	*this = rotMatrix * copy;



	//}


	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::Rotate(Radian<TValueType> _angle, const Vector3<TValueType>& _axis)
	//{
	//	const Vector3<TValueType>		norm = ion::math::Normalize(_axis);
	//	const TValueType				xCpy = m_x, yCpy = m_y, zCpy = m_z;

	//	// lib math trig functions are not precise enough,
	//	// use the standard ones instead :(
	//	const TValueType			cosAngle = std::cos(_angle.Raw());
	//	const TValueType			sinAngle = std::sin(_angle.Raw());

	//	const TValueType			oneMinCos = 1.f - cosAngle;
	//	const Vector3<TValueType>		oneMinAxis = norm * oneMinCos;

	//	// Create multiplication matrix and multiply manually
	//	TValueType				factorX = cosAngle + norm.m_x *
	//								  norm.m_x * oneMinCos;

	//	TValueType				factorY = norm.m_x * norm.m_y *
	//								  oneMinCos - norm.m_z * sinAngle;
	//	TValueType				factorZ = norm.m_x * norm.m_z *
	//								  oneMinCos + norm.m_y * sinAngle;

	//	m_x = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

	//	factorX = norm.m_y * norm.m_x *
	//			  oneMinCos + norm.m_z * sinAngle;

	//	factorY = cosAngle + norm.m_y *
	//			  norm.m_y * oneMinCos;

	//	factorZ = norm.m_y * norm.m_z *
	//		      oneMinCos - norm.m_x * sinAngle;

	//	m_y = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

	//	factorX = norm.m_z * norm.m_x *
	//			  oneMinCos - norm.m_y * sinAngle;

	//	factorY = norm.m_z * norm.m_y *
	//			  oneMinCos + norm.m_x * sinAngle;

	//	factorZ = cosAngle + norm.m_z *
	//			  norm.m_z * oneMinCos;

	//	m_z = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

	//}


	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::Scale(const Vector3<TValueType>& _other)
	//{
	//	*this *= _other;
	//}


	//template <CScalarType TValueType> inline
	//std::string Vector3<TValueType>::String() const
	//{
	//	// Use stream for easy conversion
	//	std::stringstream		stream;

	//	// Pass components to stream
	//	stream << '{' << m_x << ',' << m_y << ',' << m_z << '}';

	//	return stream.str();
	//}



	//template <CScalarType TValueType> inline
	//std::string Vector3<TValueType>::StringLong() const
	//{
	//	// Use stream for easy conversion
	//	std::stringstream		stream;

	//	// Pass components to stream
	//	stream << "Vector3<TValueType>{ x:" << m_x << ", y:" << m_y << ", z:" << m_z << " }";

	//	return stream.str();
	//}


	//template <CScalarType TValueType> inline
	//void Vector3<TValueType>::Translate(const Vector3<TValueType>& _other)
	//{
	//	*this += _other;
	//}



	//template <CScalarType TValueType> inline
	//TValueType& Vector3<TValueType>::X()
	//{
	//	return m_x;
	//}


	//template <CScalarType TValueType> inline
	//TValueType& Vector3<TValueType>::Y()
	//{
	//	return m_y;
	//}


	//template <CScalarType TValueType> inline
	//TValueType& Vector3<TValueType>::Z()
	//{
	//	return m_z;
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::GetX() const
	//{
	//	return m_x;
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::GetY() const
	//{
	//	return m_y;
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::GetZ() const
	//{
	//	return m_z;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>& Vector3<TValueType>::operator=(const Vector3<TValueType>& _rhs)
	//{
	//	// Copy assign
	//	m_x = _rhs.m_x;
	//	m_y = _rhs.m_y;
	//	m_z = _rhs.m_z;

	//	return *this;
	//}


	//template <CScalarType TValueType> inline
	//TValueType& Vector3<TValueType>::operator[](int _index)
	//{
	//	switch (_index)
	//	{
	//	case 0:
	//		return m_x;
	//	case 1:
	//		return m_y;
	//	case 2:
	//		return m_z;
	//	default:
	//		throw std::logic_error("Vector index out of range");
	//	}
	//}


	//template <CScalarType TValueType> inline
	//TValueType Vector3<TValueType>::operator[](int _index) const
	//{
	//	switch (_index)
	//	{
	//	case 0:
	//		return m_x;

	//	case 1:
	//		return m_y;

	//	case 2:
	//		return m_z;

	//	default:
	//		throw std::logic_error("Vector index out of range");
	//	}
	//}


	//template <CScalarType TValueType> inline
	//bool Vector3<TValueType>::operator==(const Vector3<TValueType>& _rhs) const
	//{
	//	// Compare all components
	//	return
	//	(
	//		AlmostEqual(m_x, _rhs.m_x) &&
	//		AlmostEqual(m_y, _rhs.m_y) &&
	//		AlmostEqual(m_z, _rhs.m_z)
	//	);
	//}



	//template <CScalarType TValueType> inline
	//bool Vector3<TValueType>::operator!=(const Vector3<TValueType>& _rhs) const
	//{
	//	return !(*this == _rhs);
	//}


	//template <CScalarType TValueType> inline
	//TValueType Dot(const Vector3<TValueType>& _first, const Vector3<TValueType>& _second)
	//{
	//	return _first.Dot(_second);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Cross(const Vector3<TValueType>& _first, const Vector3<TValueType>& _second)
	//{
	//	return _first.Cross(_second);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Reflect(const Vector3<TValueType>& _target, const Vector3<TValueType>& _ontoNormal)
	//{
	//	Vector3<TValueType>		result = _target;

	//	// Return reflected copy
	//	result.ReflectOnto(_ontoNormal);

	//	return result;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> ReflectUnit(const Vector3<TValueType>& _target, const Vector3<TValueType>& _ontoNormal)
	//{
	//	Vector3<TValueType>		result = _target;

	//	// Return reflected copy
	//	result.ReflectOntoUnit(_ontoNormal);

	//	return result;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Project(const Vector3<TValueType>& _target, const Vector3<TValueType>& _ontoVector)
	//{
	//	Vector3<TValueType>		result = _target;

	//	// Return projected copy
	//	result.ProjectOnto(_ontoVector);

	//	return result;
	//}



	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Normalize(const Vector3<TValueType>& _target)
	//{
	//	Vector3<TValueType>		result = _target;

	//	// Return normalized copy
	//	result.Normalize();

	//	return result;
	//}


	//template <CScalarType TValueType> inline
	//TValueType Distance(const Vector3<TValueType>& _start, const Vector3<TValueType>& _end)
	//{
	//	return _start.DistanceFrom(_end);
	//}


	//template <CScalarType TValueType> inline
	//TValueType DistanceSquared(const Vector3<TValueType>& _start, const Vector3<TValueType>& _end)
	//{
	//	return _start.DistanceSquaredFrom(_end);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Rotate(const Vector3<TValueType>& _target, Radian<TValueType> _x, Radian<TValueType> _y, Radian<TValueType> _z)
	//{
	//	Vector3<TValueType>		result = _target;

	//	// Return rotated copy
	//	result.Rotate(_x, _y, _z);

	//	return result;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Rotate(const Vector3<TValueType>& _target, Radian<TValueType> _angle, const Vector3<TValueType>& _axis)
	//{
	//	Vector3<TValueType>		result = _target;

	//	// Return rotated copy
	//	result.Rotate(_angle, _axis);

	//	return result;
	//}


	//// Component-wise operators


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::operator+(const Vector3<TValueType>& _rhs) const
	//{
	//	return Vector3<TValueType>(m_x + _rhs.m_x, m_y + _rhs.m_y, m_z + _rhs.m_z);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::operator-(const Vector3<TValueType>& _rhs) const
	//{
	//	return Vector3<TValueType>(m_x - _rhs.m_x, m_y - _rhs.m_y, m_z - _rhs.m_z);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::operator*(const Vector3<TValueType>& _rhs) const
	//{
	//	return Vector3<TValueType>(m_x * _rhs.m_x, m_y * _rhs.m_y, m_z * _rhs.m_z);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::operator/(const Vector3<TValueType>& _rhs) const
	//{
	//	return Vector3<TValueType>(m_x / _rhs.m_x, m_y / _rhs.m_y, m_z / _rhs.m_z);
	//}



	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::operator*(TValueType _rhs) const
	//{
	//	return Vector3<TValueType>(m_x * _rhs, m_y * _rhs, m_z * _rhs);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::operator/(TValueType _rhs) const
	//{
	//	_rhs = 1.f / _rhs;

	//	return Vector3<TValueType>(m_x * _rhs, m_y * _rhs, m_z * _rhs);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::operator-(void) const
	//{
	//	return Vector3<TValueType>(-m_x, -m_y, -m_z);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>& Vector3<TValueType>::operator+=(const Vector3<TValueType>& _rhs)
	//{
	//	m_x += _rhs.m_x;
	//	m_y += _rhs.m_y;
	//	m_z += _rhs.m_z;

	//	return *this;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>& Vector3<TValueType>::operator-=(const Vector3<TValueType>& _rhs)
	//{
	//	m_x -= _rhs.m_x;
	//	m_y -= _rhs.m_y;
	//	m_z -= _rhs.m_z;

	//	return *this;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>& Vector3<TValueType>::operator*=(const Vector3<TValueType>& _rhs)
	//{
	//	m_x *= _rhs.m_x;
	//	m_y *= _rhs.m_y;
	//	m_z *= _rhs.m_z;

	//	return *this;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>& Vector3<TValueType>::operator/=(const Vector3<TValueType>& _rhs)
	//{
	//	m_x /= _rhs.m_x;
	//	m_y /= _rhs.m_y;
	//	m_z /= _rhs.m_z;

	//	return*this;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>& Vector3<TValueType>::operator*=(TValueType _rhs)
	//{
	//	m_x *= _rhs;
	//	m_y *= _rhs;
	//	m_z *= _rhs;

	//	return *this;
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType>& Vector3<TValueType>::operator/=(TValueType _rhs)
	//{
	//	_rhs = 1.f / _rhs;

	//	m_x *= _rhs;
	//	m_y *= _rhs;
	//	m_z *= _rhs;

	//	return *this;
	//}


	//// !Component-wise operators


	//// Constants


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Zero(void)
	//{
	//	return Vector3<TValueType>();
	//}



	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::One(void)
	//{
	//	return Vector3<TValueType>(1.f, 1.f, 1.f);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Up(void)
	//{
	//	return Vector3<TValueType>(0.f, 1.f, 0.f);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Down(void)
	//{
	//	return Vector3<TValueType>(0.f, -1.f, 0.f);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Left(void)
	//{
	//	return Vector3<TValueType>(-1.f, 0.f, 0.f);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Right(void)
	//{
	//	return Vector3<TValueType>(1.f, 0.f, 0.f);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Back(void)
	//{
	//	return Vector3<TValueType>(0.f, 0.f, -1.f);
	//}


	//template <CScalarType TValueType> inline
	//Vector3<TValueType> Vector3<TValueType>::Front(void)
	//{
	//	return Vector3<TValueType>(0.f, 0.f, 1.f);
	//}

	//// !Constants


	//template <CScalarType TValueType> inline
	//std::ostream& operator<<(std::ostream& _os, Vector3<TValueType> const& _vector)
	//{
	//	// Pass components to stream
	//	_os << '{' << _vector.GetX() << ',' << _vector.GetY() << ',' <<
	//	_vector.GetZ() << '}';

	//	return _os;
	//}


	//template <CScalarType TValueType> inline
	//std::istream& operator>>(std::istream& _is, Vector3<TValueType>& _vector)
	//{
	//	char	discard;

	//	// Get input from stream
	//	_is >> discard >> _vector.X() >> discard >> _vector.Y()
	//		>> discard >> _vector.Z() >> discard;

	//	return _is;
	//}



}