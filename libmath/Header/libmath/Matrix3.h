#pragma once

#include "libmath/Matrix2.h"

namespace mth
{
	class Matrix3
	{
    public:

        Matrix3(void) = default;
        Matrix3(const float _diag);
        Matrix3(const float _vals[][3]);
        Matrix3(const float _vals[]);
        Matrix3(const Matrix3& _other);

        ~Matrix3(void) = default;

        float           Determinant(void)                   const;

        void            Identity(float _diag = 1.f);

        Matrix3         Adjugate(void)                      const;


        Matrix3         Minor(void)                         const;
        Matrix3         Cofactor(void)                      const;
        Matrix3         Inverse(void)                       const;
        Matrix3         Transpose(void)                     const;

        Matrix2         SubMatrix(int _row, int _column)    const;

        Matrix3&        operator=(const Matrix3& _rhs);
        Matrix3&        operator=(const float _rhs[][3]);
        Matrix3&        operator=(const float _rhs[9]);

        Matrix3         operator+(const Matrix3& _rhs)      const;
        Matrix3         operator-(const Matrix3& _rhs)      const;
        Matrix3         operator*(const Matrix3& _rhs)      const;

        Matrix3         operator*(float _factor)            const;
        Matrix3         operator/(float _factor)            const;

        Matrix3&        operator+=(const Matrix3& _rhs);
        Matrix3&        operator-=(const Matrix3& _rhs);
        Matrix3&        operator*=(const Matrix3& _rhs);

        Matrix3&        operator*=(float _factor);
        Matrix3&        operator/=(float _factor);

        bool            operator==(const Matrix3& _rhs)     const;
        bool            operator!=(const Matrix3& _rhs)     const;

        float*          operator[](int _index);
        float const*    operator[](int _index)              const;


    private:

        float       m_values[3][3] = { {0.f} };

    };

}

namespace lm = mth;
namespace LibMath = mth;