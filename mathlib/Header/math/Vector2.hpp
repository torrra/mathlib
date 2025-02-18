#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <string>
#include <sstream>

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"


#include "Angle.hpp"
#include "Trigonometry.hpp"


namespace math
{

	template <CScalarType TValueType>
	class Vector<2, TValueType>
	{
	public:
		// Constructors / destructor

		inline				Vector(void) = default;

		inline
		explicit			Vector(TValueType val);

		inline				Vector(TValueType x, TValueType y);
		inline				Vector(const Vector& other );

		inline				~Vector(void) = default;

		// Get angle from this vector to another
		inline
		Radian<TValueType>			AngleFrom(const Vector& other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
		inline
		Radian<TValueType>			AngleFromUnit(const Vector& other)				const;

		// Compute cross product with another
		// this x other
		inline TValueType			Cross(const Vector& other)						const;

		// Get distance between 2 points
		inline TValueType			DistanceFrom(const Vector& other)					const;

		// Get distance squared between two points
		inline TValueType			DistanceSquaredFrom(const Vector& other)			const;

		// Compute dot product of two vectors
		inline TValueType			Dot(const Vector& other)							const;

		// Is this vector's magnitude longer than another ?
		inline bool			IsLongerThan(const Vector& other)					const;

		// Is this vector's magnitude shorter than another ?
		inline bool			IsShorterThan(const Vector& other)				const;

		// Is this vector's magnitude equal to 1 ?
		inline bool			IsUnitVector(void)									const;

		inline TValueType			Magnitude(void)										const;
		inline TValueType			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
		inline void			Normalize(void);

		// Get copy of this vector as a unit vector
		inline Vector			Normalized(void)									const;

		// Get vector normal to this one
		inline Vector			Normal(void)										const;

		// Project this vector onto another
		inline void			ProjectOnto(const Vector& other);

		// Reflect this vector onto another
		inline void			ReflectOnto(const Vector& axis);

		// Reflect this vector onto a UNIT vector
		inline void			ReflectOntoUnit(const Vector& axis);

		// Rotate this point around the z axis
		inline void			Rotate(Radian<TValueType> angle);

		// Multiply this vector's components by another's
		inline void			Scale(const Vector& other);

		// Get components as string
		inline std::string		String(void)										const;

		// Get components as verbose string
		inline std::string		StringLong(void)									const;

		// Add another vector's components to this one's
		inline void			Translate(const Vector& other);

		// Accessors

		inline TValueType&			X(void);
		inline TValueType&			Y(void);

		inline TValueType			GetX(void)											const;
		inline TValueType			GetY(void)											const;


		inline Vector&		operator=(const Vector& rhs);

		inline TValueType&			operator[](int index);
		inline TValueType			operator[](int index)								const;

		// Boolean test operators

		inline bool			operator==(const Vector& rhs)						const;
		inline bool			operator!=(const Vector& rhs)						const;

		// Component-wise operations

		inline Vector			operator+(const Vector& rhs)						const;
		inline Vector			operator-(const Vector& rhs)						const;
		inline Vector			operator*(const Vector& rhs)						const;
		inline Vector			operator/(const Vector& rhs)						const;

		// Multiply all components by a single scalar
		inline Vector			operator*(TValueType rhs)								const;

		// Divide all components by a single scalar
		inline Vector			operator/(TValueType rhs)								const;

		// Flip sign of both componenents
		inline Vector			operator-(void)										const;


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


	private:

		TValueType				m_x;
		TValueType				m_y;
	};


	// Non-member functions (similar to member functions but provided for readability)

	template <CScalarType TValueType> inline
	TValueType				Dot(const Vector<2, TValueType>& first, const Vector<2, TValueType>& second);

	template <CScalarType TValueType> inline
	TValueType				Cross(const Vector<2, TValueType>& first, const Vector<2, TValueType>& second);


	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Reflect(const Vector<2, TValueType>& target, const Vector<2, TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector<2, TValueType>				ReflectUnit(const Vector<2, TValueType>& target, const Vector<2, TValueType>& ontoNormal);

	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Project(const Vector<2, TValueType>& target, const Vector<2, TValueType>& ontoVector);


	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Normalize(const Vector<2, TValueType>& target);


	template <CScalarType TValueType> inline
	TValueType				Distance(const Vector<2, TValueType>& start, const Vector<2, TValueType>& end);


	template <CScalarType TValueType> inline
	TValueType				DistanceSquared(const Vector<2, TValueType>& start, const Vector<2, TValueType>& end);


	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Rotate(const Vector<2, TValueType>& target, Radian<TValueType> angle);


	// Send a Vector<2, TValueType>'s components to an output stream
	template <CScalarType TValueType> inline
	std::ostream&		operator<<(std::ostream& os, Vector<2, TValueType> const& vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream&		operator>>(std::istream& is, Vector<2, TValueType>& vector);





// ---- Implementation ----


	template <CScalarType TValueType> inline
	Vector<2, TValueType>::Vector(TValueType val)
		: m_x(val), m_y(val) {}

	template <CScalarType TValueType> inline
	Vector<2, TValueType>::Vector(TValueType x, TValueType y)
		: m_x(x), m_y(y) {}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>::Vector(const Vector<2, TValueType>& other)
		: m_x(other.m_x), m_y(other.m_y) {}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<2, TValueType>::AngleFrom(const Vector<2, TValueType>& other) const
	{
		TValueType		magnitudes = MagnitudeSquared() * other.MagnitudeSquared();

		// Only run square root once
		magnitudes = SquareRoot(magnitudes);

		// Transform dot product equation to get cos angle,
		// then run acos
		return Acos(Dot(other) / magnitudes);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<2, TValueType>::AngleFromUnit(const Vector<2, TValueType>& other) const
	{
		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		return Acos(Clamp(Dot(other), MIN_COS, MAX_COS));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::Cross(const Vector<2, TValueType>& other) const
	{
		// Only compute result for result's  z component as
		// both x and y will be zero for vec2 cross product
		return (m_x * other.m_y) - (m_y * other.m_x);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::DistanceFrom(const Vector<2, TValueType>& other) const
	{
		return SquareRoot(DistanceSquaredFrom(other));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::DistanceSquaredFrom(const Vector<2, TValueType>& other) const
	{
		// Find distance vector and get magnitude
		return (other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::Dot(const Vector<2, TValueType>& other) const
	{
		// Multiply components
		return (m_x * other.m_x) + (m_y * other.m_y);
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::IsLongerThan(const Vector<2, TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::IsShorterThan(const Vector<2, TValueType>& other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::IsUnitVector() const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}

	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::MagnitudeSquared() const
	{
		// Square components
		return Dot(*this);
	}


	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Normalize()
	{
		TValueType		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, 0.f, std::numeric_limits<float>::epsilon()))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		// Only divide once
		else
			invMagnitude = 1.f / invMagnitude;

		m_x *= invMagnitude;
		m_y *= invMagnitude;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Normalized(void) const
	{
		Vector<2, TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Normal(void) const
	{
		// Swap x and y and flip one sign (y here)
		return Vector<2, TValueType>(-m_y, m_x);
	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::ProjectOnto(const Vector<2, TValueType>& other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = other.MagnitudeSquared();
		TValueType		projFactor = Dot(other) / squareMagnitude;

		m_x = other.m_x * projFactor;
		m_y = other.m_y * projFactor;

	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::ReflectOnto(const Vector<2, TValueType>& axis)
	{
		// Only reflect onto unit vector
		Vector<2, TValueType>		normal = math::Normalize(axis);

		// Apply reflection formula
		*this -= normal * (Dot(normal) * 2.f);
	}


	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::ReflectOntoUnit(const Vector<2, TValueType>& axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= axis * (Dot(axis) * 2.f);
	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Rotate(Radian<TValueType> angle)
	{
		TValueType		cosAngle = Cos(angle),
					sinAngle = Sin(angle);

		// Copy x as base x value is needed for
		// both x and y results
		TValueType		xCopy = m_x;

		// Manually multiply by 2x2 rotation matrix
		m_x = cosAngle * xCopy - m_y * sinAngle;
		m_y = sinAngle * xCopy + m_y * cosAngle;
	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Scale(const Vector<2, TValueType>& other)
	{
		*this *= other;
	}


	template <CScalarType TValueType> inline
	std::string Vector<2, TValueType>::String() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << '}';

		return stream.str();
	}


	template <CScalarType TValueType> inline
	std::string Vector<2, TValueType>::StringLong() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream with some extra
		stream << "Vector2{ x:" << m_x << ", y:" << m_y << " }";

		return stream.str();
	}


	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Translate(const Vector<2, TValueType>& other)
	{
		*this += other;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<2, TValueType>::X()
	{
		return m_x;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<2, TValueType>::Y()
	{
		return m_y;
	}



	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::GetX() const
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::GetY() const
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator=(const Vector<2, TValueType>& rhs)
	{
		// Copy assign
		m_x = rhs.m_x;
		m_y = rhs.m_y;

		return *this;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<2, TValueType>::operator[](int index)
	{
		switch (index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		default:
			throw std::logic_error("Index out of range");
		}
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		default:
			throw std::logic_error("Index out of range");
		}
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::operator==(const Vector<2, TValueType>& rhs) const
	{
		// Compare both components
		return
		(
			AlmostEqual(m_x, rhs.m_x) &&
			AlmostEqual(m_y, rhs.m_y)
		);
	}



	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::operator!=(const Vector<2, TValueType>& rhs) const
	{
		return !(*this == rhs);
	}


	template <CScalarType TValueType> inline
	TValueType Dot(const Vector<2, TValueType>& first, const Vector<2, TValueType>& second)
	{
		return first.Dot(second);
	}


	template <CScalarType TValueType> inline
	TValueType Cross(const Vector<2, TValueType>& first, const Vector<2, TValueType>& second)
	{
		return first.Cross(second);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Reflect(const Vector<2, TValueType>& target, const Vector<2, TValueType>& ontoNormal)
	{
		Vector<2, TValueType>		result = target;

		// Return reflected copy
		result.ReflectOnto(ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> ReflectUnit(const Vector<2, TValueType>& target, const Vector<2, TValueType>& ontoNormal)
	{
		Vector<2, TValueType>		result = target;

		// Return reflected copy
		result.ReflectOntoUnit(ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Project(const Vector<2, TValueType>& target, const Vector<2, TValueType>& ontoVector)
	{
		Vector<2, TValueType>		result = target;

		// Return projected copy
		result.ProjectOnto(ontoVector);

		return result;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Normalize(const Vector<2, TValueType>& target)
	{
		Vector<2, TValueType>		result = target;

		// Return normalized copy
		result.Normalize();

		return result;
	}


	template <CScalarType TValueType> inline
	TValueType Distance(const Vector<2, TValueType>& start, const Vector<2, TValueType>& end)
	{
		return start.DistanceFrom(end);
	}


	template <CScalarType TValueType> inline
	TValueType DistanceSquared(const Vector<2, TValueType>& start, const Vector<2, TValueType>& end)
	{
		return start.DistanceSquaredFrom(end);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Rotate(const Vector<2, TValueType>& target, Radian<TValueType> angle)
	{
		Vector<2, TValueType>		result = target;

		// Return rotated copy
		result.Rotate(angle);

		return result;
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator+(const Vector<2, TValueType>& rhs) const
	{
		return Vector<2, TValueType>(m_x + rhs.m_x, m_y + rhs.m_y);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator-(const Vector<2, TValueType>& rhs) const
	{
		return Vector<2, TValueType>(m_x - rhs.m_x, m_y - rhs.m_y);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator*(const Vector<2, TValueType>& rhs) const
	{
		return Vector<2, TValueType>(m_x * rhs.m_x, m_y * rhs.m_y);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator/(const Vector<2, TValueType>& rhs) const
	{
		return Vector<2, TValueType>(m_x / rhs.m_x, m_y / rhs.m_y);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator*(TValueType rhs) const
	{
		return Vector<2, TValueType>(m_x * rhs, m_y * rhs);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator/(TValueType rhs) const
	{
		rhs = 1.f / rhs;

		return Vector<2, TValueType>(m_x * rhs, m_y * rhs);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator-(void) const
	{
		return Vector<2, TValueType>(-m_x, -m_y);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator+=(const Vector<2, TValueType>& rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator-=(const Vector<2, TValueType>& rhs)
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;

		return *this;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator*=(const Vector<2, TValueType>& rhs)
	{
		m_x *= rhs.m_x;
		m_y *= rhs.m_y;

		return *this;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator/=(const Vector<2, TValueType>& rhs)
	{
		m_x /= rhs.m_x;
		m_y /= rhs.m_y;

		return* this;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator*=(TValueType rhs)
	{
		m_x *= rhs;
		m_y *= rhs;

		return *this;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator/=(TValueType rhs)
	{
		rhs = 1.f / rhs;

		m_x *= rhs;
		m_y *= rhs;

		return *this;
	}

	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Zero(void)
	{
		return Vector<2, TValueType>();
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::One(void)
	{
		return Vector<2, TValueType>(1.f, 1.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Up(void)
	{
		return Vector<2, TValueType>(0.f, 1.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Down(void)
	{
		return Vector<2, TValueType>(0.f, -1.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Left(void)
	{
		return Vector<2, TValueType>(-1.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Right(void)
	{
		return Vector<2, TValueType>(1.f, 0.f);
	}

	// !Constants


	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& os, Vector<2, TValueType> const& vector)
	{
		// Pass components to stream
		os << '{' << vector.GetX() << ',' << vector.GetY() << '}';

		return os;
	}


	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& is, Vector<2, TValueType>& vector)
	{
		char	discard;

		// Get input from stream
		is >> discard >> vector.X() >> discard >> vector.Y() >> discard;

		return is;
	}

}

namespace LibMath = math;
namespace lm = LibMath;

#endif