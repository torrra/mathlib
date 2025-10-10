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
	class Vector3 : public Vector<3, TValueType>
	//class Vector<3, TValueType>
	{
	public:

		using Vector<3, TValueType>::Vector;
		
		inline				Vector3(TValueType x, TValueType y, TValueType z);
		
		//~Vector3(void) = default;

		// Get angle from this Vector3 to another
		inline
		Radian<TValueType>	AngleFrom(const Vector3& other)				const;

		// Get angle from this Vector3 to another unit Vector3
		// Should be used if this Vector3 and the other are both
		// unit Vector3s
		inline
		Radian<TValueType>	AngleFromUnit(const Vector3& other)			const;

		// Compute cross product with another
		// this x other
		inline Vector3		Cross(const Vector3& other)					const;

		// Get distance between 2 points
		inline TValueType	DistanceFrom(const Vector3& other)				const;

		// Get distance squared between two points
		inline TValueType	DistanceSquaredFrom(const Vector3& other)		const;

		// Get distance between 2 points disregarding the z axis
		inline TValueType	Distance2DFrom(Vector3 const&)					const;

		// Get distance squared between two points disregarding the z axis
		inline TValueType	Distance2DSquaredFrom(Vector3 const&)			const;

		// Compute dot product of two Vector3s
		inline TValueType	Dot(const Vector3& other)						const;

		// Is this Vector3's magnitude longer than another ?
		inline bool			IsLongerThan(const Vector3& other)				const;

		// Is this Vector3's magnitude shorter than another ?
		inline bool			IsShorterThan(const Vector3& other)			const;

		// Is this Vector3's magnitude equal to 1 ?
		inline bool			IsUnitVector(void)								const;

		inline TValueType	Magnitude(void)									const;
		inline TValueType	MagnitudeSquared(void)							const;

		// Adjust Vector3 to turn into unit Vector3
		inline void			Normalize(void);

		// Get copy of this Vector3 as a unit Vector3
		inline Vector3		Normalized(void)								const;

		// Project this Vector3 onto another
		inline void			ProjectOnto(const Vector3& other);

		// Reflect this Vector3 onto another
		inline void			ReflectOnto(const Vector3& axis);

		// Reflect this Vector3 onto a UNIT Vector3
		inline void			ReflectOntoUnit(const Vector3& axis);

		// Rotate this Vector3 around the all 3 axes
		inline void			Rotate
		(
			Radian<TValueType> angleX,
			Radian<TValueType> angleY,
			Radian<TValueType> angleZ
		);

		// Rotate this Vector3 around an arbitrary axis
		inline void			Rotate
		(Radian<TValueType> angle, const Vector3& axis);

		// Multiply this Vector3's components by another's
		inline void			Scale(const Vector3& other);

		// Get components as string
		inline std::string	String(void)									const;

		// Get components as verbose string
		inline std::string	StringLong(void)								const;

		// Add another Vector3's components to this one's
		inline void			Translate(const Vector3& other);

		// Accessors

		inline TValueType&	X(void);
		inline TValueType&	Y(void);
		inline TValueType&	Z(void);

		inline TValueType	GetX(void)										const;
		inline TValueType	GetY(void)										const;
		inline TValueType	GetZ(void)										const;


		inline Vector3&		operator=(const Vector3& rhs);

		

		// Boolean test operators

		inline bool			operator==(const Vector3& rhs)					const;
		inline bool			operator!=(const Vector3& rhs)					const;

		// Component-wise operations

		inline Vector3			operator+(const Vector3& rhs)				const;
		inline Vector3			operator-(const Vector3& rhs)				const;
		inline Vector3			operator*(const Vector3& rhs)				const;
		inline Vector3			operator/(const Vector3& rhs)				const;

		// Multiply all components by a single scalar
		inline Vector3			operator*(TValueType rhs)					const;

		// Divide all components by a single scalar
		inline Vector3			operator/(TValueType rhs)					const;

		// Flip sign of both components
		inline Vector3			operator-(void)								const;


		// Component-wise operations

		inline Vector3&		operator+=(const Vector3& rhs);
		inline Vector3&		operator-=(const Vector3& rhs);
		inline Vector3&		operator*=(const Vector3& rhs);
		inline Vector3&		operator/=(const Vector3& rhs);

		// Multiply all components by a single scalar
		inline Vector3&		operator*=(TValueType rhs);

		// Divide all components by a single scalar
		inline Vector3&		operator/=(TValueType rhs);


		// Constants

		inline static Vector3	Zero(void);
		inline static Vector3	One(void);
		inline static Vector3	Up(void);
		inline static Vector3	Down(void);
		inline static Vector3	Left(void);
		inline static Vector3	Right(void);
		inline static Vector3	Back(void);
		inline static Vector3	Front(void);
		inline static Vector3	Lerp(const Vector3& start, const Vector3& end, TValueType time);

	};


	using Vector3f = Vector3<float>;
	using Vector3i = Vector3<int32_t>;
	using Vector3d = Vector3<double>;

	// Non-member functions (similar to member functions but provided for readability)

	template <CScalarType TValueType> inline
	TValueType				Dot
	(const Vector3<TValueType>& first, const Vector3<TValueType>& second);

	template <CScalarType TValueType> inline
	Vector3<TValueType>		Cross
	(const Vector3<TValueType>& first, const Vector3<TValueType>& second);

	template <CScalarType TValueType> inline
	Vector3<TValueType>				Reflect
	(const Vector3<TValueType>& target, const Vector3<TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector3<TValueType>				ReflectUnit
	(const Vector3<TValueType>& target, const Vector3<TValueType>& ontoNormal);


	template <CScalarType TValueType> inline
	Vector3<TValueType>				Project
	(const Vector3<TValueType>& target, const Vector3<TValueType>& ontoVector);

	template <CScalarType TValueType> inline
	Vector3<TValueType>				Normalize(const Vector3<TValueType>& target);


	template <CScalarType TValueType> inline
	TValueType				Distance
	(const Vector3<TValueType>& start, const Vector3<TValueType>& end);


	template <CScalarType TValueType> inline
	TValueType				DistanceSquared
	(const Vector3<TValueType>& start, const Vector3<TValueType>& end);


	template <CScalarType TValueType> inline
	Vector3<TValueType>				Rotate
	(
		const Vector3<TValueType>& target,
		Radian<TValueType> angleX,
		Radian<TValueType> angleY,
		Radian<TValueType> angleZ
	);


	template <CScalarType TValueType> inline
	Vector3<TValueType>				Rotate
	(
		const Vector3<TValueType>& target,
		Radian<TValueType> angle, const Vector3<TValueType>& axis
	);

	// Send a vector's components to an output stream
	template <CScalarType TValueType> inline
	std::ostream&		operator<<
	(std::ostream& os, Vector3<TValueType> const& vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream&		operator>>
	(std::istream& is, Vector3<TValueType>& vector);


	// ---- Implementation ---


	template <CScalarType TValueType> inline
		Vector3<TValueType>::Vector3(TValueType x, TValueType y, TValueType z)
	{
		Vector<3, TValueType>::m_values[0] = x;
		Vector<3, TValueType>::m_values[1] = y;
		Vector<3, TValueType>::m_values[2] = z;
	}


	template <CScalarType TValueType> inline
		Radian<TValueType> Vector3<TValueType>::AngleFrom
		(const Vector3<TValueType>& other) const
	{
		if constexpr (std::is_integral<TValueType>::value)
			return Radian<TValueType>(0);

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
		Radian<TValueType> Vector3<TValueType>::AngleFromUnit
		(const Vector3<TValueType>& other) const
	{
		if constexpr (std::is_integral<TValueType>::value)
			return Radian<TValueType>(0);

		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		else
			return Acos(Clamp(Dot(other), static_cast<TValueType>(MIN_COS),
				static_cast<TValueType>(MAX_COS)));
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::Cross
		(const Vector3<TValueType>& other) const
	{
		// Compute cross product
		return Vector3<TValueType>
			(
				(GetY() * other.GetZ()) - (GetZ() * other.GetY()),
				(GetZ() * other.GetX()) - (GetX() * other.GetZ()),
				(GetX() * other.GetY()) - (GetY() * other.GetX())
			);

	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::DistanceFrom
		(const Vector3<TValueType>& other) const
	{
		return SquareRoot(DistanceSquaredFrom(other));
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::DistanceSquaredFrom
		(const Vector3<TValueType>& other) const
	{
		// Find distance vector and get magnitude
		return (other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::Distance2DFrom
		(const Vector3<TValueType>& other) const
	{
		return SquareRoot(Distance2DSquaredFrom(other));
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::Distance2DSquaredFrom(const Vector3<TValueType>& other) const
	{
		// Ignore z axis
		Vector2<TValueType>		dist2D =
		{
			static_cast<TValueType>(other.GetX() - GetX()),
			static_cast<TValueType>(other.GetY() - GetY())
		};

		// Find distance vector and get magnitude
		return dist2D.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::Dot
		(const Vector3<TValueType>& other) const
	{
		// Multiply components
		return (GetX() * other.GetX()) + (GetY() * other.GetY()) + (GetZ() * other.GetZ());
	}



	template <CScalarType TValueType> inline
		bool Vector3<TValueType>::IsLongerThan
		(const Vector3<TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		bool Vector3<TValueType>::IsShorterThan
		(const Vector3<TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
		bool Vector3<TValueType>::IsUnitVector() const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}



	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::MagnitudeSquared() const
	{
		// Square components
		return Dot(*this);
	}



	template <CScalarType TValueType> inline
		void Vector3<TValueType>::Normalize()
	{
		TValueType		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, static_cast<TValueType>(0), std::numeric_limits<TValueType>::epsilon()))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		// Only divide once
		else
			invMagnitude = static_cast<TValueType>(1) / invMagnitude;


		X() *= invMagnitude;
		Y() *= invMagnitude;
		Z() *= invMagnitude;
	}



	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::Normalized(void) const
	{
		Vector3<TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}



	template <CScalarType TValueType> inline
		void Vector3<TValueType>::ProjectOnto(const Vector3<TValueType>& other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = other.MagnitudeSquared();
		TValueType		projFactor = Dot(other) / squareMagnitude;

		X() = other.GetX() * projFactor;
		Y() = other.GetY() * projFactor;
		Z() = other.GetZ() * projFactor;

	}



	template <CScalarType TValueType> inline
		void Vector3<TValueType>::ReflectOnto(const Vector3<TValueType>& axis)
	{
		// Only reflect onto unit vector
		Vector3<TValueType>		normal = math::Normalize(axis);

		// Apply reflection formula
		*this -= normal * (Dot(normal) * static_cast<TValueType>(2));
	}


	template <CScalarType TValueType> inline
		void Vector3<TValueType>::ReflectOntoUnit(const Vector3<TValueType>& axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= axis * (Dot(axis) * static_cast<TValueType>(2));
	}


	template <CScalarType TValueType> inline
		void Vector3<TValueType>::Rotate
		(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
	{
		if constexpr (std::is_unsigned_v<TValueType> || std::is_integral_v<TValueType>)
			throw std::logic_error("cannot rotate unsigned or integral vector");

		else
			/*(*this) = RotateWithQuat(*this, angleX, angleY, angleZ); */

		{
			Vector3<TValueType>		copy = *this;

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
		void Vector3<TValueType>::Rotate
		(Radian<TValueType> angle, const Vector3<TValueType>& axis)
	{
		const Vector3<TValueType>		norm = math::Normalize(axis);
		const TValueType				xCpy = X(), yCpy = Y(), zCpy = Z();

		// lib math trig functions are not precise enough,
		// use the standard ones instead :(
		const TValueType			cosAngle = Cos(angle);
		const TValueType			sinAngle = Sin(angle);

		const TValueType			oneMinCos = static_cast<TValueType>(1) - cosAngle;
		const Vector3<TValueType>		oneMinAxis = norm * oneMinCos;

		// Create multiplication matrix and multiply manually
		// TODO: Clean up
		TValueType				factorX = cosAngle + norm.GetX() *
			norm.GetX() * oneMinCos;

		TValueType				factorY = norm.GetX() * norm.GetY() *
			oneMinCos - norm.GetZ() * sinAngle;
		TValueType				factorZ = norm.GetX() * norm.GetZ() *
			oneMinCos + norm.GetY() * sinAngle;

		X() = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = norm.GetY() * norm.GetX() *
			oneMinCos + norm.GetZ() * sinAngle;

		factorY = cosAngle + norm.GetY() *
			norm.GetY() * oneMinCos;

		factorZ = norm.GetY() * norm.GetZ() *
			oneMinCos - norm.GetX() * sinAngle;

		Y() = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = norm.GetZ() * norm.GetX() *
			oneMinCos - norm.GetY() * sinAngle;

		factorY = norm.GetZ() * norm.GetY() *
			oneMinCos + norm.GetX() * sinAngle;

		factorZ = cosAngle + norm.GetZ() *
			norm.GetZ() * oneMinCos;

		Z() = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

	}


	template <CScalarType TValueType> inline
		void Vector3<TValueType>::Scale(const Vector3<TValueType>& other)
	{
		*this *= other;
	}


	template <CScalarType TValueType> inline
		std::string Vector3<TValueType>::String() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << GetX() << ',' << GetY() << ',' << GetZ() << '}';

		return stream.str();
	}



	template <CScalarType TValueType> inline
		std::string Vector3<TValueType>::StringLong() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << "Vector3{ x:" << GetX() << ", y:" << GetY() << ", z:" << GetZ() << " }";

		return stream.str();
	}


	template <CScalarType TValueType> inline
		void Vector3<TValueType>::Translate(const Vector3<TValueType>& other)
	{
		*this += other;
	}



	template <CScalarType TValueType> inline
		TValueType& Vector3<TValueType>::X()
	{
		return Vector3<TValueType>::m_values[0];
	}


	template <CScalarType TValueType> inline
		TValueType& Vector3<TValueType>::Y()
	{
		return Vector3<TValueType>::m_values[1];
	}


	template <CScalarType TValueType> inline
		TValueType& Vector3<TValueType>::Z()
	{
		return Vector3<TValueType>::m_values[2];
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::GetX() const
	{
		return Vector3<TValueType>::m_values[0];
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::GetY() const
	{
		return Vector3<TValueType>::m_values[1];
	}


	template <CScalarType TValueType> inline
		TValueType Vector3<TValueType>::GetZ() const
	{
		return Vector3<TValueType>::m_values[2];
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType>& Vector3<TValueType>::operator=
		(const Vector3<TValueType>& rhs)
	{
		// Copy assign
		X() = rhs.GetX();
		Y() = rhs.GetY();
		Z() = rhs.GetZ();

		return *this;
	}


	template <CScalarType TValueType> inline
		bool Vector3<TValueType>::operator==(const Vector3<TValueType>& rhs) const
	{
		// Compare all components
		return
			(
				AlmostEqual(GetX(), rhs.GetX()) &&
				AlmostEqual(GetY(), rhs.GetY()) &&
				AlmostEqual(GetZ(), rhs.GetZ())
				);
	}



	template <CScalarType TValueType> inline
		bool Vector3<TValueType>::operator!=
		(const Vector3<TValueType>& rhs) const
	{
		return !(*this == rhs);
	}


	template <CScalarType TValueType> inline
		TValueType Dot
		(const Vector3<TValueType>& first, const Vector3<TValueType>& second)
	{
		return first.Dot(second);
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Cross
		(const Vector3<TValueType>& first, const Vector3<TValueType>& second)
	{
		return first.Cross(second);
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Reflect
		(const Vector3<TValueType>& target, const Vector3<TValueType>& ontoNormal)
	{
		Vector3<TValueType>		result = target;

		// Return reflected copy
		result.ReflectOnto(ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> ReflectUnit
		(const Vector3<TValueType>& target, const Vector3<TValueType>& ontoNormal)
	{
		Vector3<TValueType>		result = target;

		// Return reflected copy
		result.ReflectOntoUnit(ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Project
		(const Vector3<TValueType>& target, const Vector3<TValueType>& ontoVector)
	{
		Vector3<TValueType>		result = target;

		// Return projected copy
		result.ProjectOnto(ontoVector);

		return result;
	}



	template <CScalarType TValueType> inline
		Vector3<TValueType> Normalize(const Vector3<TValueType>& target)
	{
		Vector3<TValueType>		result = target;

		// Return normalized copy
		result.Normalize();

		return result;
	}


	template <CScalarType TValueType> inline
		TValueType Distance
		(const Vector3<TValueType>& start, const Vector3<TValueType>& end)
	{
		return start.DistanceFrom(end);
	}


	template <CScalarType TValueType> inline
		TValueType DistanceSquared
		(const Vector3<TValueType>& start, const Vector3<TValueType>& end)
	{
		return start.DistanceSquaredFrom(end);
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Rotate
		(
			const Vector3<TValueType>& target,
			Radian<TValueType> x, Radian<TValueType> y, Radian<TValueType> z
		)
	{
		Vector3<TValueType>		result = target;

		// Return rotated copy
		result.Rotate(x, y, z);

		return result;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Rotate
		(
			const Vector3<TValueType>& target,
			Radian<TValueType> angle, const Vector3<TValueType>& axis
		)
	{
		Vector3<TValueType>		result = target;

		// Return rotated copy
		result.Rotate(angle, axis);

		return result;
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::operator+
		(const Vector3<TValueType>& rhs) const
	{
		return Vector3<TValueType>(GetX() + rhs.GetX(), GetY() + rhs.GetY(), GetZ() + rhs.GetZ());
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::operator-
		(const Vector3<TValueType>& rhs) const
	{
		return Vector3<TValueType>(GetX() - rhs.GetX(), GetY() - rhs.GetY(), GetZ() - rhs.GetZ());
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::operator*
		(const Vector3<TValueType>& rhs) const
	{
		return Vector3<TValueType>(GetX() * rhs.GetX(), GetY() * rhs.GetY(), GetZ() * rhs.GetZ());
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::operator/
		(const Vector3<TValueType>& rhs) const
	{
		return Vector3<TValueType>(GetX() / rhs.GetX(), GetY() / rhs.GetY(), GetZ() / rhs.GetZ());
	}



	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::operator*(TValueType rhs) const
	{
		return Vector3<TValueType>(GetX() * rhs, GetY() * rhs, GetZ() * rhs);
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::operator/(TValueType rhs) const
	{
		rhs = static_cast<TValueType>(1) / rhs;

		return Vector3<TValueType>(GetX() * rhs, GetY() * rhs, GetZ() * rhs);
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType> Vector3<TValueType>::operator-(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			return *this;

		else
			return Vector3<TValueType>(-GetX(), -GetY(), -GetZ());
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType>& Vector3<TValueType>::operator+=
		(const Vector3<TValueType>& rhs)
	{
		X() += rhs.GetX();
		Y() += rhs.GetY();
		Z() += rhs.GetZ();

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType>& Vector3<TValueType>::operator-=
		(const Vector3<TValueType>& rhs)
	{
		X() -= rhs.GetX();
		Y() -= rhs.GetY();
		Z() -= rhs.GetZ();

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType>& Vector3<TValueType>::operator*=
		(const Vector3<TValueType>& rhs)
	{
		X() *= rhs.GetX();
		Y() *= rhs.GetY();
		Z() *= rhs.GetZ();

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType>& Vector3<TValueType>::operator/=
		(const Vector3<TValueType>& rhs)
	{
		X() /= rhs.GetX();
		Y() /= rhs.GetY();
		Z() /= rhs.GetZ();

		return*this;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType>& Vector3<TValueType>::operator*=(TValueType rhs)
	{
		X() *= rhs;
		Y() *= rhs;
		Z() *= rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
		Vector3<TValueType>& Vector3<TValueType>::operator/=(TValueType rhs)
	{
		rhs = static_cast<TValueType>(1) / rhs;

		X() *= rhs;
		Y() *= rhs;
		Z() *= rhs;

		return *this;
	}


	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::Zero(void)
	{
		return Vector3<TValueType>();
	}



	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::One(void)
	{
		return Vector3<TValueType>(static_cast<TValueType>(1),
			static_cast<TValueType>(1),
			static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::Up(void)
	{
		return Vector3<TValueType>(static_cast<TValueType>(0),
			static_cast<TValueType>(1),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::Down(void)
	{
		return Vector3<TValueType>(static_cast<TValueType>(0),
			static_cast<TValueType>(-1),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::Left(void)
	{
		return Vector3<TValueType>(static_cast<TValueType>(-1),
			static_cast<TValueType>(0),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::Right(void)
	{
		return Vector3<TValueType>(static_cast<TValueType>(1),
			static_cast<TValueType>(0),
			static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::Back(void)
	{
		return Vector3<TValueType>(static_cast<TValueType>(0),
			static_cast<TValueType>(0),
			static_cast<TValueType>(-1));
	}


	template <CScalarType TValueType> inline
	Vector3<TValueType> Vector3<TValueType>::Front(void)
	{
		return Vector3<TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(0), static_cast<TValueType>(1));
	}

	// !Constants


	template <CScalarType TValueType> inline
		std::ostream& operator<<(std::ostream& os, Vector3<TValueType> const& vector)
	{
		// Pass components to stream
		os << '{' << vector.GetX() << ',' << vector.GetY() << ',' <<
			vector.GetZ() << '}';

		return os;
	}


	template <CScalarType TValueType> inline
		std::istream& operator>>(std::istream& is, Vector3<TValueType>& vector)
	{
		char	discard;

		// Get input from stream
		is >> discard >> vector.X() >> discard >> vector.Y()
			>> discard >> vector.Z() >> discard;

		return is;
	}






	
	template<CScalarType TValueType>
	Vector3<TValueType> Vector3<TValueType>::Lerp(const Vector3<TValueType>& start, const Vector3<TValueType>& end, TValueType time)
	{
		return (end - start) * time + start;
	}

}

namespace LibMath = math;
namespace lm = LibMath;

#endif