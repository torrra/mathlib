#ifndef __MATRIX2_H__
#define __MATRIX2_H__

#include "MathGeneric.hpp"
#include "MatrixGeneric.hpp"

#include "Vector2.hpp"

#include "Angle.hpp"

#include "Arithmetic.hpp"
#include "Trigonometry.hpp"

namespace math
{
    template <CScalarType TValueType>
    class Matrix<2, TValueType>
     {
     private:

         using TMatrixType = Matrix<2, TValueType>;
         using TRowType = Vector<2, TValueType>;

     public:

          // Constructor / destructor

        inline          Matrix(void) = default;
        inline          Matrix(const TValueType diag);

        inline          Matrix(TValueType a, TValueType b, TValueType c, TValueType d);

        inline          Matrix(const TValueType vals[]);
        inline          Matrix(const Matrix& other);

                        ~Matrix(void) = default;

        // Calculate matrix determinant
        inline TValueType      Determinant(void)                   const;

        // Turn this matrix into an identity matrix of a given diagonal
        inline void            Identity(TValueType diag = static_cast<TValueType>(1));

        // Get transposed matrix of cofactors
        inline TMatrixType         Adjugate(void)                      const;

        // Get inverse of this matrix
        inline TMatrixType         Inverse(void)                       const;

        // Get transposed copy of this matrix
        inline TMatrixType         Transpose(void)                     const;

        inline TMatrixType&        operator=(const TMatrixType& rhs);

        // TMatrixType / matrix operators

        inline TMatrixType         operator+(const TMatrixType& rhs)      const;
        inline TMatrixType         operator-(const TMatrixType& rhs)      const;
        inline TMatrixType         operator*(const TMatrixType& rhs)      const;

        // Multiply all numbers of a copy of this matrix by a scalar factor
        inline TMatrixType         operator*(TValueType factor)            const;

        // TMatrixType / matrix assignment operators

        inline TMatrixType&        operator+=(const TMatrixType& rhs);
        inline TMatrixType&        operator-=(const TMatrixType& rhs);
        inline TMatrixType&        operator*=(const TMatrixType& rhs);

        inline bool            operator==(const TMatrixType& rhs)     const;
        inline bool            operator!=(const TMatrixType& rhs)     const;

        // Access a row (no bound checking)
        inline TRowType&    operator[](int index);

        // Access a row (no bound checking)
        inline TRowType    operator[](int index)              const;

        // Get a 2x2 rotation matrix from an angle in radians
        inline static TMatrixType  Rotate(Radian<TValueType> angle);



    private:

        TRowType     m_values[2];
     };







    // ---- Implementations ----


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(TValueType a, TValueType b, TValueType c, TValueType d)
    {
        m_values[0][0] = a;
        m_values[0][1] = b;
        m_values[1][0] = c;
        m_values[1][1] = d;
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(const TValueType diag)
    {
        m_values[0][0] = diag;
        m_values[1][1] = diag;

        m_values[0][1] = static_cast<TValueType>(0);
        m_values[1][0] = static_cast<TValueType>(0);
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(const TValueType vals[])
    {
        m_values[0][0] = vals[0];
        m_values[0][1] = vals[1];
        m_values[1][0] = vals[2];
        m_values[1][1] = vals[3];
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(const Matrix<2, TValueType>& other)
    {
        m_values[0][0] = other.m_values[0][0];
        m_values[0][1] = other.m_values[0][1];
        m_values[1][0] = other.m_values[1][0];
        m_values[1][1] = other.m_values[1][1];
    }


    template <CScalarType TValueType> inline
    TValueType Matrix<2, TValueType>::Determinant(void)    const
    {
        return (m_values[0][0] * m_values[1][1]) -
	           (m_values[0][1] * m_values[1][0]);
    }


    template <CScalarType TValueType> inline
    void Matrix<2, TValueType>::Identity(TValueType diag)
    {
        m_values[0][0] = diag;
	    m_values[0][1] = static_cast<TValueType>(0);
	    m_values[1][0] = static_cast<TValueType>(0);
	    m_values[1][1] = diag;
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Adjugate(void) const
    {
        if constexpr (std::is_unsigned<TValueType>::value)
            throw std::logic_error("Cannot compute adjugate matrix for unsigned type");

        // Transpose cofactors
        else
        {
            return Matrix<2, TValueType>(m_values[1][1], -m_values[0][1],
                                        -m_values[1][0], m_values[0][0]);
        }
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Inverse(void) const
    {
        TValueType       det = Determinant();

        // Divide adjugate by determinant
        if (det != static_cast<TValueType>(0))
            return Adjugate() * (1 / det);

        // Do not devide by zero
        return Matrix<2, TValueType>();
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Transpose(void) const
    {
        // Switch non-diagonal values
        return Matrix<2, TValueType>
        (
            m_values[0][0], m_values[1][0],
            m_values[0][1], m_values[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator=(const Matrix<2, TValueType>& rhs)
    {
        m_values[0][0] = rhs[0][0];
        m_values[0][1] = rhs[0][1];
        m_values[1][0] = rhs[1][0];
        m_values[1][1] = rhs[1][1];

        return *this;

    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator+(const Matrix<2, TValueType>& rhs) const
    {
        // Add components
        return Matrix<2, TValueType>
        (
            m_values[0][0] + rhs[0][0], m_values[0][1] + rhs[0][1],
            m_values[1][0] + rhs[1][0], m_values[1][1] + rhs[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator-(const Matrix<2, TValueType>& rhs) const
    {
        // Subtract components
        return Matrix<2, TValueType>
        (
            m_values[0][0] - rhs.m_values[0][0], m_values[0][1] - rhs.m_values[0][1],
            m_values[1][0] - rhs.m_values[1][0], m_values[1][1] - rhs.m_values[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator*(const Matrix<2, TValueType>& rhs) const
    {
        // TODO: doule check
        // Multiply components
        return Matrix<2, TValueType>
        (
            m_values[0][0] * rhs.m_values[0][0] + m_values[1][0] * rhs.m_values[0][1],
            m_values[0][1] * rhs.m_values[0][0] + m_values[1][1] * rhs.m_values[0][1],
            m_values[0][0] * rhs.m_values[1][0] + m_values[1][0] * rhs.m_values[1][1],
            m_values[0][1] * rhs.m_values[1][0] + m_values[1][1] * rhs.m_values[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator*(TValueType factor) const
    {
        // Multiply by a scalar
        return Matrix<2, TValueType>(
                        m_values[0][0] * factor,
                        m_values[0][1] * factor,
                        m_values[1][0] * factor,
                        m_values[1][1] * factor
                      );
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator+=(const Matrix<2, TValueType>& rhs)
    {
        *this = *this + rhs;

        return *this;
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator-=(const Matrix<2, TValueType>& rhs)
    {
        *this = *this - rhs;

        return *this;
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator*=(const Matrix<2, TValueType>& rhs)
    {
        *this = *this * rhs;

        return *this;
    }



    template <CScalarType TValueType> inline
    bool  Matrix<2, TValueType>::operator==(const Matrix<2, TValueType>& rhs) const
    {
        // Check if all componenents are almost equal
        return math::AlmostEqual(m_values[0][0], rhs[0][0]) &&
               math::AlmostEqual(m_values[0][1], rhs[0][1]) &&
               math::AlmostEqual(m_values[1][0], rhs[1][0]) &&
               math::AlmostEqual(m_values[1][1], rhs[1][1]);
    }


    template <CScalarType TValueType> inline
    bool Matrix<2, TValueType>::operator!=(const Matrix<2, TValueType>& rhs) const
    {
        return !(*this == rhs);
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType>&
    Matrix<2, TValueType>::operator[](int index)
    {
        return m_values[index];
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType>
    Matrix<2, TValueType>::operator[](int index) const
    {
        return m_values[index];
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Rotate(Radian<TValueType> angle)
    {
        if constexpr (std::is_unsigned<TValueType>::value)
            throw std::logic_error("Cannot compute unsigned rotation matrix");

        else
        {
            TValueType   cosAngle = Cos(angle), sinAngle = Sin(angle);

            // Create z axis rotation matrix (non-homogenized)
            return Matrix<2, TValueType>
                (
                    cosAngle, -sinAngle,
                    sinAngle, cosAngle
                );
        }
    }


// !Implementation


}


namespace LibMath = math;
namespace lm = math;

#endif