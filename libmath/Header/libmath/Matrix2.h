#pragma once

namespace mth
{
    class Matrix2
    {
    public:

                        Matrix2(void) = default;
                        Matrix2(float _diag);
                        Matrix2(float _a, float _b, float _c, float _d);
                        Matrix2(float _vals[]);
                        Matrix2(const Matrix2& _other);

                        ~Matrix2(void) = default;

        float           Determinant(void)                   const;

        void            Identity(float _diag = 1.f);

        Matrix2         Adjugate(void)                      const;
        Matrix2         Inverse(void)                       const;

        Matrix2&        operator=(const Matrix2& _rhs);

        Matrix2         operator+(const Matrix2& _rhs)      const;
        Matrix2         operator-(const Matrix2& _rhs)      const;
        Matrix2         operator*(const Matrix2& _rhs)      const;

        Matrix2         operator*(float _factor)            const;

        Matrix2&        operator+=(const Matrix2& _rhs);
        Matrix2&        operator-=(const Matrix2& _rhs);
        Matrix2&        operator*=(const Matrix2& _rhs);

        bool            operator==(const Matrix2& _rhs)     const;
        bool            operator!=(const Matrix2& _rhs)     const;

        float*          operator[](int _index);
        float const*    operator[](int _index)              const;


    private:

        float       m_values[2][2] = {{0.f}};


    };
}