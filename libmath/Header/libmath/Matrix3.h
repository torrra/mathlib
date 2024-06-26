#pragma once

#include "libmath/Vector3.h"
#include "libmath/Matrix2.h"

namespace ion::math
{
	class Matrix3
	{
    public:

        // Constructors / destructor

                        Matrix3(void) = default;
                        Matrix3(const float _diag);
                        Matrix3(const float _vals[][3]);
                        Matrix3(const float _vals[]);
                        Matrix3(const Matrix3& _other);

                        ~Matrix3(void) = default;

        // Get this matrix' determinant
        float           Determinant(void)                   const;

        // Turn this matrix into an identity matrix with a given diagonal
        void            Identity(float _diag = 1.f);

        // Get this matrix' transposed cofactor matrix
        Matrix3         Adjugate(void)                      const;

        // Get a matrix of all 2x2 submatrices' determinants within
        // this matrix
        Matrix3         Minor(void)                         const;

        // Get a matrix of this matrix' cofactors taken from all 2x2
        // matrices within it
        Matrix3         Cofactor(void)                      const;

        // Get inverse of this matrix
        Matrix3         Inverse(void)                       const;

        // Get a transposed copy of this matrix
        Matrix3         Transpose(void)                     const;

        // Get this matrix stripped of a row and a column
        Matrix2         SubMatrix(int _row, int _column)    const;

        Matrix3&        operator=(const Matrix3& _rhs);
        Matrix3&        operator=(const float _rhs[][3]);
        Matrix3&        operator=(const float _rhs[9]);

        // Matrix / matrix operators

        Matrix3         operator+(const Matrix3& _rhs)      const;
        Matrix3         operator-(const Matrix3& _rhs)      const;
        Matrix3         operator*(const Matrix3& _rhs)      const;

        Vector3<float>         operator*(const Vector3<float>& _rhs)      const;

        // Multiply all numbers of a copy of this matrix by a scalar factor
        Matrix3         operator*(float _factor)            const;

        // Divide all numbers of a copy of this matrix by a scalar factor
        Matrix3         operator/(float _factor)            const;

        // Matrix / matrix assignment operators

        Matrix3&        operator+=(const Matrix3& _rhs);
        Matrix3&        operator-=(const Matrix3& _rhs);
        Matrix3&        operator*=(const Matrix3& _rhs);

        // Multiply all numbers of a copy of this matrix by a scalar factor
        Matrix3&        operator*=(float _factor);

        // Divide all numbers of a copy of this matrix by a scalar factor
        Matrix3&        operator/=(float _factor);

        bool            operator==(const Matrix3& _rhs)     const;
        bool            operator!=(const Matrix3& _rhs)     const;

        // Access a row (no bound checking)
        float*          operator[](int _index);

        // Access a row (no bound checking)
        float const*    operator[](int _index)              const;


    private:

        float       m_values[3][3] = { {0.f} };

    };

}

namespace lm = ion::math;
namespace LibMath = ion::math;