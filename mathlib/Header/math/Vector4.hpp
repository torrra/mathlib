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
	class Vector<4, TValueType>
	{
	public:

		// Constructors / destructor

	inline			Vector(void) = default;

	inline
	explicit		Vector(TValueType val);

	inline			Vector(TValueType x, TValueType y, TValueType z, TValueType w);

	inline			Vector(const Vector<4, TValueType>& other);

	inline			~Vector(void) = default;

		// Get angle from this vector to another
	inline			Radian<TValueType>
					AngleFrom(const Vector<4, TValueType>& other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
	inline			Radian<TValueType>
					AngleFromUnit(const Vector<4, TValueType>& other)				const;

		// Get distance between 2 points
	inline	TValueType			DistanceFrom(const Vector<4, TValueType>& other)					const;

		// Get distance squared between two points
	inline	TValueType			DistanceSquaredFrom(const Vector<4, TValueType>& other)			const;

		// Get distance between 2 points disregarding the z and w axes
	inline	TValueType			Distance2DFrom(Vector<4, TValueType> const& other)				const;

		// Get distance squared between two points disregarding the z and w axes
	inline	TValueType			Distance2DSquaredFrom(Vector<4, TValueType> const& other)		const;

		// Get distance between two points disregarding the w axis
	inline	TValueType			Distance3DFrom(Vector<4, TValueType> const& other)				const;

		// Get distance squared between two points disregarding the w axis
	inline	TValueType			Distance3DSquaredFrom(Vector<4, TValueType> const& other)		const;


		// Compute dot product of two vectors
	inline	TValueType			Dot(const Vector<4, TValueType>& other)							const;

		// Is this vector's magnitude longer than another ?
	inline	bool			IsLongerThan(const Vector<4, TValueType>& other)					const;

		// Is this vector's magnitude shorter than another ?
	inline	bool			IsShorterThan(const Vector<4, TValueType>& other)				const;

		// Is this vector's magnitude equal to 1 ?
	inline	bool			IsUnitVector(void)									const;

	inline	TValueType			Magnitude(void)										const;
	inline	TValueType			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
	inline	void			Normalize(void);

		// Get copy of this vector as a unit vector
	inline	Vector<4, TValueType>			Normalized(void)									const;

		// Project this vector onto another
	inline	void			ProjectOnto(const Vector<4, TValueType>& other);

		// Reflect this vector onto another
	inline	void			ReflectOnto(const Vector<4, TValueType>& axis);

		// Reflect this vector onto a UNIT vector
	inline	void			ReflectOntoUnit(const Vector<4, TValueType>& axis);

		// Rotate this vector around the all 3 axes (not w)
	inline	void			Rotate(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ);

		// Rotate this vector around an arbitrary 3D axis
	inline	void			Rotate(Radian<TValueType> angle, const Vector3<TValueType>& axis);

		// Multiply this vector's components by another's
	inline	void			Scale(const Vector<4, TValueType>& other);

		// Get components as string
	inline	std::string		String(void)										const;

		// Get components as verbose string
	inline	std::string		StringLong(void)									const;

		// Add another vector's components to this one's
	inline	void			Translate(const Vector<4, TValueType>& other);


		// Accessors

	inline	TValueType&			X(void);
	inline	TValueType&			Y(void);
	inline	TValueType&			Z(void);
	inline	TValueType&			W(void);

	inline	TValueType			GetX(void)											const;
	inline	TValueType			GetY(void)											const;
	inline	TValueType			GetZ(void)											const;
	inline	TValueType			GetW(void)											const;


	inline	Vector<4, TValueType>&		operator=(const Vector<4, TValueType>& rhs);

	inline	TValueType&			operator[](int index);
	inline	TValueType			operator[](int index)								const;


		// Boolean test operators

	inline	bool			operator==(const Vector<4, TValueType>& rhs)						const;
	inline	bool			operator!=(const Vector<4, TValueType>& rhs)						const;


		// Component-wise operations

	inline	Vector<4, TValueType>			operator+(const Vector<4, TValueType>& rhs)						const;
	inline	Vector<4, TValueType>			operator-(const Vector<4, TValueType>& rhs)						const;
	inline	Vector<4, TValueType>			operator*(const Vector<4, TValueType>& rhs)						const;
	inline	Vector<4, TValueType>			operator/(const Vector<4, TValueType>& rhs)						const;


		// Multiply all components by a single scalar
	inline	Vector<4, TValueType>			operator*(TValueType rhs)								const;

		// Divide all components by a single scalar
	inline	Vector<4, TValueType>			operator/(TValueType rhs)								const;

		// Flip sign of both components
	inline	Vector<4, TValueType>			operator-(void)										const;


		// Component-wise operations

	inline	Vector<4, TValueType>&		operator+=(const Vector<4, TValueType>& rhs);
	inline	Vector<4, TValueType>&		operator-=(const Vector<4, TValueType>& rhs);
	inline	Vector<4, TValueType>&		operator*=(const Vector<4, TValueType>& rhs);
	inline	Vector<4, TValueType>&		operator/=(const Vector<4, TValueType>& rhs);

		// Multiply all components by a single scalar
	inline	Vector<4, TValueType>&		operator*=(TValueType rhs);

		// Divide all components by a single scalar
	inline	Vector<4, TValueType>&		operator/=(TValueType rhs);


		// Constants

	inline	static Vector<4, TValueType>	Zero(void);
	inline	static Vector<4, TValueType>	One(void);
	inline	static Vector<4, TValueType>	Up(void);
	inline	static Vector<4, TValueType>	Down(void);
	inline	static Vector<4, TValueType>	Left(void);
	inline	static Vector<4, TValueType>	Right(void);
	inline	static Vector<4, TValueType>  Back(void);
	inline	static Vector<4, TValueType>  Front(void);


	private:

		TValueType				m_x = static_cast<TValueType>(0);
		TValueType				m_y = static_cast<TValueType>(0);
		TValueType				m_z = static_cast<TValueType>(0);
		TValueType				m_w = static_cast<TValueType>(0);
	};

	// Non-member functions (similar to member functions but provided for readability)
	template <CScalarType TValueType> inline
	TValueType				Dot(const Vector<4, TValueType>& first, const Vector<4, TValueType>& second);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Reflect(const Vector<4, TValueType>& target, const Vector<4, TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				ReflectUnit(const Vector<4, TValueType>& target, const Vector<4, TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Project(const Vector<4, TValueType>& target, const Vector<4, TValueType>& ontoVector);


	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Normalize(const Vector<4, TValueType>& target);


	template <CScalarType TValueType> inline
	TValueType				Distance(const Vector<4, TValueType>& start, const Vector<4, TValueType>& end);

	template <CScalarType TValueType> inline
	TValueType				DistanceSquared(const Vector<4, TValueType>& start, const Vector<4, TValueType>& end);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Rotate
	(
		const Vector<4, TValueType>& target, Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ
	);


	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Rotate
	(
		const Vector<4, TValueType>& target, Radian<TValueType> angle, const Vector3<TValueType>& axis
	);


	// Send a vector's components to an output stream
	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& os, Vector<4, TValueType> const& vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& is, Vector<4, TValueType>& vector);







/// ---- Implementation ----


	template <CScalarType TValueType> inline
	Vector<4, TValueType>::Vector(TValueType val)
		: m_x(val), m_y(val), m_z(val), m_w(val)
	{}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>::Vector(TValueType x, TValueType y, TValueType z, TValueType w)
		: m_x(x), m_y(y), m_z(z), m_w(w)
	{}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>::Vector(const Vector<4, TValueType>& other)
		: m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_w(other.m_w)
	{}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<4, TValueType>::AngleFrom(const Vector<4, TValueType>& other) const
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
	Radian<TValueType> Vector<4, TValueType>::AngleFromUnit(const Vector<4, TValueType>& other) const
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
	TValueType Vector<4, TValueType>::DistanceFrom(const Vector<4, TValueType>& other) const
	{
		return SquareRoot(DistanceSquaredFrom(other));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::DistanceSquaredFrom(const Vector<4, TValueType>& other) const
	{
		// Find distance vector and get magnitude
		return (other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance2DFrom(Vector<4, TValueType> const& other) const
	{
		// Ignore z and w axes
		Vector2<TValueType>		self2D = { m_x, m_y };
		Vector2<TValueType>		other2D = { other.m_x, other.m_y };


		return self2D.DistanceFrom(other2D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance2DSquaredFrom(Vector<4, TValueType> const& other) const
	{
		// Ignore z and w axes
		Vector2<TValueType>		self2D = { m_x, m_y };
		Vector2<TValueType>		other2D = { other.m_x, other.m_y };


		return self2D.DistanceSquaredFrom(other2D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance3DFrom(Vector<4, TValueType> const& other) const
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { m_x, m_y, m_z };
		Vector3<TValueType>		other3D = { other.m_x, other.m_y, other.m_z };


		return self3D.DistanceFrom(other3D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance3DSquaredFrom(Vector<4, TValueType> const& other) const
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { m_x, m_y, m_z };
		Vector3<TValueType>		other3D = { other.m_x, other.m_y, other.m_z };


		return self3D.DistanceSquaredFrom(other3D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Dot(const Vector<4, TValueType>& other) const
	{
		// Multiply components
		return (m_x * other.m_x) + (m_y * other.m_y) +
			(m_z * other.m_z) + (m_w * other.m_w);
	}


	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::IsLongerThan(const Vector<4, TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::IsShorterThan(const Vector<4, TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::IsUnitVector(void) const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Magnitude(void) const
	{
		return SquareRoot(MagnitudeSquared());
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::MagnitudeSquared(void) const
	{
		// Square components
		return Dot(*this);
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Normalize(void)
	{
		// Only divide once
		TValueType		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, static_cast<TValueType>(0), std::numeric_limits<TValueType>::epsilon()))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		else
			invMagnitude = static_cast<TValueType>(1) / invMagnitude;


		m_x *= invMagnitude;
		m_y *= invMagnitude;
		m_z *= invMagnitude;
		m_w *= invMagnitude;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Normalized(void) const
	{
		Vector<4, TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::ProjectOnto(const Vector<4, TValueType>& other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = other.MagnitudeSquared();
		TValueType		projFactor = Dot(other) / squareMagnitude;

		m_x = other.m_x * projFactor;
		m_y = other.m_y * projFactor;
		m_z = other.m_z * projFactor;
		m_w = other.m_w * projFactor;
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::ReflectOnto(const Vector<4, TValueType>& axis)
	{
		// Only reflect onto unit vector
		Vector<4, TValueType>		normal = math::Normalize(axis);

		*this -= normal * (Dot(normal) * static_cast<TValueType>(2));
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::ReflectOntoUnit(const Vector<4, TValueType>& axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= axis * (Dot(axis) * static_cast<TValueType>(2));
	}



	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Rotate(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
	{
		if constexpr (std::is_unsigned_v<TValueType> || std::is_integral_v<TValueType>)
			throw std::logic_error("Cannot rotate unsigned or integral vector");


		else
		{
			Vector<4, TValueType>		copy = *this;

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
	void Vector<4, TValueType>::Rotate(Radian<TValueType> angle, const Vector3<TValueType>& axis)
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { m_x, m_y, m_z };

		// Rotate without w
		self3D.Rotate(angle, axis);

		m_x = self3D.GetX();
		m_y = self3D.GetY();
		m_z = self3D.GetZ();
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Scale(const Vector<4, TValueType>& other)
	{
		*this *= other;
	}



	template <CScalarType TValueType> inline
	std::string Vector<4, TValueType>::String(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << ',' << m_z << ',' << m_w << '}';

		return stream.str();
	}


	template <CScalarType TValueType> inline
	std::string Vector<4, TValueType>::StringLong(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << "Vector4{ x:" << m_x << ", y:" << m_y << ", z:"
			<< m_z << ", w:" << m_w << " }";

		return stream.str();
	}



	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Translate(const Vector<4, TValueType>& other)
	{
		*this += other;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::X(void)
	{
		return m_x;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::Y(void)
	{
		return m_y;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::Z(void)
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::W(void)
	{
		return m_w;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetX(void) const
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetY(void) const
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetZ(void) const
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetW(void) const
	{
		return m_w;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator=(const Vector<4, TValueType>& rhs)
	{
		// Copy assign
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_z = rhs.m_z;
		m_w = rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::operator[](int index)
	{
		switch (index)
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


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::operator[](int index) const
	{
		switch (index)
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



	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::operator==(const Vector<4, TValueType>& rhs) const
	{
		// Compare all components
		return
			(
				AlmostEqual(m_x, rhs.m_x) &&
				AlmostEqual(m_y, rhs.m_y) &&
				AlmostEqual(m_z, rhs.m_z) &&
				AlmostEqual(m_w, rhs.m_w)

				);
	}



	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::operator!=(const Vector<4, TValueType>& rhs) const
	{
		return !(*this == rhs);
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator+(const Vector<4, TValueType>& rhs) const
	{
		return Vector<4, TValueType>(m_x + rhs.m_x, m_y + rhs.m_y,
			m_z + rhs.m_z, m_w + rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator-(const Vector<4, TValueType>& rhs) const
	{
		return Vector<4, TValueType>(m_x - rhs.m_x, m_y - rhs.m_y,
			m_z - rhs.m_z, m_w - rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator*(const Vector<4, TValueType>& rhs) const
	{
		return Vector<4, TValueType>(m_x * rhs.m_x, m_y * rhs.m_y,
			m_z * rhs.m_z, m_w * rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator/(const Vector<4, TValueType>& rhs) const
	{
		return Vector<4, TValueType>(m_x / rhs.m_x, m_y / rhs.m_y,
			m_z / rhs.m_z, m_w / rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator*(TValueType rhs) const
	{
		return Vector<4, TValueType>(m_x * rhs, m_y * rhs,
			m_z * rhs, m_w * rhs);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator/(TValueType rhs) const
	{
		rhs = static_cast<TValueType>(1) / rhs;

		return Vector<4, TValueType>(m_x * rhs, m_y * rhs, m_z * rhs, m_w * rhs);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator-(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			throw std::logic_error("Cannot negate unsigned vector");

		else
			return Vector<4, TValueType>(-m_x, -m_y, -m_z, -m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator+=(const Vector<4, TValueType>& rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;
		m_w += rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator-=(const Vector<4, TValueType>& rhs)
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;
		m_w -= rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator*=(const Vector<4, TValueType>& rhs)
	{
		m_x *= rhs.m_x;
		m_y *= rhs.m_y;
		m_z *= rhs.m_z;
		m_w *= rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator/=(const Vector<4, TValueType>& rhs)
	{
		m_x /= rhs.m_x;
		m_y /= rhs.m_y;
		m_z /= rhs.m_z;
		m_w /= rhs.m_w;

		return*this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator*=(TValueType rhs)
	{
		m_x *= rhs;
		m_y *= rhs;
		m_z *= rhs;
		m_w *= rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator/=(TValueType rhs)
	{
		rhs = static_cast<TValueType>(1) / rhs;

		m_x *= rhs;
		m_y *= rhs;
		m_z *= rhs;
		m_w *= rhs;

		return *this;
	}


	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Zero(void)
	{
		return Vector<4, TValueType>();
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::One(void)
	{
		return Vector<4, TValueType>(static_cast<TValueType>(1), static_cast<TValueType>(1),
								     static_cast<TValueType>(1), static_cast<TValueType>(1));
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Up(void)
	{
		return Vector<4, TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(1),
									 static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Down(void)
	{
		return Vector<4, TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(-1),
									static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Left(void)
	{
		return Vector<4, TValueType>(static_cast<TValueType>(-1), static_cast<TValueType>(0),
									 static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Right(void)
	{
		return Vector<4, TValueType>(static_cast<TValueType>(1), static_cast<TValueType>(0),
									 static_cast<TValueType>(0), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Back(void)
	{
		return Vector<4, TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(0),
									 static_cast<TValueType>(-1), static_cast<TValueType>(0));
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Front(void)
	{
		return Vector<4, TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(0),
									static_cast<TValueType>(1), static_cast<TValueType>(0));
	}


	// !Constants


	template <CScalarType TValueType> inline
	TValueType Dot(const Vector<4, TValueType>& first, const Vector<4, TValueType>& second)
	{
		return first.Dot(second);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Reflect(const Vector<4, TValueType>& target, const Vector<4, TValueType>& ontoNormal)
	{
		Vector<4, TValueType>		copy = target;

		// Return reflected copy
		copy.ReflectOnto(ontoNormal);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> ReflectUnit(const Vector<4, TValueType>& target, const Vector<4, TValueType>& ontoNormal)
	{
		Vector<4, TValueType>		copy = target;

		// Return reflected copy
		copy.ReflectOntoUnit(ontoNormal);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Project(const Vector<4, TValueType>& target, const Vector<4, TValueType>& ontoVector)
	{
		Vector<4, TValueType>		copy = target;

		// Return projected copy
		copy.ProjectOnto(ontoVector);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Normalize(const Vector<4, TValueType>& target)
	{
		// Return normalized copy
		return target.Normalized();
	}


	template <CScalarType TValueType> inline
	TValueType Distance(const Vector<4, TValueType>& start, const Vector<4, TValueType>& end)
	{
		return start.DistanceFrom(end);
	}


	template <CScalarType TValueType> inline
	TValueType DistanceSquared(const Vector<4, TValueType>& start, const Vector<4, TValueType>& end)
	{
		return start.DistanceSquaredFrom(end);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Rotate(const Vector<4, TValueType>& target, Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
	{
		Vector<4, TValueType>		copy = target;

		// Return rotated copy
		copy.Rotate(angleX, angleY, angleZ);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Rotate(const Vector<4, TValueType>& target, Radian<TValueType> angle, const Vector3<TValueType>& axis)
	{
		Vector<4, TValueType>		copy = target;

		// Return rotated copy
		copy.Rotate(angle, axis);

		return copy;
	}


	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& os, Vector<4, TValueType> const& vector)
	{
		// Pass components to stream
		os << '{' << vector.GetX() << ',' << vector.GetY()
			<< ',' << vector.GetZ() << ',' << vector.GetW() << '}';

		return os;
	}

	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& is, Vector<4, TValueType>& vector)
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