#pragma once

#include <string>

#include "libmath/Angle.h"
#include "libmath/Vector3.h"

namespace mth
{
	class Vector4
	{
	public:
						Vector4(void) = default;

		explicit		Vector4(float _val);
						Vector4(float _x, float _y, float _z, float _w);
						Vector4(const Vector4& _other);

						~Vector4(void) = default;

		Radian			AngleFrom(const Vector4& _other)					const;
		Radian			AngleFromUnit(const Vector4& _other)				const;


		float			DistanceFrom(const Vector4& _other)					const;
		float			DistanceSquaredFrom(const Vector4& _other)			const;

		float			Distance2DFrom(Vector4 const& _other)				const;
		float			Distance2DSquaredFrom(Vector4 const& _other)		const;

		float			Distance3DFrom(Vector4 const& _other)				const;
		float			Distance3DSquaredFrom(Vector4 const& _other)		const;



		float			Dot(const Vector4& _other)							const;

		bool			IsLongerThan(const Vector4& _other)					const;
		bool			IsShorterThan(const Vector4& _other)				const;

		bool			IsUnitVector(void)									const;

		float			Magnitude(void)										const;
		float			MagnitudeSquared(void)								const;

		void			Normalize(void);
		Vector4			Normalized(void)									const;

		void			ProjectOnto(const Vector4& _other);

		void			ReflectOnto(const Vector4& _axis);
		void			ReflectOntoUnit(const Vector4& _axis);

		void			Rotate(Radian _angleX, Radian _angleY, Radian _angleZ);
		void			Rotate(Radian _angle, const Vector3& _axis);

		void			Scale(const Vector4& _other);

		std::string		String(void)										const;
		std::string		StringLong(void)									const;

		void			Translate(const Vector4& _other);

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


		bool			operator==(const Vector4& _rhs)						const;
		bool			operator!=(const Vector4& _rhs)						const;


		Vector4			operator+(const Vector4& _rhs)						const;
		Vector4			operator-(const Vector4& _rhs)						const;
		Vector4			operator*(const Vector4& _rhs)						const;
		Vector4			operator/(const Vector4& _rhs)						const;

		Vector4			operator*(float _rhs)								const;
		Vector4			operator/(float _rhs)								const;


		Vector4			operator-(void)										const;

		Vector4&		operator+=(const Vector4& _rhs);
		Vector4&		operator-=(const Vector4& _rhs);
		Vector4&		operator*=(const Vector4& _rhs);
		Vector4&		operator/=(const Vector4& _rhs);

		Vector4&		operator*=(float _rhs);
		Vector4&		operator/=(float _rhs);




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


	std::ostream& operator<<(std::ostream& _os, Vector4 const& _vector);
	std::istream& operator>>(std::istream& _is, Vector4& _vector);
}

namespace LibMath = mth;
namespace lm = LibMath;