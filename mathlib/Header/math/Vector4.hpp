#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include <string>
#include <cmath>
#include <sstream>

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"

#include "Trigonometry.hpp"
#include "Arithmetic.hpp"

#include "Angle.hpp"

#include "Vector3.hpp"

namespace math
{
	template <CScalarType TValueType>

	//class Vector4
	class Vector4 : public Vector<4, TValueType>
	{
	public:

		// Constructors / destructor
		using Vector<4, TValueType>::Vector;

	inline			Vector4(TValueType x, TValueType y, TValueType z, TValueType w);


					//~Vector4(void) = default;

		// Get angle from this vector to another
	inline			Radian<TValueType>
					AngleFrom(const Vector4& other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
	inline			Radian<TValueType>
					AngleFromUnit(const Vector4& other)				const;

		// Get distance between 2 points
	inline	TValueType			DistanceFrom(const Vector4& other)					const;

		// Get distance squared between two points
	inline	TValueType			DistanceSquaredFrom(const Vector4& other)			const;

		// Get distance between 2 points disregarding the z and w axes
	inline	TValueType			Distance2DFrom(Vector4 const& other)				const;

		// Get distance squared between two points disregarding the z and w axes
	inline	TValueType			Distance2DSquaredFrom(Vector4 const& other)		const;

		// Get distance between two points disregarding the w axis
	inline	TValueType			Distance3DFrom(Vector4 const& other)				const;

		// Get distance squared between two points disregarding the w axis
	inline	TValueType			Distance3DSquaredFrom(Vector4 const& other)		const;


		// Compute dot product of two vectors
	inline	TValueType			Dot(const Vector4& other)							const;

		// Is this vector's magnitude longer than another ?
	inline	bool			IsLongerThan(const Vector4& other)					const;

		// Is this vector's magnitude shorter than another ?
	inline	bool			IsShorterThan(const Vector4& other)				const;

		// Is this vector's magnitude equal to 1 ?
	inline	bool			IsUnitVector(void)									const;

	inline	TValueType			Magnitude(void)										const;
	inline	TValueType			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
	inline	void			Normalize(void);

		// Get copy of this vector as a unit vector
	inline	Vector4			Normalized(void)									const;

		// Project this vector onto another
	inline	void			ProjectOnto(const Vector4& other);

		// Reflect this vector onto another
	inline	void			ReflectOnto(const Vector4& axis);

		// Reflect this vector onto a UNIT vector
	inline	void			ReflectOntoUnit(const Vector4& axis);

		// Rotate this vector around the all 3 axes (not w)
	inline	void			Rotate(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ);

		// Rotate this vector around an arbitrary 3D axis
	inline	void			Rotate(Radian<TValueType> angle, const Vector3<TValueType>& axis);

		// Multiply this vector's components by another's
	inline	void			Scale(const Vector4& other);

		// Get components as string
	inline	std::string		String(void)										const;

		// Get components as verbose string
	inline	std::string		StringLong(void)									const;

		// Add another vector's components to this one's
	inline	void			Translate(const Vector4& other);


		// Accessors

	inline	TValueType&			X(void);
	inline	TValueType&			Y(void);
	inline	TValueType&			Z(void);
	inline	TValueType&			W(void);

	inline	TValueType			GetX(void)											const;
	inline	TValueType			GetY(void)											const;
	inline	TValueType			GetZ(void)											const;
	inline	TValueType			GetW(void)											const;


	inline	Vector4&		operator=(const Vector4& rhs);

		// Boolean test operators

	inline	bool			operator==(const Vector4& rhs)						const;
	inline	bool			operator!=(const Vector4& rhs)						const;


		// Component-wise operations

	inline	Vector4			operator+(const Vector4& rhs)						const;
	inline	Vector4			operator-(const Vector4& rhs)						const;
	inline	Vector4			operator*(const Vector4& rhs)						const;
	inline	Vector4			operator/(const Vector4& rhs)						const;


		// Multiply all components by a single scalar
	inline	Vector4			operator*(TValueType rhs)								const;

		// Divide all components by a single scalar
	inline	Vector4			operator/(TValueType rhs)								const;

		// Flip sign of both components
	inline	Vector4			operator-(void)										const;


		// Component-wise operations

	inline	Vector4&		operator+=(const Vector4& rhs);
	inline	Vector4&		operator-=(const Vector4& rhs);
	inline	Vector4&		operator*=(const Vector4& rhs);
	inline	Vector4&		operator/=(const Vector4& rhs);

		// Multiply all components by a single scalar
	inline	Vector4&		operator*=(TValueType rhs);

		// Divide all components by a single scalar
	inline	Vector4&		operator/=(TValueType rhs);


		// Constants

	inline	static Vector4	Zero(void);
	inline	static Vector4	One(void);
	inline	static Vector4	Up(void);
	inline	static Vector4	Down(void);
	inline	static Vector4	Left(void);
	inline	static Vector4	Right(void);
	inline	static Vector4  Back(void);
	inline	static Vector4  Front(void);

	};


	using Vector4f = Vector4<float>;
	using Vector4i = Vector4<int32_t>;
	using Vector4d = Vector4<double>;


	// Non-member functions (similar to member functions but provided for readability)
	template <CScalarType TValueType> inline
	TValueType				Dot(const Vector4<TValueType>& first, const Vector4<TValueType>& second);

	template <CScalarType TValueType> inline
	Vector4<TValueType>			Reflect(const Vector4<TValueType>& target, const Vector4<TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector4<TValueType>				ReflectUnit(const Vector4<TValueType>& target, const Vector4<TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector4<TValueType>				Project(const Vector4<TValueType>& target, const Vector4<TValueType>& ontoVector);


	template <CScalarType TValueType> inline
	Vector4<TValueType>				Normalize(const Vector4<TValueType>& target);


	template <CScalarType TValueType> inline
	TValueType				Distance(const Vector4<TValueType>& start, const Vector4<TValueType>& end);

	template <CScalarType TValueType> inline
	TValueType				DistanceSquared(const Vector4<TValueType>& start, const Vector4<TValueType>& end);

	template <CScalarType TValueType> inline
	Vector4<TValueType>				Rotate
	(
		const Vector4<TValueType>& target, Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ
	);


	template <CScalarType TValueType> inline
	Vector4<TValueType>				Rotate
	(
		const Vector4<TValueType>& target, Radian<TValueType> angle, const Vector3<TValueType>& axis
	);


	// Send a vector's components to an output stream
	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& os, Vector4<TValueType> const& vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& is, Vector4<TValueType>& vector);







 // ---- Implementation ----


	template<CScalarType TValueType>
	inline Vector4<TValueType>::Vector4(TValueType x, TValueType y, TValueType z, TValueType w)
	{
		Vector<4, TValueType>::m_values[0] = x;
		Vector<4, TValueType>::m_values[1] = y;
		Vector<4, TValueType>::m_values[2] = z;
		Vector<4, TValueType>::m_values[3] = w;
	}

	template <CScalarType TValueType> inline
	Radian<TValueType> Vector4<TValueType>::AngleFrom(const Vector4<TValueType>& other) const
	{
		if constexpr (std::is_integral<TValueType>::value)
			throw std::logic_error("cannot find angle between vectors of integral types");

		else
		{
			TValueType		magnitudes = MagnitudeSquared() * other.MagnitudeSquared();

			// Only run square root once
			magnitudes = SquareRoot(magnitudes);

			// Transform dot product equation to get cos angle,
			// then run acos
			return Acos(Dot(other) / magnitudes);
		}
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector4<TValueType>::AngleFromUnit(const Vector4<TValueType>& other) const
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
	TValueType Vector4<TValueType>::DistanceFrom(const Vector4<TValueType>& other) const
	{
		return SquareRoot(DistanceSquaredFrom(other));
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::DistanceSquaredFrom(const Vector4<TValueType>& other) const
	{
		// Find distance vector and get magnitude
		return (other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::Distance2DFrom(Vector4<TValueType> const& other) const
	{
		// Ignore z and w axes
		Vector2<TValueType>		self2D = { GetX(), GetY() };
		Vector2<TValueType>		other2D = { other.GetX(), other.GetY() };


		return self2D.DistanceFrom(other2D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::Distance2DSquaredFrom(Vector4<TValueType> const& other) const
	{
		// Ignore z and w axes
		Vector2<TValueType>		self2D = { GetX(), GetY() };
		Vector2<TValueType>		other2D = { other.GetX(), other.GetY() };


		return self2D.DistanceSquaredFrom(other2D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::Distance3DFrom(Vector4<TValueType> const& other) const
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { GetX(), GetY(), GetZ() };
		Vector3<TValueType>		other3D = { other.GetX(), other.GetY(), other.GetZ() };


		return self3D.DistanceFrom(other3D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::Distance3DSquaredFrom(Vector4<TValueType> const& other) const
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { GetX(), GetY(), GetZ() };
		Vector3<TValueType>		other3D = { other.GetX(), other.GetY(), other.GetZ() };


		return self3D.DistanceSquaredFrom(other3D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::Dot(const Vector4<TValueType>& other) const
	{
		// Multiply components
		return (GetX() * other.GetX()) + (GetY() * other.GetY()) +
			(GetZ() * other.GetZ()) + (GetW() * other.GetW());
	}


	template <CScalarType TValueType> inline
	bool Vector4<TValueType>::IsLongerThan(const Vector4<TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector4<TValueType>::IsShorterThan(const Vector4<TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector4<TValueType>::IsUnitVector(void) const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::Magnitude(void) const
	{
		return SquareRoot(MagnitudeSquared());
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::MagnitudeSquared(void) const
	{
		// Square components
		return Dot(*this);
	}


	template <CScalarType TValueType> inline
	void Vector4<TValueType>::Normalize(void)
	{
		// Only divide once
		TValueType		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, static_cast<TValueType>(0), std::numeric_limits<TValueType>::epsilon()))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		else
			invMagnitude = static_cast<TValueType>(1) / invMagnitude;


		X() *= invMagnitude;
		Y() *= invMagnitude;
		Z() *= invMagnitude;
		W() *= invMagnitude;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Normalized(void) const
	{
		Vector4<TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}


	template <CScalarType TValueType> inline
	void Vector4<TValueType>::ProjectOnto(const Vector4<TValueType>& other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = other.MagnitudeSquared();
		TValueType		projFactor = Dot(other) / squareMagnitude;

		X() = other.GetX() * projFactor;
		Y() = other.GetY() * projFactor;
		Z() = other.GetZ() * projFactor;
		W() = other.GetW() * projFactor;
	}


	template <CScalarType TValueType> inline
	void Vector4<TValueType>::ReflectOnto(const Vector4<TValueType>& axis)
	{
		// Only reflect onto unit vector
		Vector4<TValueType>		normal = math::Normalize(axis);

		*this -= normal * (Dot(normal) * static_cast<TValueType>(2));
	}


	template <CScalarType TValueType> inline
	void Vector4<TValueType>::ReflectOntoUnit(const Vector4<TValueType>& axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= axis * (Dot(axis) * static_cast<TValueType>(2));
	}



	template <CScalarType TValueType> inline
	void Vector4<TValueType>::Rotate(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
	{
		if constexpr (std::is_unsigned_v<TValueType> || std::is_integral_v<TValueType>)
			throw std::logic_error("Cannot rotate unsigned or integral vector");


		else
		{
			Vector4<TValueType>		copy = *this;

			TValueType		cosYaw = Cos(angleZ), sinYaw = Sin(angleZ);
			TValueType		cosPitch = Cos(angleX), sinPitch = Sin(angleX);
			TValueType		cosRoll = Cos(angleY), sinRoll = Sin(angleY);
			TValueType		rowResult;

			// Create rotation matrix
			TValueType		rotation[][4] =
			{
				{
					cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
					-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
					sinYaw * cosPitch,
					static_cast<TValueType>(0)
				},


				{
					sinRoll * cosPitch,
					cosRoll * cosPitch,
					-sinPitch,
					static_cast<TValueType>(0)
				},


				{
					-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
					sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,
					cosYaw * cosPitch,
					static_cast<TValueType>(0)
				},

				{ static_cast<TValueType>(0), static_cast<TValueType>(0),
				 static_cast<TValueType>(0), static_cast<TValueType>(1)}
			};


			for (int row = 0; row < 4; ++row)
			{
				rowResult = static_cast<TValueType>(0);

				for (int column = 0; column < 4; ++column)
				{
					rowResult += rotation[row][column] * copy[column];
				}

				(*this)[row] = rowResult;
			}
		}


	}



	template <CScalarType TValueType> inline
	void Vector4<TValueType>::Rotate(Radian<TValueType> angle, const Vector3<TValueType>& axis)
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { GetX(), GetY(), GetZ() };

		// Rotate without w
		self3D.Rotate(angle, axis);

		X() = self3D.GetX();
		Y() = self3D.GetY();
		Z() = self3D.GetZ();
	}


	template <CScalarType TValueType> inline
	void Vector4<TValueType>::Scale(const Vector4<TValueType>& other)
	{
		*this *= other;
	}



	template <CScalarType TValueType> inline
	std::string Vector4<TValueType>::String(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << GetX() << ',' << GetY() << ',' << GetZ() << ',' << GetW() << '}';

		return stream.str();
	}


	template <CScalarType TValueType> inline
	std::string Vector4<TValueType>::StringLong(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << "Vector4{ x:" << GetX() << ", y:" << GetY() << ", z:"
			<< GetZ() << ", w:" << GetW() << " }";

		return stream.str();
	}



	template <CScalarType TValueType> inline
	void Vector4<TValueType>::Translate(const Vector4<TValueType>& other)
	{
		*this += other;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector4<TValueType>::X(void)
	{
		return Vector<4, TValueType>::m_values[0];
	}



	template <CScalarType TValueType> inline
	TValueType& Vector4<TValueType>::Y(void)
	{
		return Vector<4, TValueType>::m_values[1];
	}



	template <CScalarType TValueType> inline
	TValueType& Vector4<TValueType>::Z(void)
	{
		return Vector<4, TValueType>::m_values[2];
	}


	template <CScalarType TValueType> inline
	TValueType& Vector4<TValueType>::W(void)
	{
		return Vector<4, TValueType>::m_values[3];
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::GetX(void) const
	{
		return Vector<4, TValueType>::m_values[0];
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::GetY(void) const
	{
		return Vector<4, TValueType>::m_values[1];
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::GetZ(void) const
	{
		return Vector<4, TValueType>::m_values[2];
	}


	template <CScalarType TValueType> inline
	TValueType Vector4<TValueType>::GetW(void) const
	{
		return Vector<4, TValueType>::m_values[3];
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType>& Vector4<TValueType>::operator=(const Vector4<TValueType>& rhs)
	{
		// Copy assign
		X() = rhs.GetX();
		Y() = rhs.GetY();
		Z() = rhs.GetZ();
		W() = rhs.GetW();

		return *this;
	}


	template <CScalarType TValueType> inline
	bool Vector4<TValueType>::operator==(const Vector4<TValueType>& rhs) const
	{
		// Compare all components
		return
			(
				AlmostEqual(GetX(), rhs.GetX()) &&
				AlmostEqual(GetY(), rhs.GetY()) &&
				AlmostEqual(GetZ(), rhs.GetZ()) &&
				AlmostEqual(GetW(), rhs.GetW())

				);
	}



	template <CScalarType TValueType> inline
	bool Vector4<TValueType>::operator!=(const Vector4<TValueType>& rhs) const
	{
		return !(*this == rhs);
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::operator+(const Vector4<TValueType>& rhs) const
	{
		return Vector4<TValueType>(GetX() + rhs.GetX(), GetY() + rhs.GetY(),
			GetZ() + rhs.GetZ(), GetW() + rhs.GetW());
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::operator-(const Vector4<TValueType>& rhs) const
	{
		return Vector4<TValueType>(GetX() - rhs.GetX(), GetY() - rhs.GetY(),
			GetZ() - rhs.GetZ(), GetW() - rhs.GetW());
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::operator*(const Vector4<TValueType>& rhs) const
	{
		return Vector4<TValueType>(GetX() * rhs.GetX(), GetY() * rhs.GetY(),
			GetZ() * rhs.GetZ(), GetW() * rhs.GetW());
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::operator/(const Vector4<TValueType>& rhs) const
	{
		return Vector4<TValueType>(GetX() / rhs.GetX(), GetY() / rhs.GetY(),
			GetZ() / rhs.GetZ(), GetW() / rhs.GetW());
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::operator*(TValueType rhs) const
	{
		return Vector4<TValueType>(GetX() * rhs, GetY() * rhs,
			GetZ() * rhs, GetW() * rhs);
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::operator/(TValueType rhs) const
	{
		rhs = static_cast<TValueType>(1) / rhs;

		return Vector4<TValueType>(GetX() * rhs, GetY() * rhs, GetZ() * rhs, GetW() * rhs);
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::operator-(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			throw std::logic_error("Cannot negate unsigned vector");

		else
			return Vector4<TValueType>(-GetX(), -GetY(), -GetZ(), -GetW());
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType>& Vector4<TValueType>::operator+=(const Vector4<TValueType>& rhs)
	{
		X() += rhs.GetX();
		Y() += rhs.GetY();
		Z() += rhs.GetZ();
		W() += rhs.GetW();

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType>& Vector4<TValueType>::operator-=(const Vector4<TValueType>& rhs)
	{
		X() -= rhs.GetX();
		Y() -= rhs.GetY();
		Z() -= rhs.GetZ();
		W() -= rhs.GetW();

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType>& Vector4<TValueType>::operator*=(const Vector4<TValueType>& rhs)
	{
		X() *= rhs.GetX();
		Y() *= rhs.GetY();
		Z() *= rhs.GetZ();
		W() *= rhs.GetW();

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType>& Vector4<TValueType>::operator/=(const Vector4<TValueType>& rhs)
	{
		X() /= rhs.GetX();
		Y() /= rhs.GetY();
		Z() /= rhs.GetZ();
		W() /= rhs.GetW();

		return*this;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType>& Vector4<TValueType>::operator*=(TValueType rhs)
	{
		X() *= rhs;
		Y() *= rhs;
		Z() *= rhs;
		W() *= rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType>& Vector4<TValueType>::operator/=(TValueType rhs)
	{
		rhs = static_cast<TValueType>(1) / rhs;

		X() *= rhs;
		Y() *= rhs;
		Z() *= rhs;
		W() *= rhs;

		return *this;
	}


	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Zero(void)
	{
		return Vector4<TValueType>();
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::One(void)
	{
		return Vector4<TValueType>(static_cast<TValueType>(1), static_cast<TValueType>(1),
								     static_cast<TValueType>(1), static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Up(void)
	{
		return Vector4<TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(1),
									 static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Down(void)
	{
		return Vector4<TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(-1),
									static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Left(void)
	{
		return Vector4<TValueType>(static_cast<TValueType>(-1), static_cast<TValueType>(0),
									 static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Right(void)
	{
		return Vector4<TValueType>(static_cast<TValueType>(1), static_cast<TValueType>(0),
									 static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Back(void)
	{
		return Vector4<TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(0),
									 static_cast<TValueType>(-1), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Vector4<TValueType>::Front(void)
	{
		return Vector4<TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(0),
									static_cast<TValueType>(1), static_cast<TValueType>(0));
	}


	// !Constants


	template <CScalarType TValueType> inline
	TValueType Dot(const Vector4<TValueType>& first, const Vector4<TValueType>& second)
	{
		return first.Dot(second);
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Reflect(const Vector4<TValueType>& target, const Vector4<TValueType>& ontoNormal)
	{
		Vector4<TValueType>		copy = target;

		// Return reflected copy
		copy.ReflectOnto(ontoNormal);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> ReflectUnit(const Vector4<TValueType>& target, const Vector4<TValueType>& ontoNormal)
	{
		Vector4<TValueType>		copy = target;

		// Return reflected copy
		copy.ReflectOntoUnit(ontoNormal);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Project(const Vector4<TValueType>& target, const Vector4<TValueType>& ontoVector)
	{
		Vector4<TValueType>		copy = target;

		// Return projected copy
		copy.ProjectOnto(ontoVector);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Normalize(const Vector4<TValueType>& target)
	{
		// Return normalized copy
		return target.Normalized();
	}


	template <CScalarType TValueType> inline
	TValueType Distance(const Vector4<TValueType>& start, const Vector4<TValueType>& end)
	{
		return start.DistanceFrom(end);
	}


	template <CScalarType TValueType> inline
	TValueType DistanceSquared(const Vector4<TValueType>& start, const Vector4<TValueType>& end)
	{
		return start.DistanceSquaredFrom(end);
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Rotate(const Vector4<TValueType>& target, Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
	{
		Vector4<TValueType>		copy = target;

		// Return rotated copy
		copy.Rotate(angleX, angleY, angleZ);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Rotate(const Vector4<TValueType>& target, Radian<TValueType> angle, const Vector3<TValueType>& axis)
	{
		Vector4<TValueType>		copy = target;

		// Return rotated copy
		copy.Rotate(angle, axis);

		return copy;
	}


	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& os, Vector4<TValueType> const& vector)
	{
		// Pass components to stream
		os << '{' << vector.GetX() << ',' << vector.GetY()
			<< ',' << vector.GetZ() << ',' << vector.GetW() << '}';

		return os;
	}

	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& is, Vector4<TValueType>& vector)
	{
		char	discard;

		// Get input from stream
		is >> discard >> vector.X() >> discard >> vector.Y()
			>> discard >> vector.Z() >> discard >> vector.W() >> discard;

		return is;
	}


}

namespace LibMath = math;
namespace lm = LibMath;


#endif