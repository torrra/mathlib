#pragma once

#include "libmath/Angle.h"

namespace mth
{
    class Matrix2
    {
    public:

        // Constructor / destructor

                        Matrix2(void) = default;
                        Matrix2(const float _diag);
                        Matrix2(float _a, float _b, float _c, float _d);
                        Matrix2(const float _vals[]);
                        Matrix2(const Matrix2& _other);

                        ~Matrix2(void) = default;

        // Calculate matrix determinant
        float           Determinant(void)                   const;

        // Turn this matrix into an identity matrix of a given diagonal
        void            Identity(float _diag = 1.f);

        // Get transposed matrix of cofactors
        Matrix2         Adjugate(void)                      const;

        // Get inverse of this matrix
        Matrix2         Inverse(void)                       const;

        // Get transposed copy of this matrix
        Matrix2         Transpose(void)                     const;

        Matrix2&        operator=(const Matrix2& _rhs);

        // Matrix / matrix operators

        Matrix2         operator+(const Matrix2& _rhs)      const;
        Matrix2         operator-(const Matrix2& _rhs)      const;
        Matrix2         operator*(const Matrix2& _rhs)      const;

        // Multiply all numbers of a copy of this matrix by a scalar factor
        Matrix2         operator*(float _factor)            const;

        // MAtrix / matrix assignment operators

        Matrix2&        operator+=(const Matrix2& _rhs);
        Matrix2&        operator-=(const Matrix2& _rhs);
        Matrix2&        operator*=(const Matrix2& _rhs);

        bool            operator==(const Matrix2& _rhs)     const;
        bool            operator!=(const Matrix2& _rhs)     const;

        // Access a row (no bound checking)
        float*          operator[](int _index);

        // Access a row (no bound checking)
        float const*    operator[](int _index)              const;

        // Get a 2x2 rotation matrix from an angle in radians
        static Matrix2  Rotate(Radian _angle);

    private:

        float       m_values[2][2] = {{0.f}};


    };
}

namespace LibMath = mth;
namespace lm = mth;