#pragma once

#include <string>

#include "libmath/Angle.h"

namespace mth
{
	class Vector2
	{
	public:
						Vector2(void) = default;

		explicit		Vector2(float _val);
						Vector2(float _x, float _y);
						Vector2(const Vector2& _other );

						~Vector2(void) = default;

		Radian			AngleFrom(const Vector2& _other)					const;
		Radian			AngleFromUnit(const Vector2& _other)				const;

		float			Cross(const Vector2& _other)						const;

		float			DistanceFrom(const Vector2& _other)					const;
		float			DistanceSquaredFrom(const Vector2& _other)			const;


		float			Dot(const Vector2& _other)							const;

		bool			IsLongerThan(const Vector2& _other)					const;
		bool			IsShorterThan(const Vector2& _other)				const;

		bool			IsUnitVector(void)									const;

		float			Magnitude(void)										const;
		float			MagnitudeSquared(void)								const;

		void			Normalize(void);
		Vector2			Normalized(void)									const;

		void			ProjectOnto(const Vector2& _other);

		void			ReflectOnto(const Vector2& _axis);
		void			ReflectOntoUnit(const Vector2& _axis);

		void			Rotate(Radian _angle);

		void			Scale(const Vector2& _other);

		std::string		String(void)										const;
		std::string		StringLong(void)									const;

		void			Translate(const Vector2& _other);

		float&			X(void);
		float&			Y(void);

		float			GetX(void)											const;
		float			GetY(void)											const;


		Vector2&		operator=(const Vector2& _rhs);

		float&			operator[](int _index);
		float			operator[](int _index)								const;


		bool			operator==(const Vector2& _rhs)						const;
		bool			operator!=(const Vector2& _rhs)						const;


		Vector2			operator+(const Vector2& _rhs)						const;
		Vector2			operator-(const Vector2& _rhs)						const;
		Vector2			operator*(const Vector2& _rhs)						const;
		Vector2			operator/(const Vector2& _rhs)						const;

		Vector2			operator*(float _rhs)								const;
		Vector2			operator/(float _rhs)								const;


		Vector2			operator-(void)										const;

		Vector2&		operator+=(const Vector2& _rhs);
		Vector2&		operator-=(const Vector2& _rhs);
		Vector2&		operator*=(const Vector2& _rhs);
		Vector2&		operator/=(const Vector2& _rhs);

		Vector2&		operator*=(float _rhs);
		Vector2&		operator/=(float _rhs);




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

	float				Dot(const Vector2& _first, const Vector2& _second);
	float				Cross(const Vector2& _first, const Vector2& _second);

	Vector2				Reflect(const Vector2& _target, const Vector2& _ontoNormal);
	Vector2				ReflectUnit(const Vector2& _target, const Vector2& _ontoNormal);
	Vector2				Project(const Vector2& _target, const Vector2& _ontoVector);

	Vector2				Normalize(const Vector2& _target);

	float				Distance(const Vector2& _start, const Vector2& _end);
	float				DistanceSquared(const Vector2& _start, const Vector2& _end);

	Vector2				Rotate(const Vector2& _target, Radian _angle);


	std::ostream&		operator<<(std::ostream& _os, Vector2 const& _vector);
	std::istream&		operator>>(std::istream& _is, Vector2& _vector);
}

namespace LibMath = mth;
namespace lm = LibMath;