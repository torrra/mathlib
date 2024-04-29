#include "libmath/Matrix.h"

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

    float* Matrix2::operator[](int _index)
    {
        return m_values[_index];
    }
}
