#pragma once

#include <string>

#include "libmath/Angle.h"

namespace mth
{
	class Vector2
	{
	public:
		// Constructors / destructor

						Vector2(void) = default;

		explicit		Vector2(float _val);
						Vector2(float _x, float _y);
						Vector2(const Vector2& _other );

						~Vector2(void) = default;

		// Get angle from this vector to another
		Radian			AngleFrom(const Vector2& _other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
		Radian			AngleFromUnit(const Vector2& _other)				const;

		// Compute cross product with another
		// this x other
		float			Cross(const Vector2& _other)						const;

		// Get distance between 2 points
		float			DistanceFrom(const Vector2& _other)					const;

		// Get distance squared between two points
		float			DistanceSquaredFrom(const Vector2& _other)			const;

		// Compute dot product of two vectors
		float			Dot(const Vector2& _other)							const;

		// Is this vector's magnitude longer than another ?
		bool			IsLongerThan(const Vector2& _other)					const;

		// Is this vector's magnitude shorter than another ?
		bool			IsShorterThan(const Vector2& _other)				const;

		// Is this vector's magnitude equal to 1 ?
		bool			IsUnitVector(void)									const;

		float			Magnitude(void)										const;
		float			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
		void			Normalize(void);

		// Get copy of this vector as a unit vector
		Vector2			Normalized(void)									const;

		// Get vector normal to this one
		Vector2			Normal(void)										const;

		// Project this vector onto another
		void			ProjectOnto(const Vector2& _other);

		// Reflect this vector onto another
		void			ReflectOnto(const Vector2& _axis);

		// Reflect this vector onto a UNIT vector
		void			ReflectOntoUnit(const Vector2& _axis);

		// Rotate this point around the z axis
		void			Rotate(Radian _angle);

		// Multiply this vector's components by another's
		void			Scale(const Vector2& _other);

		// Get components as string
		std::string		String(void)										const;

		// Get components as verbose string
		std::string		StringLong(void)									const;

		// Add another vector's components to this one's
		void			Translate(const Vector2& _other);

		// Accessors

		float&			X(void);
		float&			Y(void);

		float			GetX(void)											const;
		float			GetY(void)											const;


		Vector2&		operator=(const Vector2& _rhs);

		float&			operator[](int _index);
		float			operator[](int _index)								const;

		// Boolean test operators

		bool			operator==(const Vector2& _rhs)						const;
		bool			operator!=(const Vector2& _rhs)						const;

		// Component-wise operations

		Vector2			operator+(const Vector2& _rhs)						const;
		Vector2			operator-(const Vector2& _rhs)						const;
		Vector2			operator*(const Vector2& _rhs)						const;
		Vector2			operator/(const Vector2& _rhs)						const;

		// Multiply all components by a single scalar
		Vector2			operator*(float _rhs)								const;

		// Divide all components by a single scalar
		Vector2			operator/(float _rhs)								const;

		// Flip sign of both componenents
		Vector2			operator-(void)										const;


		// Component-wise operations

		Vector2&		operator+=(const Vector2& _rhs);
		Vector2&		operator-=(const Vector2& _rhs);
		Vector2&		operator*=(const Vector2& _rhs);
		Vector2&		operator/=(const Vector2& _rhs);

		// Multiply all components by a single scalar
		Vector2&		operator*=(float _rhs);

		// Divide all components by a single scalar
		Vector2&		operator/=(float _rhs);


		// Constants

		static Vector2	Zero(void);
		static Vector2	One(void);
		static Vector2	Up(void);
		static Vector2	Down(void);
		static Vector2	Left(void);
		static Vector2	Right(void);


	private:

		float				m_x = 0.f;
		float				m_y = 0.f;
	};


	// Non-member functions (similar to member functions but provided for readability)

	float				Dot(const Vector2& _first, const Vector2& _second);
	float				Cross(const Vector2& _first, const Vector2& _second);

	Vector2				Reflect(const Vector2& _target, const Vector2& _ontoNormal);
	Vector2				ReflectUnit(const Vector2& _target, const Vector2& _ontoNormal);
	Vector2				Project(const Vector2& _target, const Vector2& _ontoVector);

	Vector2				Normalize(const Vector2& _target);

	float				Distance(const Vector2& _start, const Vector2& _end);
	float				DistanceSquared(const Vector2& _start, const Vector2& _end);

	Vector2				Rotate(const Vector2& _target, Radian _angle);

	// Send a vector's components to an output stream
	std::ostream&		operator<<(std::ostream& _os, Vector2 const& _vector);

	// Get components from an input stream
	std::istream&		operator>>(std::istream& _is, Vector2& _vector);
}

namespace LibMath = mth;
namespace lm = LibMath;