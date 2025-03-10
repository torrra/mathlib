#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <string>
#include <cmath>
#include <sstream>

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"

#include "Trigonometry.hpp"
#include "Arithmetic.hpp"
#include "Angle.hpp"
#include "Vector2.hpp"
//#include "VectorQuatOperations.hpp"



namespace math
{

	template <CScalarType TValueType>
	class Vector<3, TValueType>
	{
	public:

		// Constructors / destructor
		inline				Vector(void) = default;

		inline
		explicit			Vector(TValueType val);


		inline				Vector(TValueType x, TValueType y, TValueType z);
		inline				Vector(const Vector& other);

		inline				~Vector(void) = default;

		// Get angle from this vector to another
		inline
		Radian<TValueType>	AngleFrom(const Vector& other)				const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
		inline
		Radian<TValueType>	AngleFromUnit(const Vector& other)			const;

		// Compute cross product with another
		// this x other
		inline Vector		Cross(const Vector& other)					const;

		// Get distance between 2 points
		inline TValueType	DistanceFrom(const Vector& other)				const;

		// Get distance squared between two points
		inline TValueType	DistanceSquaredFrom(const Vector& other)		const;

		// Get distance between 2 points disregarding the z axis
		inline TValueType	Distance2DFrom(Vector const&)					const;

		// Get distance squared between two points disregarding the z axis
		inline TValueType	Distance2DSquaredFrom(Vector const&)			const;

		// Compute dot product of two vectors
		inline TValueType	Dot(const Vector& other)						const;

		// Is this vector's magnitude longer than another ?
		inline bool			IsLongerThan(const Vector& other)				const;

		// Is this vector's magnitude shorter than another ?
		inline bool			IsShorterThan(const Vector& other)			const;

		// Is this vector's magnitude equal to 1 ?
		inline bool			IsUnitVector(void)								const;

		inline TValueType	Magnitude(void)									const;
		inline TValueType	MagnitudeSquared(void)							const;

		// Adjust vector to turn into unit vector
		inline void			Normalize(void);

		// Get copy of this vector as a unit vector
		inline Vector		Normalized(void)								const;

		// Project this vector onto another
		inline void			ProjectOnto(const Vector& other);

		// Reflect this vector onto another
		inline void			ReflectOnto(const Vector& axis);

		// Reflect this vector onto a UNIT vector
		inline void			ReflectOntoUnit(const Vector& axis);

		// Rotate this vector around the all 3 axes
		inline void			Rotate
		(
			Radian<TValueType> angleX,
			Radian<TValueType> angleY,
			Radian<TValueType> angleZ
		);

		// Rotate this vector around an arbitrary axis
		inline void			Rotate
		(Radian<TValueType> angle, const Vector& axis);

		// Multiply this vector's components by another's
		inline void			Scale(const Vector& other);

		// Get components as string
		inline std::string	String(void)									const;

		// Get components as verbose string
		inline std::string	StringLong(void)								const;

		// Add another vector's components to this one's
		inline void			Translate(const Vector& other);

		// Accessors

		inline TValueType&	X(void);
		inline TValueType&	Y(void);
		inline TValueType&	Z(void);

		inline TValueType	GetX(void)										const;
		inline TValueType	GetY(void)										const;
		inline TValueType	GetZ(void)										const;


		inline Vector&		operator=(const Vector& rhs);

		inline TValueType&			operator[](int index);
		inline TValueType			operator[](int index)					const;

		// Boolean test operators

		inline bool			operator==(const Vector& rhs)					const;
		inline bool			operator!=(const Vector& rhs)					const;

		// Component-wise operations

		inline Vector			operator+(const Vector& rhs)				const;
		inline Vector			operator-(const Vector& rhs)				const;
		inline Vector			operator*(const Vector& rhs)				const;
		inline Vector			operator/(const Vector& rhs)				const;

		// Multiply all components by a single scalar
		inline Vector			operator*(TValueType rhs)					const;

		// Divide all components by a single scalar
		inline Vector			operator/(TValueType rhs)					const;

		// Flip sign of both components
		inline Vector			operator-(void)								const;


		// Component-wise operations

		inline Vector&		operator+=(const Vector& rhs);
		inline Vector&		operator-=(const Vector& rhs);
		inline Vector&		operator*=(const Vector& rhs);
		inline Vector&		operator/=(const Vector& rhs);

		// Multiply all components by a single scalar
		inline Vector&		operator*=(TValueType rhs);

		// Divide all components by a single scalar
		inline Vector&		operator/=(TValueType rhs);


		// Constants

		inline static Vector	Zero(void);
		inline static Vector	One(void);
		inline static Vector	Up(void);
		inline static Vector	Down(void);
		inline static Vector	Left(void);
		inline static Vector	Right(void);
		inline static Vector	Back(void);
		inline static Vector	Front(void);
		inline static Vector	Lerp(const Vector& start, const Vector& end, TValueType time);


	private:

		TValueType				m_x;
		TValueType				m_y;
		TValueType				m_z;
	};

	// Non-member functions (similar to member functions but provided for readability)

	template <CScalarType TValueType> inline
	TValueType				Dot
	(const Vector<3, TValueType>& first, const Vector<3, TValueType>& second);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>		Cross
	(const Vector<3, TValueType>& first, const Vector<3, TValueType>& second);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Reflect
	(const Vector<3, TValueType>& target, const Vector<3, TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>				ReflectUnit
	(const Vector<3, TValueType>& target, const Vector<3, TValueType>& ontoNormal);


	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Project
	(const Vector<3, TValueType>& target, const Vector<3, TValueType>& ontoVector);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Normalize(const Vector<3, TValueType>& target);


	template <CScalarType TValueType> inline
	TValueType				Distance
	(const Vector<3, TValueType>& start, const Vector<3, TValueType>& end);


	template <CScalarType TValueType> inline
	TValueType				DistanceSquared
	(const Vector<3, TValueType>& start, const Vector<3, TValueType>& end);


	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Rotate
	(
		const Vector<3, TValueType>& target,
		Radian<TValueType> angleX,
		Radian<TValueType> angleY,
		Radian<TValueType> angleZ
	);


	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Rotate
	(
		const Vector<3, TValueType>& target,
		Radian<TValueType> angle, const Vector<3, TValueType>& axis
	);

	// Send a vector's components to an output stream
	template <CScalarType TValueType> inline
	std::ostream&		operator<<
	(std::ostream& os, Vector<3, TValueType> const& vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream&		operator>>
	(std::istream& is, Vector<3, TValueType>& vector);


	// ---- Implementation ---

	template <CScalarType TValueType> inline
		Vector<3, TValueType>::Vector(TValueType val)
		: m_x(val), m_y(val), m_z(val) {}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>::Vector(TValueType x, TValueType y, TValueType z)
		: m_x(x), m_y(y), m_z(z) {}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>::Vector(const Vector<3, TValueType>& other)
		: m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) {}


	template <CScalarType TValueType> inline
		Radian<TValueType> Vector<3, TValueType>::AngleFrom
		(const Vector<3, TValueType>& other) const
	{
		if constexpr (std::is_integral<TValueType>::value)
			throw std::logic_error("cannot find angle between vectors of integral types");

		else
		{
			TValueType    magnitudes = MagnitudeSquared() * other.MagnitudeSquared();

			// Only run square root once
			magnitudes = SquareRoot(magnitudes);

			// Transform dot product equation to get cos angle,
			// then run acos
			return Acos(Dot(other) / magnitudes);
		}
	}


	template <CScalarType TValueType> inline
		Radian<TValueType> Vector<3, TValueType>::AngleFromUnit
		(const Vector<3, TValueType>& other) const
	{
		if constexpr (std::is_integral<TValueType>::value)
			throw std::logic_error("cannot find angle between vectors of integral types");

		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		else
			return Acos(Clamp(Dot(other), static_cast<TValueType>(MIN_COS),
				static_cast<TValueType>(MAX_COS)));
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::Cross
		(const Vector<3, TValueType>& other) const
	{
		// Compute cross product
		return Vector<3, TValueType>
			(
				(m_y * other.m_z) - (m_z * other.m_y),
				(m_z * other.m_x) - (m_x * other.m_z),
				(m_x * other.m_y) - (m_y * other.m_x)
			);

	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::DistanceFrom
		(const Vector<3, TValueType>& other) const
	{
		return SquareRoot(DistanceSquaredFrom(other));
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::DistanceSquaredFrom
		(const Vector<3, TValueType>& other) const
	{
		// Find distance vector and get magnitude
		return (other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::Distance2DFrom
		(const Vector<3, TValueType>& other) const
	{
		return SquareRoot(Distance2DSquaredFrom(other));
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::Distance2DSquaredFrom(const Vector<3, TValueType>& other) const
	{
		// Ignore z axis
		Vector2<TValueType>		dist2D =
		{
			static_cast<TValueType>(other.m_x - m_x),
			static_cast<TValueType>(other.m_y - m_y)
		};

		// Find distance vector and get magnitude
		return dist2D.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::Dot
		(const Vector<3, TValueType>& other) const
	{
		// Multiply components
		return (m_x * other.m_x) + (m_y * other.m_y) + (m_z * other.m_z);
	}



	template <CScalarType TValueType> inline
		bool Vector<3, TValueType>::IsLongerThan
		(const Vector<3, TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		bool Vector<3, TValueType>::IsShorterThan
		(const Vector<3, TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		bool Vector<3, TValueType>::IsUnitVector() const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}



	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::MagnitudeSquared() const
	{
		// Square components
		return Dot(*this);
	}



	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::Normalize()
	{
		TValueType		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, static_cast<TValueType>(0), std::numeric_limits<TValueType>::epsilon()))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		// Only divide once
		else
			invMagnitude = static_cast<TValueType>(1) / invMagnitude;


		m_x *= invMagnitude;
		m_y *= invMagnitude;
		m_z *= invMagnitude;
	}



	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::Normalized(void) const
	{
		Vector<3, TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}



	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::ProjectOnto(const Vector<3, TValueType>& other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = other.MagnitudeSquared();
		TValueType		projFactor = Dot(other) / squareMagnitude;

		m_x = other.m_x * projFactor;
		m_y = other.m_y * projFactor;
		m_z = other.m_z * projFactor;

	}



	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::ReflectOnto(const Vector<3, TValueType>& axis)
	{
		// Only reflect onto unit vector
		Vector<3, TValueType>		normal = math::Normalize(axis);

		// Apply reflection formula
		*this -= normal * (Dot(normal) * static_cast<TValueType>(2));
	}


	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::ReflectOntoUnit(const Vector<3, TValueType>& axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= axis * (Dot(axis) * static_cast<TValueType>(2));
	}


	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::Rotate
		(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
	{
		if constexpr (std::is_unsigned_v<TValueType> || std::is_integral_v<TValueType>)
			throw std::logic_error("cannot rotate unsigned or integral vector");

		else
			/*(*this) = RotateWithQuat(*this, angleX, angleY, angleZ); */

		{
			Vector<3, TValueType>		copy = *this;

			TValueType				cosYaw = Cos(angleZ), sinYaw = Sin(angleZ);
			TValueType				cosPitch = Cos(angleX), sinPitch = Sin(angleX);
			TValueType				cosRoll = Cos(angleY), sinRoll = Sin(angleY);
			TValueType				rowResult;


			// Create rotation matrix.
			// Not an actual matrix3 object to avoid circular includes
			TValueType		rotation[][3] =
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
					sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,
					cosYaw * cosPitch
				}
			};


			// Multiply vector by matrix
			for (int row = 0; row < 3; ++row)
			{
				// Accumulator
				rowResult = static_cast<TValueType>(0);

				for (int column = 0; column < 3; ++column)
				{
					rowResult += rotation[row][column] * copy[column];
				}

				(*this)[row] = rowResult;
			}
		}


	}


	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::Rotate
		(Radian<TValueType> angle, const Vector<3, TValueType>& axis)
	{
		const Vector<3, TValueType>		norm = math::Normalize(axis);
		const TValueType				xCpy = m_x, yCpy = m_y, zCpy = m_z;

		// lib math trig functions are not precise enough,
		// use the standard ones instead :(
		const TValueType			cosAngle = Cos(angle);
		const TValueType			sinAngle = Sin(angle);

		const TValueType			oneMinCos = static_cast<TValueType>(1) - cosAngle;
		const Vector<3, TValueType>		oneMinAxis = norm * oneMinCos;

		// Create multiplication matrix and multiply manually
		// TODO: Clean up
		TValueType				factorX = cosAngle + norm.m_x *
			norm.m_x * oneMinCos;

		TValueType				factorY = norm.m_x * norm.m_y *
			oneMinCos - norm.m_z * sinAngle;
		TValueType				factorZ = norm.m_x * norm.m_z *
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


	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::Scale(const Vector<3, TValueType>& other)
	{
		*this *= other;
	}


	template <CScalarType TValueType> inline
		std::string Vector<3, TValueType>::String() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << ',' << m_z << '}';

		return stream.str();
	}



	template <CScalarType TValueType> inline
		std::string Vector<3, TValueType>::StringLong() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << "Vector3{ x:" << m_x << ", y:" << m_y << ", z:" << m_z << " }";

		return stream.str();
	}


	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::Translate(const Vector<3, TValueType>& other)
	{
		*this += other;
	}



	template <CScalarType TValueType> inline
		TValueType& Vector<3, TValueType>::X()
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
		TValueType& Vector<3, TValueType>::Y()
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
		TValueType& Vector<3, TValueType>::Z()
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::GetX() const
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::GetY() const
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::GetZ() const
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>& Vector<3, TValueType>::operator=
		(const Vector<3, TValueType>& rhs)
	{
		// Copy assign
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_z = rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
		TValueType& Vector<3, TValueType>::operator[](int index)
	{
		switch (index)
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


	template <CScalarType TValueType> inline
		TValueType Vector<3, TValueType>::operator[](int index) const
	{
		switch (index)
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


	template <CScalarType TValueType> inline
		bool Vector<3, TValueType>::operator==(const Vector<3, TValueType>& rhs) const
	{
		// Compare all components
		return
			(
				AlmostEqual(m_x, rhs.m_x) &&
				AlmostEqual(m_y, rhs.m_y) &&
				AlmostEqual(m_z, rhs.m_z)
				);
	}



	template <CScalarType TValueType> inline
		bool Vector<3, TValueType>::operator!=
		(const Vector<3, TValueType>& rhs) const
	{
		return !(*this == rhs);
	}


	template <CScalarType TValueType> inline
		TValueType Dot
		(const Vector<3, TValueType>& first, const Vector<3, TValueType>& second)
	{
		return first.Dot(second);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Cross
		(const Vector<3, TValueType>& first, const Vector<3, TValueType>& second)
	{
		return first.Cross(second);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Reflect
		(const Vector<3, TValueType>& target, const Vector<3, TValueType>& ontoNormal)
	{
		Vector<3, TValueType>		result = target;

		// Return reflected copy
		result.ReflectOnto(ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> ReflectUnit
		(const Vector<3, TValueType>& target, const Vector<3, TValueType>& ontoNormal)
	{
		Vector<3, TValueType>		result = target;

		// Return reflected copy
		result.ReflectOntoUnit(ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Project
		(const Vector<3, TValueType>& target, const Vector<3, TValueType>& ontoVector)
	{
		Vector<3, TValueType>		result = target;

		// Return projected copy
		result.ProjectOnto(ontoVector);

		return result;
	}



	template <CScalarType TValueType> inline
		Vector<3, TValueType> Normalize(const Vector<3, TValueType>& target)
	{
		Vector<3, TValueType>		result = target;

		// Return normalized copy
		result.Normalize();

		return result;
	}


	template <CScalarType TValueType> inline
		TValueType Distance
		(const Vector<3, TValueType>& start, const Vector<3, TValueType>& end)
	{
		return start.DistanceFrom(end);
	}


	template <CScalarType TValueType> inline
		TValueType DistanceSquared
		(const Vector<3, TValueType>& start, const Vector<3, TValueType>& end)
	{
		return start.DistanceSquaredFrom(end);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Rotate
		(
			const Vector<3, TValueType>& target,
			Radian<TValueType> x, Radian<TValueType> y, Radian<TValueType> z
		)
	{
		Vector<3, TValueType>		result = target;

		// Return rotated copy
		result.Rotate(x, y, z);

		return result;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Rotate
		(
			const Vector<3, TValueType>& target,
			Radian<TValueType> angle, const Vector<3, TValueType>& axis
		)
	{
		Vector<3, TValueType>		result = target;

		// Return rotated copy
		result.Rotate(angle, axis);

		return result;
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::operator+
		(const Vector<3, TValueType>& rhs) const
	{
		return Vector<3, TValueType>(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::operator-
		(const Vector<3, TValueType>& rhs) const
	{
		return Vector<3, TValueType>(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::operator*
		(const Vector<3, TValueType>& rhs) const
	{
		return Vector<3, TValueType>(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::operator/
		(const Vector<3, TValueType>& rhs) const
	{
		return Vector<3, TValueType>(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z);
	}



	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::operator*(TValueType rhs) const
	{
		return Vector<3, TValueType>(m_x * rhs, m_y * rhs, m_z * rhs);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::operator/(TValueType rhs) const
	{
		rhs = static_cast<TValueType>(1) / rhs;

		return Vector<3, TValueType>(m_x * rhs, m_y * rhs, m_z * rhs);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType> Vector<3, TValueType>::operator-(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			return *this;

		else
			return Vector<3, TValueType>(-m_x, -m_y, -m_z);
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>& Vector<3, TValueType>::operator+=
		(const Vector<3, TValueType>& rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>& Vector<3, TValueType>::operator-=
		(const Vector<3, TValueType>& rhs)
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>& Vector<3, TValueType>::operator*=
		(const Vector<3, TValueType>& rhs)
	{
		m_x *= rhs.m_x;
		m_y *= rhs.m_y;
		m_z *= rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>& Vector<3, TValueType>::operator/=
		(const Vector<3, TValueType>& rhs)
	{
		m_x /= rhs.m_x;
		m_y /= rhs.m_y;
		m_z /= rhs.m_z;

		return*this;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>& Vector<3, TValueType>::operator*=(TValueType rhs)
	{
		m_x *= rhs;
		m_y *= rhs;
		m_z *= rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector<3, TValueType>& Vector<3, TValueType>::operator/=(TValueType rhs)
	{
		rhs = static_cast<TValueType>(1) / rhs;

		m_x *= rhs;
		m_y *= rhs;
		m_z *= rhs;

		return *this;
	}


	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Zero(void)
	{
		return Vector<3, TValueType>();
	}



	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::One(void)
	{
		return Vector<3, TValueType>(static_cast<TValueType>(1),
			static_cast<TValueType>(1),
			static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Up(void)
	{
		return Vector<3, TValueType>(static_cast<TValueType>(0),
			static_cast<TValueType>(1),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Down(void)
	{
		return Vector<3, TValueType>(static_cast<TValueType>(0),
			static_cast<TValueType>(-1),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Left(void)
	{
		return Vector<3, TValueType>(static_cast<TValueType>(-1),
			static_cast<TValueType>(0),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Right(void)
	{
		return Vector<3, TValueType>(static_cast<TValueType>(1),
			static_cast<TValueType>(0),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Back(void)
	{
		return Vector<3, TValueType>(static_cast<TValueType>(0),
			static_cast<TValueType>(0),
			static_cast<TValueType>(-1));
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Front(void)
	{
		return Vector<3, TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(0), static_cast<TValueType>(1));
	}

	// !Constants


	template <CScalarType TValueType> inline
		std::ostream& operator<<(std::ostream& os, Vector<3, TValueType> const& vector)
	{
		// Pass components to stream
		os << '{' << vector.GetX() << ',' << vector.GetY() << ',' <<
			vector.GetZ() << '}';

		return os;
	}


	template <CScalarType TValueType> inline
		std::istream& operator>>(std::istream& is, Vector<3, TValueType>& vector)
	{
		char	discard;

		// Get input from stream
		is >> discard >> vector.X() >> discard >> vector.Y()
			>> discard >> vector.Z() >> discard;

		return is;
	}






	
	template<CScalarType TValueType>
	Vector<3, TValueType> Vector<3, TValueType>::Lerp(const Vector& start, const Vector& end, TValueType time)
	{
		return (end - start) * time + start;
	}

}

namespace LibMath = math;
namespace lm = LibMath;

#endif