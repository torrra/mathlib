#ifndef __ANGLE_H__
#define __ANGLE_H__


#include "MathGeneric.hpp"
#include "Arithmetic.hpp"


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

namespace math
{
	template <CScalarType TValueType = float>
	class Radian;



	template <CScalarType TValueType = float>
	class Degree
	{
	public:

		// Constructors / Destructors

	inline		Degree(void) = default;

	explicit
	inline	    Degree(TValueType val);

	inline		Degree(const Degree& other);
	inline		~Degree(void) = default;

	inline		operator Radian<TValueType>(void)			const;


		// Accessors
	inline		TValueType		Deg(bool wrap180 = false)				const;
	inline		TValueType		Rad(bool wrapPi = true)				const;
	inline		TValueType		Raw()									const;

		// Wrap around unit circle
	inline		void			Wrap(bool wrap180 = false);

		// Copy assignment
	inline		Degree&			operator=(const Degree<TValueType>& rhs);
	inline		Degree&			operator=(TValueType rhs);

		// Arithmetic operators
	inline		Degree			operator+(const Degree& rhs)				const;
	inline		Degree			operator-(const Degree& rhs)				const;
	inline		Degree			operator*(const Degree& rhs)				const;
	inline		Degree			operator/(const Degree& rhs)				const;

	inline		Degree			operator+(TValueType rhs)					const;
	inline		Degree			operator-(TValueType rhs)					const;
	inline		Degree			operator*(TValueType rhs)					const;
	inline		Degree			operator/(TValueType rhs)					const;

		// Arithmetic assignment operators
	inline		Degree&			operator+=(const Degree& rhs);
	inline		Degree&			operator-=(const Degree& rhs);
	inline		Degree&			operator*=(const Degree& rhs);
	inline		Degree&			operator/=(const Degree& rhs);


	inline		Degree&			operator+=(TValueType rhs);
	inline		Degree&			operator-=(TValueType rhs);
	inline		Degree&			operator*=(TValueType rhs);
	inline		Degree&			operator/=(TValueType rhs);

		// Negation operators
	inline		Degree			operator-(void)								const;

		// Equality operators
	inline		bool			operator==(const Degree& rhs)				const;
	inline		bool			operator!=(const Degree& rhs)				const;

	inline		bool			operator==(TValueType rhs)					const;
	inline		bool			operator!=(TValueType rhs)					const;


	private:

		TValueType	m_value = static_cast<TValueType>(0);
	};





	template <CScalarType TValueType>
	class Radian
	{
	public:

		// Constructor / Destructors
	inline		Radian(void) = default;

	explicit
	inline  	Radian(TValueType val);
				Radian(const Radian& other);
				~Radian(void) = default;

				// Implicit cast operator
	inline		operator Degree<TValueType>(void)										const;

				// Accessors
	inline		TValueType		Rad(bool wrapPi = true)					const;
	inline		TValueType		Deg(bool wrap180 = false)					const;
	inline		TValueType		Raw()										const;

				// Wrap around unit circle
	inline		void			Wrap(bool wrap180 = false);


				// Copy assignment
	inline		Radian&			operator=(const Radian& rhs);
	inline		Radian&			operator=(TValueType rhs);


				// Arithmetic operators
	inline		Radian			operator+(const Radian& rhs)				const;
	inline		Radian			operator-(const Radian& rhs)				const;
	inline		Radian			operator*(const Radian& rhs)				const;
	inline		Radian			operator/(const Radian& rhs)				const;

		        // Arithmetic assignment
	inline		Radian&			operator+=(const Radian& rhs);
	inline		Radian&			operator-=(const Radian& rhs);
	inline		Radian&			operator*=(const Radian& rhs);
	inline		Radian&			operator/=(const Radian& rhs);

				// Arithmetic with scalar
	inline		Radian			operator+(TValueType rhs)					const;
	inline		Radian			operator-(TValueType rhs)					const;
	inline		Radian			operator*(TValueType rhs)					const;
	inline		Radian			operator/(TValueType rhs)					const;

				// Arithmetic assignment with scalar
	inline		Radian&			operator+=(TValueType rhs);
	inline		Radian&			operator-=(TValueType rhs);
	inline		Radian&			operator*=(TValueType rhs);
	inline		Radian&			operator/=(TValueType rhs);

				// Negate value
	inline		Radian			operator-(void)								const;

				// Equality operators
	inline		bool			operator==(const Radian& rhs)				const;
	inline		bool			operator!=(const Radian& rhs)				const;

	inline		bool			operator==(TValueType rhs)					const;
	inline		bool			operator!=(TValueType rhs)					const;

	private:

		TValueType	m_value = static_cast<TValueType>(0);

	};

	// Angle literals
	inline namespace Literal
	{
		inline Degree<float>		operator""_deg(long double val);
		inline Degree<float>		operator""_deg(unsigned long long int val);

		inline Radian<float>		operator""_rad(long double val);
		inline Radian<float>		operator""_rad(unsigned long long int val);

	}





// ---- Degree implementation

	template <CScalarType TValueType>
	Degree<TValueType>::Degree(TValueType val)
		: m_value(val) {}



	template <CScalarType TValueType>
	Degree<TValueType>::Degree(const Degree<TValueType>& other)
		: m_value(other.m_value) {}



	template <CScalarType TValueType>
	Degree<TValueType>::operator Radian<TValueType>() const
	{
		// Convert deg value to rad
		return Radian<TValueType>(Rad(false));
	}

	template <CScalarType TValueType>
	TValueType Degree<TValueType>::Deg(bool wrap180) const
	{
		// Wrap value depending on argument

		if (wrap180)
			return math::Wrap(m_value, -HALF_CIRCLE_DEG, HALF_CIRCLE_DEG);

		else
			return math::Wrap(m_value, 0.f, FULL_CIRCLE_DEG);
	}



	template <CScalarType TValueType>
	TValueType Degree<TValueType>::Rad(bool wrapPi) const
	{
		// Wrap value depending on argument

		if (wrapPi)
			return math::Wrap(m_value * DEG2RAD, -MTH_PI, MTH_PI);

		else
			return math::Wrap(m_value * DEG2RAD, 0.f, RAD_CIRCLE);
	}



	template <CScalarType TValueType>
	TValueType Degree<TValueType>::Raw(void) const
	{
		return m_value;
	}



	template <CScalarType TValueType>
	void Degree<TValueType>::Wrap(bool wrap180)
	{
		// Assign wrapped value to raw value
		m_value = Deg(wrap180);
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator=(const Degree& rhs)
	{
		// Copy assignment

		m_value = rhs.m_value;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator=(TValueType rhs)
	{
		// Copy assignment

		m_value = rhs;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator+(const Degree& rhs) const
	{
		// Addition

		return Degree<TValueType>(m_value + rhs.m_value);
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator-(const Degree<TValueType>& rhs) const
	{
		// Subtraction

		return Degree<TValueType>(m_value - rhs.m_value);
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator*(const Degree<TValueType>& rhs) const
	{
		// Multiplication

		return Degree(m_value * rhs.m_value);
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator/(const Degree<TValueType>& rhs) const
	{
		// Division

		return Degree(m_value / rhs.m_value);
	}




	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator+(TValueType rhs) const
	{
		// Addition

		return Degree<TValueType>(m_value + rhs);
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator-(TValueType rhs) const
	{
		// Subtraction

		return Degree<TValueType>(m_value - rhs);
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator*(TValueType rhs) const
	{
		// Multiplication
		return Degree<TValueType>(m_value * rhs);
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator/(TValueType rhs) const
	{
		// Division
		return Degree<TValueType>(m_value / rhs);
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator+=(const Degree& rhs)
	{
		// Addition assignment

		m_value += rhs.m_value;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator-=(const Degree& rhs)
	{
		// Subtraction assignment

		m_value -= rhs.m_value;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator*=(const Degree& rhs)
	{
		// Multiplication assignment

		m_value *= rhs.m_value;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator/=(const Degree& rhs)
	{
		// Division assignment

		m_value /= rhs.m_value;

		return *this;
	}




	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator+=(TValueType rhs)
	{
		// Addition assignment

		m_value += rhs;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator-=(TValueType rhs)
	{
		// Subtraction assignment

		m_value -= rhs;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator*=(TValueType rhs)
	{
		// Multiplication assignment

		m_value *= rhs;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType>& Degree<TValueType>::operator/=(TValueType rhs)
	{
		// Division assignment

		m_value /= rhs;

		return *this;
	}



	template <CScalarType TValueType>
	Degree<TValueType> Degree<TValueType>::operator-(void) const
	{
		// Flip sign
		return Degree<TValueType>(-m_value);
	}



	template <CScalarType TValueType>
	bool Degree<TValueType>::operator==(const Degree<TValueType>& rhs) const
	{
		return AlmostEqual
		(
			Deg(false),
			rhs.Deg(false),
			DEG_PRECISION
		);
	}



	template <CScalarType TValueType>
	bool Degree<TValueType>::operator!=(const Degree& rhs) const
	{
		// Not equal
		return !(*this == rhs);
	}



	template <CScalarType TValueType>
	bool Degree<TValueType>::operator==(TValueType rhs) const
	{
		return AlmostEqual<TValueType>
		(
			Deg(false),
			rhs,
			DEG_PRECISION
		);
	}



	template <CScalarType TValueType>
	bool Degree<TValueType>::operator!=(TValueType rhs) const
	{
		// Not equal
		return !(*this == rhs);
	}






// !Degree implementation





// ---- Radian implementation ----

	template <CScalarType TValueType> inline
	Radian<TValueType>::Radian(TValueType val)
		: m_value(val) {}



	template <CScalarType TValueType> inline
	Radian<TValueType>::Radian(const Radian<TValueType>& other)
		: m_value(other.m_value) {}



	template <CScalarType TValueType> inline
	Radian<TValueType>::operator Degree<TValueType>(void) const
	{
		// Converti value to radians and construct object
		return Degree<TValueType>(Deg(false));
	}


	template <CScalarType TValueType> inline
	TValueType Radian<TValueType>::Radian::Deg(bool wrap180) const
	{
		// Wrap value depending on argument
		if (wrap180)
			return math::Wrap(m_value * RAD2DEG, -HALF_CIRCLE_DEG, HALF_CIRCLE_DEG);

		else
			return math::Wrap(m_value * RAD2DEG, 0.f, FULL_CIRCLE_DEG);
	}



	template <CScalarType TValueType> inline
	TValueType Radian<TValueType>::Rad(bool wrapPi) const
	{
		// Use custom wrap as math wrap is not precise enough

		// Treat value as positive
		float			absValue = Absolute(m_value);

		// Wrap around unit circle
		if (absValue >= RAD_CIRCLE)
		{
			float	circleCount = Floor(absValue / RAD_CIRCLE);

			absValue -= circleCount * RAD_CIRCLE;
		}

		// Wrap again if range is -pi, pi
		if (wrapPi)
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
	void Radian<TValueType>::Wrap(bool wrap180)
	{
		// Set raw value to wrapped value
		m_value = Rad(wrap180);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator=(const Radian<TValueType>& rhs)
	{
		// Copy assignment

		m_value = rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator=(TValueType rhs)
	{
		// Copy assignment

		m_value = rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator+(const Radian<TValueType>& rhs) const
	{
		// Addition

		return Radian(m_value + rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator-(const Radian<TValueType>& rhs) const
	{
		// Subtraction
		return Radian(m_value - rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator*(const Radian<TValueType>& rhs) const
	{
		// Multiplication
		return Radian<TValueType>(m_value * rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator/(const Radian<TValueType>& rhs) const
	{
		// Division
		return Radian(m_value / rhs.m_value);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator+=(const Radian<TValueType>& rhs)
	{
		// Addition assignment
		m_value += rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator-=(const Radian<TValueType>& rhs)
	{
		// Subtraction assignment
		m_value -= rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator*=(const Radian<TValueType>& rhs)
	{
		// Multiplication assignment
		m_value *= rhs.m_value;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator/=(const Radian<TValueType>& rhs)
	{
		// Division assignment
		m_value /= rhs.m_value;

		return *this;
	}



	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator+(TValueType rhs) const
	{
		// Addition
		return Radian(m_value + rhs);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator-(TValueType rhs) const
	{
		// Subtraction
		return Radian(m_value - rhs);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator*(TValueType rhs) const
	{
		// Multiplication
		return Radian(m_value * rhs);
	}



	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator/(TValueType rhs) const
	{
		// Division
		return Radian(m_value / rhs);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator+=(TValueType rhs)
	{
		// Addition assignment
		m_value += rhs;

		return *this;
	}



	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator-=(TValueType rhs)
	{
		// Subtraction assignment
		m_value -= rhs;

		return *this;
	}



	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator*=(TValueType rhs)
	{
		// Multiplication assignment
		m_value *= rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType>& Radian<TValueType>::operator/=(TValueType rhs)
	{
		// Division assignment
		m_value /= rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Radian<TValueType>::operator-(void) const
	{
		// Flip sign
		return Radian(-m_value);
	}


	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator==(const Radian<TValueType>& rhs) const
	{
		return AlmostEqual
		(
			Rad(false),
			rhs.Rad(false),
			RAD_PRECISION
		);
	}


	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator!=(const Radian<TValueType>& rhs) const
	{
		// Not equal
		return !(*this == rhs);
	}



	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator==(TValueType rhs) const
	{
		return AlmostEqual
		(
			Rad(false),
			rhs,
			RAD_PRECISION
		);
	}


// !Radian implementation




// ---- Literal operators implementation ----

	template <CScalarType TValueType> inline
	bool Radian<TValueType>::operator!=(TValueType rhs) const
	{
		// Not equal
		return !(*this == rhs);
	}



	inline Radian<float> math::Literal::operator""_rad(long double val)
	{
		// Get numeric value from literal
		return Radian(static_cast<float>(val));
	}


	inline Radian<float> math::Literal::operator""_rad(unsigned long long int val)
	{
		// Get numeric value from literal
		return Radian(static_cast<float>(val));
	}


	inline Degree<float> math::Literal::operator""_deg(long double val)
	{
		// Get numeric value from literal
		return Degree<float>(static_cast<float>(val));
	}

	inline Degree<float> Literal::operator""_deg(unsigned long long int val)
	{
		// Get numeric value from literal
		return Degree<float>(static_cast<float>(val));
	}


}


// !Literal operators implementation

namespace	LibMath = math;
namespace	lm = math;


#endif