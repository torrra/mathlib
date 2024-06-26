#pragma once

#include "MathGeneric.hpp"
#include "Arithmetic.h"

#define MTH_PI				3.141592653589f


#define RAD_CIRCLE			6.283185307179f
#define PI_OVER_FOUR		0.785398163397f
#define PI_OVER_TWO			1.570796326794f


#define DEG2RAD				0.0174532925f
#define RAD2DEG				57.29577951308f


#define DEG_PRECISION		1.f
#define RAD_PRECISION		0.0001f

#define HALF_CIRCLE_DEG		180.f
#define FULL_CIRCLE_DEG		360.f

namespace ion::math
{
	template <CScalarType TValueType = float>
	class Radian;

	class Degree
	{
	public:

		// Constructors / Destructors

		Degree(void) = default;
		explicit	Degree(float _val);
		Degree(const Degree& _other);
		~Degree(void) = default;

		operator Radian<float>(void)							const;


		// Accessors
		float		Deg(bool _wrap180 = false)				const;
		float		Rad(bool _wrapPi = true)				const;
		float		Raw()									const;

		// Wrap around unit circle
		void		Wrap(bool _wrap180 = false);

		// Copy assignment
		Degree& operator=(const Degree& _rhs);
		Degree& operator=(float _rhs);

		// Arithmetic operators
		Degree		operator+(const Degree& _rhs)			const;
		Degree		operator-(const Degree& _rhs)			const;
		Degree		operator*(const Degree& _rhs)			const;
		Degree		operator/(const Degree& _rhs)			const;

		Degree		operator+(float _rhs)					const;
		Degree		operator-(float _rhs)					const;
		Degree		operator*(float _rhs)					const;
		Degree		operator/(float _rhs)					const;

		// Arithmetic assignment operators
		Degree& operator+=(const Degree& _rhs);
		Degree& operator-=(const Degree& _rhs);
		Degree& operator*=(const Degree& _rhs);
		Degree& operator/=(const Degree& _rhs);


		Degree& operator+=(float _rhs);
		Degree& operator-=(float _rhs);
		Degree& operator*=(float _rhs);
		Degree& operator/=(float _rhs);

		// Negation operators
		Degree		operator-(void)							const;

		// Equality operators
		bool		operator==(const Degree& _rhs)			const;
		bool		operator!=(const Degree& _rhs)			const;

		bool		operator==(float _rhs)					const;
		bool		operator!=(float _rhs)					const;


	private:

		float	m_value = 0.f;
	};

	template <CScalarType TValueType>
	class Radian
	{
	public:

		// Constructor / Destructors
	inline		Radian(void) = default;

	explicit
	inline  	Radian(TValueType _val);
				Radian(const Radian& _other);
				~Radian(void) = default;

				// Implicit cast operator
	inline		operator Degree(void)										const;

				// Accessors
	inline		TValueType		Rad(bool _wrapPi = true)					const;
	inline		TValueType		Deg(bool _wrap180 = false)					const;
	inline		TValueType		Raw()										const;

				// Wrap around unit circle
	inline		void			Wrap(bool _wrap180 = false);


				// Copy assignment
	inline		Radian&			operator=(const Radian& _rhs);
	inline		Radian&			operator=(TValueType _rhs);


				// Arithmetic operators
	inline		Radian			operator+(const Radian& _rhs)				const;
	inline		Radian			operator-(const Radian& _rhs)				const;
	inline		Radian			operator*(const Radian& _rhs)				const;
	inline		Radian			operator/(const Radian& _rhs)				const;

		        // Arithmetic assignment
	inline		Radian&			operator+=(const Radian& _rhs);
	inline		Radian&			operator-=(const Radian& _rhs);
	inline		Radian&			operator*=(const Radian& _rhs);
	inline		Radian&			operator/=(const Radian& _rhs);

				// Arithmetic with scalar
	inline		Radian			operator+(TValueType _rhs)					const;
	inline		Radian			operator-(TValueType _rhs)					const;
	inline		Radian			operator*(TValueType _rhs)					const;
	inline		Radian			operator/(TValueType _rhs)					const;

				// Arithmetic assignment with scalar
	inline		Radian&			operator+=(TValueType _rhs);
	inline		Radian&			operator-=(TValueType _rhs);
	inline		Radian&			operator*=(TValueType _rhs);
	inline		Radian&			operator/=(TValueType _rhs);

				// Negate value
	inline		Radian			operator-(void)								const;

				// Equality operators
	inline		bool			operator==(const Radian& _rhs)				const;
	inline		bool			operator!=(const Radian& _rhs)				const;

	inline		bool			operator==(TValueType _rhs)					const;
	inline		bool			operator!=(TValueType _rhs)					const;

	private:

		TValueType	m_value = 0.f;

	};

	// Angle literals
	inline namespace Literal
	{
		Degree						operator""_deg(long double _val);
		Degree						operator""_deg(unsigned long long int _val);

		inline Radian<float>		operator""_rad(long double _val);
		inline Radian<float>		operator""_rad(unsigned long long int _val);

	}







// ---- Radian implementation ----

	template <CScalarType TValueType> inline
	Radian<TValueType>::Radian(TValueType _val)
		: m_value(_val) {}



	template <CScalarType TValueType> inline
	Radian<TValueType>::Radian(const Radian<TValueType>& _other)
		: m_value(_other.m_value) {}



	template <CScalarType TValueType> inline
	Radian<TValueType>::operator Degree(void) const
	{
		// Converti value to radians and construct object
		return Degree(Deg(false));
	}


	template <CScalarType TValueType> inline
	TValueType Radian<TValueType>::Radian::Deg(bool _wrap180) const
	{
		// Wrap value depending on argument
		if (_wrap180)
			return ion::math::Wrap(m_value * RAD2DEG, -HALF_CIRCLE_DEG, HALF_CIRCLE_DEG);

		else
			return ion::math::Wrap(m_value * RAD2DEG, 0.f, FULL_CIRCLE_DEG);
	}



	template <CScalarType TValueType> inline
	TValueType Radian<TValueType>::Rad(bool _wrapPi) const
	{
		// Use custom wrap as libmath wrap is not precise enough

		// Treat value as positive
		float			absValue = Absolute(m_value);

		// Wrap around unit circle
		if (absValue >= RAD_CIRCLE)
		{
			float	circleCount = Floor(absValue / RAD_CIRCLE);

			absValue -= circleCount * RAD_CIRCLE;
		}

		// Wrap again if range is -pi, pi
		if (_wrapPi)
		{
			if (absValue >= MTH_PI)
				absValue -= RAD_CIRCLE;

			// Restore sign
			if (m_value < 0.f && absValue > 0.f)
				absValue = -absValue;

		}

		// Add negative value to circle if range is 0, 2pi
		else if (m_value < 0.f)
		{
			absValue = RAD_CIRCLE - absValue;
		}

		return absValue;


	}


	template <CScalarType TValueType> inline
	TValueType Radian<TValueType>::Raw() const
	{
		return m_value;
	}

	template <CScalarType TValueType> inline
	void Radian<TValueType>::Wrap(bool _wrap180)
	{
		// Set raw value to wrapped value
		m_value = Rad(_wrap180);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator=(const Radian<TValueType>& _rhs)
	{
		// Copy assignment

		m_value = _rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator=(TValueType _rhs)
	{
		// Copy assignment

		m_value = _rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator+(const Radian<TValueType>& _rhs) const
	{
		// Addition

		return Radian(m_value + _rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator-(const Radian<TValueType>& _rhs) const
	{
		// Subtraction
		return Radian(m_value - _rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator*(const Radian<TValueType>& _rhs) const
	{
		// Multiplication
		return Radian<TValueType>(m_value * _rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator/(const Radian<TValueType>& _rhs) const
	{
		// Division
		return Radian(m_value / _rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator+=(const Radian<TValueType>& _rhs)
	{
		// Addition assignment
		m_value += _rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator-=(const Radian<TValueType>& _rhs)
	{
		// Subtraction assignment
		m_value -= _rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator*=(const Radian<TValueType>& _rhs)
	{
		// Multiplication assignment
		m_value *= _rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator/=(const Radian<TValueType>& _rhs)
	{
		// Division assignment
		m_value /= _rhs.m_value;

		return *this;
	}



	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator+(TValueType _rhs) const
	{
		// Addition
		return Radian(m_value + _rhs);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator-(TValueType _rhs) const
	{
		// Subtraction
		return Radian(m_value - _rhs);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator*(TValueType _rhs) const
	{
		// Multiplication
		return Radian(m_value * _rhs);
	}



	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator/(TValueType _rhs) const
	{
		// Division
		return Radian(m_value / _rhs);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator+=(TValueType _rhs)
	{
		// Addition assignment
		m_value += _rhs;

		return *this;
	}



	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator-=(TValueType _rhs)
	{
		// Subtraction assignment
		m_value -= _rhs;

		return *this;
	}



	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator*=(TValueType _rhs)
	{
		// Multiplication assignment
		m_value *= _rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator/=(TValueType _rhs)
	{
		// Division assignment
		m_value /= _rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator-(void) const
	{
		// Flip sign
		return Radian(-m_value);
	}


	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator==(const Radian<TValueType>& _rhs) const
	{
		return AlmostEqual
		(
			Rad(false),
			_rhs.Rad(false),
			RAD_PRECISION
		);
	}


	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator!=(const Radian<TValueType>& _rhs) const
	{
		// Not equal
		return !(*this == _rhs);
	}



	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator==(TValueType _rhs) const
	{
		return AlmostEqual
		(
			Rad(false),
			_rhs,
			RAD_PRECISION
		);
	}



	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator!=(TValueType _rhs) const
	{
		// Not equal
		return !(*this == _rhs);
	}



	inline Radian<float> ion::math::Literal::operator""_rad(long double _val)
	{
		// Get numeric value from literal
		return Radian(static_cast<float>(_val));
	}


	inline Radian<float> ion::math::Literal::operator""_rad(unsigned long long int _val)
	{
		// Get numeric value from literal
		return Radian(static_cast<float>(_val));
	}



// !Radian implementation


}

namespace	LibMath = ion::math;
namespace	lm = ion::math;