#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include <numeric>

#include "Vector3.hpp"
#include "MathGeneric.hpp"
#include "Arithmetic.hpp"
#include "Matrix4.hpp"
#include "Trigonometry.hpp"
#include "Interpolation.hpp"

namespace math
{
    // W is the real part, XYZ is the vector part
    template <CFloatingType TValueType>
    class Quaternion
    {

    public:

        Quaternion(void) = default;
        Quaternion(const Quaternion&) = default;

        inline				Quaternion(TValueType w, TValueType x, TValueType y, TValueType z);
        explicit inline		Quaternion(TValueType value);
        inline				Quaternion(const Vector3<TValueType>& axis, const Radian<TValueType>& angle);
        inline				Quaternion(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ);

        ~Quaternion(void) = default;

        inline TValueType	Length(void)			const;
        inline TValueType	LengthSquared(void)		const;

        inline Quaternion	Conjugate(void)			const;
        inline Quaternion	Inverse(void)			const;

        inline Quaternion	Normalized(void)		const;
        inline bool			IsUnit(void)			const;
        inline bool			IsPure(void)			const;
        inline bool			IsReal(void)			const;

        inline void			Normalize(void);

        inline
        Matrix4<TValueType> RotationMatrix(void)	const;


        Vector3<TValueType> Rotate(const Vector3<TValueType>& vector)   const;
        Vector3<TValueType> EulerAngles(void) const;

        inline Quaternion& operator=(const Quaternion& rhs);

        inline
       Vector3<TValueType>	operator*(const Vector3<TValueType>& rhs) const;

        inline Quaternion	operator*(TValueType rhs) const;
        inline Quaternion	operator/(TValueType rhs) const;

        inline Quaternion	operator*(const Quaternion& rhs) const;
        inline Quaternion	operator+(const Quaternion& rhs) const;
        inline Quaternion	operator-(const Quaternion& rhs) const;

        inline Quaternion& operator*=(const Quaternion& rhs);
        inline Quaternion& operator+=(const Quaternion& rhs);
        inline Quaternion& operator-=(const Quaternion& rhs);

        inline bool			operator==(const Quaternion& rhs) const;
        inline bool			operator!=(const Quaternion& rhs) const;

        inline Quaternion	operator-(void)					  const;

        static Quaternion   Slerp(const Quaternion& q1, const Quaternion& q2, TValueType ration);


        TValueType	        GetW() const { return m_w; }
        TValueType	        GetX() const { return m_x; }
        TValueType	        GetY() const { return m_y; }
        TValueType	        GetZ() const { return m_z; }

        TValueType& W() { return m_w; }
        TValueType& X() { return m_x; }
        TValueType& Y() { return m_y; }
        TValueType& Z() { return m_z; }

    private:

        TValueType				m_w;
        TValueType				m_x;
        TValueType				m_y;
        TValueType				m_z;

    };


    template <CFloatingType TValueType>
    Matrix4<TValueType> TransformMatrix(const Quaternion<TValueType>& rotation, const Vector3<TValueType>& translation);

    //template <CFloatingType TValueType>
    //Matrix4<TValueType> TransformMatrix(const Quaternion<TValueType>& rotation, const Vector3<TValueType>& translation, const Vector3<TValueType>& scale);

    template <CFloatingType TValueType>
    TValueType			Dot(const Quaternion<TValueType>& q1, const Quaternion<TValueType>& q2);

    using Quatf = Quaternion<float>;
    using Quatd = Quaternion<double>;


    template <CFloatingType TValueType>
    Quaternion<TValueType>::Quaternion(TValueType w, TValueType x, TValueType y, TValueType z)
        : m_w(w), m_x(x), m_y(y), m_z(z)
    {

    }

    template <CFloatingType TValueType>
    Quaternion<TValueType>::Quaternion(TValueType value)
        : m_w(value), m_x(value), m_y(value), m_z(value)
    {

    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>::Quaternion(const Vector3<TValueType>& axis, const Radian<TValueType>& angle)
    {
        TValueType angleHalf = angle.Rad() * (TValueType)0.5;
        TValueType sinAngle = sin(angleHalf);

        m_w = cos(angleHalf);
        m_x = sinAngle * Cos(axis.AngleFrom(Vector3<TValueType>::Right()));
        m_y = sinAngle * Cos(axis.AngleFrom(Vector3<TValueType>::Up()));
        m_z = sinAngle * Cos(axis.AngleFrom(Vector3<TValueType>::Front()));
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>::Quaternion(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
    {
        angleX *= (TValueType) 0.5;
        angleY *= (TValueType) 0.5;
        angleZ *= (TValueType) 0.5;

        TValueType cosX = Cos(angleX), sinX = Sin(angleX);
        TValueType cosY = Cos(angleY), sinY = Sin(angleY);
        TValueType cosZ = Cos(angleZ), sinZ = Sin(angleZ);

        m_w = cosX * cosY * cosZ + sinX * sinY * sinZ;
        m_x = sinX * cosY * cosZ - cosX * sinY * sinZ;
        m_y = cosX * sinY * cosZ + sinX * cosY * sinZ;
        m_z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    }

    template<CFloatingType TValueType>
    inline TValueType Quaternion<TValueType>::LengthSquared(void) const
    {
        return m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType> Quaternion<TValueType>::Conjugate(void) const
    {
        return Quaternion<TValueType>(m_w, -m_x, -m_y, -m_z);
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType> Quaternion<TValueType>::Inverse(void) const
    {
        return Conjugate() / LengthSquared();
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType> Quaternion<TValueType>::Normalized(void) const
    {
        Quaternion<TValueType>		copy(*this);

        copy.Normalize();
        return copy;
    }

    template<CFloatingType TValueType>
    inline void Quaternion<TValueType>::Normalize(void)
    {
        TValueType lengthDiv = static_cast<TValueType>(1) / Length();

        m_w *= lengthDiv;
        m_x *= lengthDiv;
        m_y *= lengthDiv;
        m_z *= lengthDiv;
    }

    template<CFloatingType TValueType>
    inline Matrix4<TValueType> Quaternion<TValueType>::RotationMatrix(void) const
    {

        Matrix4<TValueType> mat;
        TValueType	 xSqr = m_x * m_x, ySqr = m_y * m_y, zSqr = m_z * m_z;
        TValueType	 wSqr = m_w * m_w;

        mat[0][0] = wSqr + xSqr - ySqr - zSqr;
        mat[1][0] = 2 * (m_x * m_y) + 2 * (m_w * m_z);
        mat[2][0] = 2 * (m_x * m_z) - 2 * (m_w * m_y);
        mat[3][0] = 0.f;

        mat[0][1] = 2 * (m_x * m_y) - 2 * (m_w * m_z);
        mat[1][1] = wSqr - xSqr + ySqr - zSqr;
        mat[2][1] = 2 * (m_y * m_z) + 2 * (m_w * m_x);
        mat[3][1] = 0.f;

        mat[0][2] = 2 * (m_x * m_z) + 2 * (m_w * m_y);
        mat[1][2] = 2 * (m_y * m_z) - 2 * (m_w * m_x);
        mat[2][2] = wSqr - xSqr - ySqr + zSqr;
        mat[3][2] = 0.f;

        mat[0][3] = 0.f;
        mat[1][3] = 0.f;
        mat[2][3] = 0.f;
        mat[3][3] = 1.f;

        return mat;
    }



    template<CFloatingType TValueType>
    inline Vector3<TValueType> Quaternion<TValueType>::Rotate(const Vector3<TValueType>& vector) const
    {
        Vector3<TValueType>     quatVector(m_x, m_y, m_z);

        Vector3<TValueType>     doubleCross = Cross(quatVector, vector) * (TValueType) 2;

        return vector + (doubleCross * m_w) + Cross(quatVector, doubleCross);
    }


    template<CFloatingType TValueType>
    inline Vector3<TValueType> Quaternion<TValueType>::operator*(const Vector3<TValueType>& vector) const
    {
        return Rotate(vector);
    }


    template<CFloatingType TValueType>
    inline Vector3<TValueType> Quaternion<TValueType>::EulerAngles(void) const
    {
        // x axis
        TValueType		atan2Y = ((TValueType)(2)) * (m_w * m_x + m_y * m_z);
        TValueType		atan2X = m_w * m_w - m_x * m_x - m_y * m_y + m_z * m_z;
        TValueType		x = Atan2(atan2Y, atan2X).Raw();

        // y axis
        TValueType      sine = static_cast<TValueType>(2) * (m_w * m_y - m_x * m_z);

        // avoid domain errors
        sine = Clamp(sine, static_cast<TValueType>(-1), static_cast<TValueType>(1));

        TValueType      y = Asin(sine).Raw();


        // z axis
        atan2Y = ((TValueType)(2)) * (m_w * m_z + m_x * m_y);
        atan2X = m_w * m_w + m_x * m_x - m_y * m_y - m_z * m_z;

        TValueType	    z = Atan2(atan2Y, atan2X).Raw();

        return Vector3<TValueType>(x, y, z);
    }

    template<CFloatingType TValueType>
    inline TValueType Quaternion<TValueType>::Length(void) const
    {
        return SquareRoot(LengthSquared());
    }


    template<CFloatingType TValueType>
    inline bool	 Quaternion<TValueType>::operator==(const Quaternion<TValueType>& rhs) const
    {
        return AlmostEqual(m_w, rhs.m_w) &&
            AlmostEqual(m_x, rhs.m_x) &&
            AlmostEqual(m_y, rhs.m_y) &&
            AlmostEqual(m_z, rhs.m_z);
    }


    template<CFloatingType TValueType>
    inline bool	 Quaternion<TValueType>::operator!=(const Quaternion<TValueType>& rhs) const
    {
        return !((*this) == rhs);
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType> Quaternion<TValueType>::Slerp(const Quaternion<TValueType>& q1, const Quaternion<TValueType>& q2, TValueType ratio)
    {

        TValueType cosAngle = Dot(q1, q2);

        TValueType sign = (cosAngle < static_cast<TValueType>(0)) ?
            static_cast<TValueType>(-1) : static_cast<TValueType>(1);

        cosAngle *= sign;

        TValueType coefQ1 = static_cast<TValueType>(1) - ratio;
        TValueType coefQ2 = ratio * sign;

        if (cosAngle < static_cast<TValueType>(0.9999))
        {
            TValueType angle = acos(cosAngle);
            TValueType invSin = static_cast<TValueType>(1) / sin(angle);

            coefQ1 = sin(coefQ1 * angle) * invSin;
            coefQ2 = sin(coefQ2 * angle) * invSin;
        }

        return Quaternion<TValueType>(
            coefQ1 * q1.m_w + coefQ2 * q2.m_w,
            coefQ1 * q1.m_x + coefQ2 * q2.m_x,
            coefQ1 * q1.m_y + coefQ2 * q2.m_y,
            coefQ1 * q1.m_z + coefQ2 * q2.m_z
        );


    }

    template<CFloatingType TValueType>
    inline bool Quaternion<TValueType>::IsUnit(void) const
    {
        return AlmostEqual(LengthSquared(), static_cast<TValueType>(1));
    }

    template<CFloatingType TValueType>
    inline bool Quaternion<TValueType>::IsPure(void) const
    {
        return AlmostEqual(m_w, static_cast<TValueType>(0));
    }

    template<CFloatingType TValueType>
    inline bool Quaternion<TValueType>::IsReal(void) const
    {
        return AlmostEqual(m_x, static_cast<TValueType>(0)) &&
               AlmostEqual(m_y, static_cast<TValueType>(0)) &&
               AlmostEqual(m_z, static_cast<TValueType>(0));
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>& Quaternion<TValueType>::operator=(const Quaternion<TValueType>& rhs)
    {
        m_w = rhs.m_w;
        m_x = rhs.m_x;
        m_y = rhs.m_y;
        m_z = rhs.m_z;

        return *this;
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>	 Quaternion<TValueType>::operator*(TValueType rhs) const
    {
        // Product of real parts - dot product of vector parts
        TValueType w = this->m_w * rhs;

        TValueType x = this->m_x * rhs;
        TValueType y = this->m_y * rhs;
        TValueType z = this->m_z * rhs;

        return Quaternion<TValueType>(w, x, y, z);

        //return Quaternion<TValueType>(x, y, z, w);
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>	 Quaternion<TValueType>::operator/(TValueType rhs) const
    {
        rhs = static_cast<TValueType>(1) / rhs;

        return (*this) * rhs;
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>	 Quaternion<TValueType>::operator*(const Quaternion<TValueType>& rhs) const
    {
        // Product of real parts - dot product of vector parts
        TValueType w = this->m_w * rhs.m_w - this->m_x * rhs.m_x - this->m_y * rhs.m_y - this->m_z * rhs.m_z;

        TValueType x = this->m_w * rhs.m_x + this->m_x * rhs.m_w + this->m_y * rhs.m_z - this->m_z * rhs.m_y;
        TValueType y = this->m_w * rhs.m_y - this->m_x * rhs.m_z + this->m_y * rhs.m_w + this->m_z * rhs.m_x;
        TValueType z = this->m_w * rhs.m_z + this->m_x * rhs.m_y - this->m_y * rhs.m_x + this->m_z * rhs.m_w;

        return Quaternion<TValueType>(w, x, y, z);
    }


    template<CFloatingType TValueType>
    inline Quaternion<TValueType>& Quaternion<TValueType>::operator*=(const Quaternion<TValueType>& rhs)
    {
        (*this) = (*this) * rhs;
        return *this;
    }


    template<CFloatingType TValueType>
    inline Quaternion<TValueType>	 Quaternion<TValueType>::operator+(const Quaternion<TValueType>& rhs) const
    {
        TValueType x = this->m_w + rhs.m_w;
        TValueType y = this->m_x + rhs.m_x;
        TValueType z = this->m_y + rhs.m_y;
        TValueType w = this->m_z + rhs.m_z;

        return Quaternion<TValueType>(x, y, z, w);
    }


    template<CFloatingType TValueType>
    inline Quaternion<TValueType>	 Quaternion<TValueType>::operator-(const Quaternion<TValueType>& rhs) const
    {
        TValueType x = this->m_w - rhs.m_w;
        TValueType y = this->m_x - rhs.m_x;
        TValueType z = this->m_y - rhs.m_y;
        TValueType w = this->m_z - rhs.m_z;

        return Quaternion<TValueType>(x, y, z, w);
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>& Quaternion<TValueType>::operator+=(const Quaternion<TValueType>& rhs)
    {
        (*this) = (*this) + rhs;
        return *this;
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>& Quaternion<TValueType>::operator-=(const Quaternion<TValueType>& rhs)
    {
        (*this) = (*this) - rhs;
        return *this;
    }

    template<CFloatingType TValueType>
    inline Quaternion<TValueType>	 Quaternion<TValueType>::operator-(void) const
    {
        return Quaternion<TValueType>(m_x, m_y, m_z, m_w);
    }

    template<CFloatingType TValueType>
    Matrix4<TValueType> TransformMatrix(const Quaternion<TValueType>& rotation, const Vector3<TValueType>& translation)
    {
        Matrix4<TValueType> matrix{ 1.f };

        matrix[0][3] = translation.GetX();
        matrix[1][3] = translation.GetY();
        matrix[2][3] = translation.GetZ();

        matrix *= rotation.RotationMatrix() /** matrix*/;

        return matrix;
    }

    template<CFloatingType TValueType>
    TValueType Dot(const Quaternion<TValueType>& q1, const Quaternion<TValueType>& q2)
    {
        return q1.GetX() * q2.GetX() + q1.GetY() * q2.GetY() + q1.GetZ() * q2.GetZ() + q1.GetW() * q2.GetW();
    }
}


#endif