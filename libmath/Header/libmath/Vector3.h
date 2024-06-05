#pragma once

#include <string>

#include "libmath/Angle.h"

namespace mth
{
	class Vector3
	{
	public:

		// Constructors / destructor
						Vector3(void) = default;

		explicit		Vector3(float _val);
						Vector3(float _x, float _y, float _z);
						Vector3(const Vector3& _other);

						~Vector3(void) = default;

		// Get angle from this vector to another
		Radian			AngleFrom(const Vector3& _other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
		Radian			AngleFromUnit(const Vector3& _other)				const;

		// Compute cross product with another
		// this x other
		Vector3			Cross(const Vector3& _other)						const;

		// Get distance between 2 points
		float			DistanceFrom(const Vector3& _other)					const;

		// Get distance squared between two points
		float			DistanceSquaredFrom(const Vector3& _other)			const;

		// Get distance between 2 points disregarding the z axis
		float			Distance2DFrom(Vector3 const&)						const;

		// Get distance squared between two points disregarding the z axis
		float			Distance2DSquaredFrom(Vector3 const&)				const;

		// Compute dot product of two vectors
		float			Dot(const Vector3& _other)							const;

		// Is this vector's magnitude longer than another ?
		bool			IsLongerThan(const Vector3& _other)					const;

		// Is this vector's magnitude shorter than another ?
		bool			IsShorterThan(const Vector3& _other)				const;

		// Is this vector's magnitude equal to 1 ?
		bool			IsUnitVector(void)									const;

		float			Magnitude(void)										const;
		float			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
		void			Normalize(void);

		// Get copy of this vector as a unit vector
		Vector3			Normalized(void)									const;

		// Project this vector onto another
		void			ProjectOnto(const Vector3& _other);

		// Reflect this vector onto another
		void			ReflectOnto(const Vector3& _axis);

		// Reflect this vector onto a UNIT vector
		void			ReflectOntoUnit(const Vector3& _axis);

		// Rotate this vector around the all 3 axes
		void			Rotate(Radian _angleX, Radian _angleY, Radian _angleZ);

		// Rotate this vector around an arbitrary axis
		void			Rotate(Radian _angle, const Vector3& _axis);

		// Multiply this vector's components by another's
		void			Scale(const Vector3& _other);

		// Get components as string
		std::string		String(void)										const;

		// Get components as verbose string
		std::string		StringLong(void)									const;

		// Add another vector's components to this one's
		void			Translate(const Vector3& _other);

		// Accessors

		float&			X(void);
		float&			Y(void);
		float&			Z(void);

		float			GetX(void)											const;
		float			GetY(void)											const;
		float			GetZ(void)											const;


		Vector3&		operator=(const Vector3& _rhs);

		float&			operator[](int _index);
		float			operator[](int _index)								const;

		// Boolean test operators

		bool			operator==(const Vector3& _rhs)						const;
		bool			operator!=(const Vector3& _rhs)						const;

		// Component-wise operations

		Vector3			operator+(const Vector3& _rhs)						const;
		Vector3			operator-(const Vector3& _rhs)						const;
		Vector3			operator*(const Vector3& _rhs)						const;
		Vector3			operator/(const Vector3& _rhs)						const;

		// Multiply all components by a single scalar
		Vector3			operator*(float _rhs)								const;

		// Divide all components by a single scalar
		Vector3			operator/(float _rhs)								const;

		// Flip sign of both components
		Vector3			operator-(void)										const;


		// Component-wise operations

		Vector3&		operator+=(const Vector3& _rhs);
		Vector3&		operator-=(const Vector3& _rhs);
		Vector3&		operator*=(const Vector3& _rhs);
		Vector3&		operator/=(const Vector3& _rhs);

		// Multiply all components by a single scalar
		Vector3&		operator*=(float _rhs);

		// Divide all components by a single scalar
		Vector3&		operator/=(float _rhs);


		// Constants

		static Vector3	Zero(void);
		static Vector3	One(void);
		static Vector3	Up(void);
		static Vector3	Down(void);
		static Vector3	Left(void);
		static Vector3	Right(void);
		static Vector3  Back(void);
		static Vector3  Front(void);


	private:

		float				m_x = 0.f;
		float				m_y = 0.f;
		float				m_z = 0.f;
	};

	// Non-member functions (similar to member functions but provided for readability)

	float				Dot(const Vector3& _first, const Vector3& _second);

	Vector3				Cross(const Vector3& _first, const Vector3& _second);

	Vector3				Reflect(const Vector3& _target, const Vector3& _ontoNormal);
	Vector3				ReflectUnit(const Vector3& _target, const Vector3& _ontoNormal);
	Vector3				Project(const Vector3& _target, const Vector3& _ontoVector);

	Vector3				Normalize(const Vector3& _target);

	float				Distance(const Vector3& _start, const Vector3& _end);
	float				DistanceSquared(const Vector3& _start, const Vector3& _end);

	Vector3				Rotate
	(
		const Vector3& _target, Radian _angleX, Radian _angleY, Radian _angleZ
	);

	Vector3				Rotate
	(
		const Vector3& _target, Radian _angle, const Vector3& _axis
	);

	// Send a vector's components to an output stream
	std::ostream&		operator<<(std::ostream& _os, Vector3 const& _vector);

	// Get components from an input stream
	std::istream&		operator>>(std::istream& _is, Vector3& _vector);
}

namespace LibMath = mth;
namespace lm = LibMath;