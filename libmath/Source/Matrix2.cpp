#include "libmath/Matrix2.h"
#include "libmath/Arithmetic.h"

namespace mth
{
    Matrix2::Matrix2(float _diag)
    {
        m_values[0][0] = _diag;
        m_values[1][1] = _diag;
    }

    Matrix2::Matrix2(float _a, float _b, float _c, float _d)
    {
        m_values[0][0] = _a;
        m_values[0][1] = _b;
        m_values[1][0] = _c;
        m_values[1][1] = _d;
    }


    Matrix2::Matrix2(float _vals[])
    {
        m_values[0][0] = _vals[0];
        m_values[0][1] = _vals[1];
        m_values[1][0] = _vals[2];
        m_values[1][1] = _vals[3];
    }


    Matrix2::Matrix2(const Matrix2& _other)
    {
        m_values[0][0] = _other.m_values[0][0];
        m_values[0][1] = _other.m_values[0][1];
        m_values[1][0] = _other.m_values[1][0];
        m_values[1][1] = _other.m_values[1][1];
    }


    float Matrix2::Determinant(void)    const
    {
        return (m_values[0][0] * m_values[1][1]) -
	           (m_values[0][1] * m_values[1][0]);
    }


    void Matrix2::Identity(float _diag)
    {
        m_values[0][0] = _diag;
	    m_values[0][1] = 0.f;
	    m_values[1][0] = 0.f;
	    m_values[1][1] = _diag;
    }

    Matrix2 Matrix2::Adjugate(void) const
    {
        return Matrix2(m_values[1][1], -m_values[0][1],
                       -m_values[1][0], m_values[0][0]);
    }

    Matrix2 Matrix2::Inverse(void) const
    {
        float       det = Determinant();

        if (det != 0.f)
            return Adjugate() * (1 / det);

        return Matrix2();
    }

    Matrix2 Matrix2::Transpose(void) const
    {
        return Matrix2
        (
            m_values[0][0], m_values[1][0],
            m_values[0][1], m_values[1][1]
        );
    }


    Matrix2& Matrix2::operator=(const Matrix2& _rhs)
    {
        m_values[0][0] = _rhs[0][0];
        m_values[0][1] = _rhs[0][1];
        m_values[1][0] = _rhs[1][0];
        m_values[1][1] = _rhs[1][1];

        return *this;

    }

    Matrix2 Matrix2::operator+(const Matrix2& _rhs) const
    {
        return Matrix2
        (
            m_values[0][0] + _rhs[0][0], m_values[0][1] + _rhs[0][1],
            m_values[1][0] + _rhs[1][0], m_values[1][1] + _rhs[1][1]
        );
    }

    Matrix2 Matrix2::operator-(const Matrix2& _rhs) const
    {
        return Matrix2
        (
            m_values[0][0] - _rhs.m_values[0][0], m_values[0][1] - _rhs.m_values[0][1],
            m_values[1][0] - _rhs.m_values[1][0], m_values[1][1] - _rhs.m_values[1][1]
        );
    }

    Matrix2 Matrix2::operator*(const Matrix2& _rhs) const
    {
        return Matrix2
        (
            m_values[0][0] * _rhs.m_values[0][0] + m_values[1][0] * _rhs.m_values[0][1],
            m_values[0][1] * _rhs.m_values[0][0] + m_values[1][1] * _rhs.m_values[0][1],
            m_values[0][0] * _rhs.m_values[1][0] + m_values[1][0] * _rhs.m_values[1][1],
            m_values[0][1] * _rhs.m_values[1][0] + m_values[1][1] * _rhs.m_values[1][1]
        );
    }


    Matrix2 Matrix2::operator*(float _factor) const
    {
        return Matrix2(
                        m_values[0][0] * _factor,
                        m_values[0][1] * _factor,
                        m_values[1][0] * _factor,
                        m_values[1][1] * _factor
                      );
    }

    Matrix2& Matrix2::operator+=(const Matrix2& _rhs)
    {
        *this = *this + _rhs;

        return *this;
    }

    Matrix2& Matrix2::operator-=(const Matrix2& _rhs)
    {
        *this = *this - _rhs;

        return *this;
    }

    Matrix2& Matrix2::operator*=(const Matrix2& _rhs)
    {
        *this = *this * _rhs;

        return *this;
    }

    bool  Matrix2::operator==(const Matrix2& _rhs) const
    {
        return mth::almostEqual(m_values[0][0], _rhs[0][0]) &&
               mth::almostEqual(m_values[0][1], _rhs[0][1]) &&
               mth::almostEqual(m_values[1][0], _rhs[1][0]) &&
               mth::almostEqual(m_values[1][1], _rhs[1][1]);
    }

    bool Matrix2::operator!=(const Matrix2& _rhs) const
    {
        return !(*this == _rhs);
    }


    float* Matrix2::operator[](int _index)
    {
        return m_values[_index];
    }

    float const* Matrix2::operator[](int _index) const
    {
        return m_values[_index];
    }
}
