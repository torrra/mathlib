#pragma once

#include <string>

#include "libmath/Angle.h"

namespace mth
{
	class Vector3
	{
	public:
						Vector3(void) = default;

		explicit		Vector3(float _val);
						Vector3(float _x, float _y, float _z);
						Vector3(const Vector3& _other);

						~Vector3(void) = default;

		Radian			AngleFrom(const Vector3& _other)					const;
		Radian			AngleFromUnit(const Vector3& _other)				const;

		Vector3			Cross(const Vector3& _other)						const;

		float			DistanceFrom(const Vector3& _other)					const;
		float			DistanceSquaredFrom(const Vector3& _other)			const;

		float			Distance2DFrom(Vector3 const&)						const;
		float			Distance2DSquaredFrom(Vector3 const&)				const;


		float			Dot(const Vector3& _other)							const;

		bool			IsLongerThan(const Vector3& _other)					const;
		bool			IsShorterThan(const Vector3& _other)				const;

		bool			IsUnitVector(void)									const;

		float			Magnitude(void)										const;
		float			MagnitudeSquared(void)								const;

		void			Normalize(void);
		Vector3			Normalized(void)									const;

		void			ProjectOnto(const Vector3& _other);

		void			ReflectOnto(const Vector3& _axis);
		void			ReflectOntoUnit(const Vector3& _axis);

		void			Rotate(Radian _angleX, Radian _angleY, Radian _angleZ);
		void			Rotate(Radian _angle, const Vector3& _axis);

		void			Scale(const Vector3& _other);

		std::string		String(void)										const;
		std::string		StringLong(void)									const;

		void			Translate(const Vector3& _other);

		float&			X(void);
		float&			Y(void);
		float&			Z(void);

		float			GetX(void)											const;
		float			GetY(void)											const;
		float			GetZ(void)											const;


		Vector3&		operator=(const Vector3& _rhs);

		float&			operator[](int _index);
		float			operator[](int _index)								const;


		bool			operator==(const Vector3& _rhs)						const;
		bool			operator!=(const Vector3& _rhs)						const;


		Vector3			operator+(const Vector3& _rhs)						const;
		Vector3			operator-(const Vector3& _rhs)						const;
		Vector3			operator*(const Vector3& _rhs)						const;
		Vector3			operator/(const Vector3& _rhs)						const;

		Vector3			operator*(float _rhs)								const;
		Vector3			operator/(float _rhs)								const;


		Vector3			operator-(void)										const;

		Vector3&		operator+=(const Vector3& _rhs);
		Vector3&		operator-=(const Vector3& _rhs);
		Vector3&		operator*=(const Vector3& _rhs);
		Vector3&		operator/=(const Vector3& _rhs);

		Vector3&		operator*=(float _rhs);
		Vector3&		operator/=(float _rhs);




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


	std::ostream&		operator<<(std::ostream& _os, Vector3 const& _vector);
	std::istream&		operator>>(std::istream& _is, Vector3& _vector);
}

namespace LibMath = mth;
namespace lm = LibMath;