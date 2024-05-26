#pragma once

#include "libmath/Matrix3.h"

namespace mth
{
	class Matrix4
	{
	public:

		Matrix4(void) = default;
		Matrix4(const float _diag);
		Matrix4(const float _vals[][4]);
		Matrix4(const float _vals[]);
		Matrix4(const Matrix4& _other);

		~Matrix4(void) = default;

		float           Determinant(void)                   const;

		void            Identity(float _diag = 1.f);

		Matrix4         Adjugate(void)                      const;


		Matrix4         Minor(void)                         const;
		Matrix4         Cofactor(void)                      const;
		Matrix4         Inverse(void)                       const;
		Matrix4         Transpose(void)                     const;

		Matrix3         SubMatrix(int _row, int _column)    const;

		Matrix4&		operator=(const Matrix4& _rhs);
		Matrix4&		operator=(const float _rhs[][4]);
		Matrix4&		operator=(const float _rhs[16]);

		Matrix4         operator+(const Matrix4& _rhs)      const;
		Matrix4         operator-(const Matrix4& _rhs)      const;
		Matrix4         operator*(const Matrix4& _rhs)      const;

		Matrix4         operator*(float _factor)            const;
		Matrix4         operator/(float _factor)            const;

		Matrix4&		operator+=(const Matrix4& _rhs);
		Matrix4&		operator-=(const Matrix4& _rhs);
		Matrix4&		operator*=(const Matrix4& _rhs);

		Matrix4&		operator*=(float _factor);
		Matrix4&		operator/=(float _factor);

		bool            operator==(const Matrix4& _rhs)     const;
		bool            operator!=(const Matrix4& _rhs)     const;

		float*			operator[](int _index);
		float const*	operator[](int _index)              const;


	private:

		float       m_values[4][4] = { {0.f} };

	};
}

namespace lm = mth;
namespace LibMath = lm;