#pragma once

#include "libmath/Matrix3.h"
#include "libmath/Vector4.h"

namespace ion::math
{
	class Matrix4
	{
	public:

		// Constructors / destructor

						Matrix4(void) = default;
						Matrix4(const float _diag);
						Matrix4(const float _vals[][4]);
						Matrix4(const float _vals[]);
						Matrix4(const Matrix4& _other);

						~Matrix4(void) = default;

		// Get this matrix' determinant
		float           Determinant(void)                   const;

		// Turn this matrix into an identity matrix with a given diagonal
		void            Identity(float _diag = 1.f);

		// Get this matrix' transposed cofactor matrix
		Matrix4         Adjugate(void)                      const;

		// Get a matrix of all 3x3 submatrices' determinants within
		// this matrix
		Matrix4         Minor(void)                         const;

		// Get a matrix of this matrix' cofactors taken from all 3x3
		// matrices within it
		Matrix4         Cofactor(void)                      const;

		// Get inverse of this matrix
		Matrix4         Inverse(void)                       const;

		// Get a transposed copy of this matrix
		Matrix4         Transpose(void)                     const;

		// Get this matrix stripped of a row and a column
		Matrix3f         SubMatrix(int _row, int _column)    const;

		Matrix4&		operator=(const Matrix4& _rhs);
		Matrix4&		operator=(const float _rhs[][4]);
		Matrix4&		operator=(const float _rhs[16]);


		// Matrix / matrix operators

		Matrix4         operator+(const Matrix4& _rhs)      const;
		Matrix4         operator-(const Matrix4& _rhs)      const;
		Matrix4         operator*(const Matrix4& _rhs)      const;

		// Multiply a vector 4D by this matrix
		Vector4         operator*(const Vector4& _rhs)      const;


		// Multiply all numbers of a copy of this matrix by a scalar factor
		Matrix4         operator*(float _factor)            const;

		// Divide all numbers of a copy of this matrix by a scalar factor
		Matrix4         operator/(float _factor)            const;


		// Matrix / matrix assignment operators


		Matrix4&		operator+=(const Matrix4& _rhs);
		Matrix4&		operator-=(const Matrix4& _rhs);
		Matrix4&		operator*=(const Matrix4& _rhs);

		// Multiply all numbers of a copy of this matrix by a scalar factor
		Matrix4&		operator*=(float _factor);

		// Divide all numbers of a copy of this matrix by a scalar factor
		Matrix4&		operator/=(float _factor);

		bool            operator==(const Matrix4& _rhs)     const;
		bool            operator!=(const Matrix4& _rhs)     const;

		// Access a row (no bound checking)
		float*			operator[](int _index);

		// Access a row (no bound checking)
		float const*	operator[](int _index)              const;


	private:

		float       m_values[4][4] = { {0.f} };

	};
}

namespace lm = ion::math;
namespace LibMath = lm;