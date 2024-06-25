#pragma once

#include <string>

#include "libmath/Angle.h"
#include "libmath/Vector3.h"

namespace ion::math
{
	class Vector4
	{
	public:

		// Constructors / destructor

						Vector4(void) = default;

		explicit		Vector4(float _val);
						Vector4(float _x, float _y, float _z, float _w);
						Vector4(const Vector4& _other);

						~Vector4(void) = default;

		// Get angle from this vector to another
		Radian			AngleFrom(const Vector4& _other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
		Radian			AngleFromUnit(const Vector4& _other)				const;

		// Get distance between 2 points
		float			DistanceFrom(const Vector4& _other)					const;

		// Get distance squared between two points
		float			DistanceSquaredFrom(const Vector4& _other)			const;

		// Get distance between 2 points disregarding the z and w axes
		float			Distance2DFrom(Vector4 const& _other)				const;

		// Get distance squared between two points disregarding the z and w axes
		float			Distance2DSquaredFrom(Vector4 const& _other)		const;

		// Get distance between two points disregarding the w axis
		float			Distance3DFrom(Vector4 const& _other)				const;

		// Get distance squared between two points disregarding the w axis
		float			Distance3DSquaredFrom(Vector4 const& _other)		const;


		// Compute dot product of two vectors
		float			Dot(const Vector4& _other)							const;

		// Is this vector's magnitude longer than another ?
		bool			IsLongerThan(const Vector4& _other)					const;

		// Is this vector's magnitude shorter than another ?
		bool			IsShorterThan(const Vector4& _other)				const;

		// Is this vector's magnitude equal to 1 ?
		bool			IsUnitVector(void)									const;

		float			Magnitude(void)										const;
		float			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
		void			Normalize(void);

		// Get copy of this vector as a unit vector
		Vector4			Normalized(void)									const;

		// Project this vector onto another
		void			ProjectOnto(const Vector4& _other);

		// Reflect this vector onto another
		void			ReflectOnto(const Vector4& _axis);

		// Reflect this vector onto a UNIT vector
		void			ReflectOntoUnit(const Vector4& _axis);

		// Rotate this vector around the all 3 axes (not w)
		void			Rotate(Radian _angleX, Radian _angleY, Radian _angleZ);

		// Rotate this vector around an arbitrary 3D axis
		void			Rotate(Radian _angle, const Vector3& _axis);

		// Multiply this vector's components by another's
		void			Scale(const Vector4& _other);

		// Get components as string
		std::string		String(void)										const;

		// Get components as verbose string
		std::string		StringLong(void)									const;

		// Add another vector's components to this one's
		void			Translate(const Vector4& _other);


		// Accessors

		float&			X(void);
		float&			Y(void);
		float&			Z(void);
		float&			W(void);

		float			GetX(void)											const;
		float			GetY(void)											const;
		float			GetZ(void)											const;
		float			GetW(void)											const;


		Vector4&		operator=(const Vector4& _rhs);

		float&			operator[](int _index);
		float			operator[](int _index)								const;


		// Boolean test operators

		bool			operator==(const Vector4& _rhs)						const;
		bool			operator!=(const Vector4& _rhs)						const;


		// Component-wise operations

		Vector4			operator+(const Vector4& _rhs)						const;
		Vector4			operator-(const Vector4& _rhs)						const;
		Vector4			operator*(const Vector4& _rhs)						const;
		Vector4			operator/(const Vector4& _rhs)						const;


		// Multiply all components by a single scalar
		Vector4			operator*(float _rhs)								const;

		// Divide all components by a single scalar
		Vector4			operator/(float _rhs)								const;

		// Flip sign of both components
		Vector4			operator-(void)										const;


		// Component-wise operations

		Vector4&		operator+=(const Vector4& _rhs);
		Vector4&		operator-=(const Vector4& _rhs);
		Vector4&		operator*=(const Vector4& _rhs);
		Vector4&		operator/=(const Vector4& _rhs);

		// Multiply all components by a single scalar
		Vector4&		operator*=(float _rhs);

		// Divide all components by a single scalar
		Vector4&		operator/=(float _rhs);


		// Constants

		static Vector4	Zero(void);
		static Vector4	One(void);
		static Vector4	Up(void);
		static Vector4	Down(void);
		static Vector4	Left(void);
		static Vector4	Right(void);
		static Vector4  Back(void);
		static Vector4  Front(void);


	private:

		float				m_x = 0.f;
		float				m_y = 0.f;
		float				m_z = 0.f;
		float				m_w = 0.f;
	};

	// Non-member functions (similar to member functions but provided for readability)

	float				Dot(const Vector4& _first, const Vector4& _second);

	Vector4				Reflect(const Vector4& _target, const Vector4& _ontoNormal);
	Vector4				ReflectUnit(const Vector4& _target, const Vector4& _ontoNormal);
	Vector4				Project(const Vector4& _target, const Vector4& _ontoVector);

	Vector4				Normalize(const Vector4& _target);

	float				Distance(const Vector4& _start, const Vector4& _end);
	float				DistanceSquared(const Vector4& _start, const Vector4& _end);

	Vector4				Rotate
	(
		const Vector4& _target, Radian _angleX, Radian _angleY, Radian _angleZ
	);

	Vector4				Rotate
	(
		const Vector4& _target, Radian _angle, const Vector3& _axis
	);

	// Send a vector's components to an output stream
	std::ostream& operator<<(std::ostream& _os, Vector4 const& _vector);

	// Get components from an input stream
	std::istream& operator>>(std::istream& _is, Vector4& _vector);
}

namespace LibMath = ion::math;
namespace lm = LibMath;