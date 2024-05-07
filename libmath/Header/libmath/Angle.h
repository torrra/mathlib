#pragma once

#define MTH_PI		3.141592653589f
#define RAD_CIRCLE	6.283185307179f
#define DEG2RAD		0.0174532925f
#define RAD2DEG		57.29577951308f

namespace mth
{
	class Radian;

	class Degree
	{
	public:

				Degree(void) = default;
	explicit	Degree(float _val);
				Degree(const Degree& _other);
				~Degree(void) = default;

	operator	Radian(void)							const;


	float		Deg(bool _wrap180 = false)				const;
	float		Rad(bool _wrapPi = true)				const;
	float		Raw()									const;

	void		Wrap(bool _wrap180 = false);

	Degree&		operator=(const Degree& _rhs);
	Degree&		operator=(float _rhs);

	Degree		operator+(const Degree& _rhs)			const;
	Degree		operator-(const Degree& _rhs)			const;
	Degree		operator*(const Degree& _rhs)			const;
	Degree		operator/(const Degree& _rhs)			const;

	Degree		operator+(float _rhs)					const;
	Degree		operator-(float _rhs)					const;
	Degree		operator*(float _rhs)					const;
	Degree		operator/(float _rhs)					const;

	Degree& 	operator+=(const Degree& _rhs);
	Degree&		operator-=(const Degree& _rhs);
	Degree&		operator*=(const Degree& _rhs);
	Degree&		operator/=(const Degree& _rhs);


	Degree&		operator+=(float _rhs);
	Degree&		operator-=(float _rhs);
	Degree&		operator*=(float _rhs);
	Degree&		operator/=(float _rhs);


	bool		operator==(const Degree& _rhs)			const;
	bool		operator!=(const Degree& _rhs)			const;

	bool		operator==(float _rhs)					const;
	bool		operator!=(float _rhs)					const;


	private:

		float	m_value = 0.f;
	};


	class Radian
	{
	public:

				Radian(void) = default;
	explicit	Radian(float _val);
				Radian(const Radian& _other);
				~Radian(void) = default;

	operator	Degree(void)							const;


	float		Deg(bool _wrap180 = false)				const;
	float		Rad(bool _wrapPi = true)				const;
	float		Raw()									const;

	void		Wrap(bool _wrap180 = false);

	Radian		operator+(const Radian& _rhs)			const;
	Radian		operator-(const Radian& _rhs)			const;
	Radian		operator*(const Radian& _rhs)			const;
	Radian		operator/(const Radian& _rhs)			const;

	Radian&		operator+=(const Radian& _rhs);
	Radian&		operator-=(const Radian& _rhs);
	Radian&		operator*=(const Radian& _rhs);
	Radian&		operator/=(const Radian& _rhs);


	Radian		operator+(float _rhs)					const;
	Radian		operator-(float _rhs)					const;
	Radian		operator*(float _rhs)					const;
	Radian		operator/(float _rhs)					const;


	Radian&		operator+=(float _rhs);
	Radian&		operator-=(float _rhs);
	Radian&		operator*=(float _rhs);
	Radian&		operator/=(float _rhs);


	bool		operator==(const Radian& _rhs)			const;
	bool		operator!=(const Radian& _rhs)			const;

	bool		operator==(float _rhs)			const;
	bool		operator!=(float _rhs)			const;

	private:

		float m_value = 0.f;

	};

	inline namespace Literal
	{
		Degree		operator""_deg(long double _val);
		Degree		operator""_deg(unsigned long long int _val);

		Radian		operator""_rad(long double _val);
		Radian		operator""_rad(unsigned long long int _val);

	}
}