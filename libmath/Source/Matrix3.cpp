//#include "libmath/Matrix3.h"
//#include "libmath/Matrix2.h"
//
//#include "libmath/Arithmetic.h"
//
//namespace ion::math
//{
//	Matrix3::Matrix3(const float _diag)
//	{
//		Identity(_diag);
//	}
//
//	Matrix3::Matrix3(const float _vals[][3])
//	{
//		// Copy 3x3 array into matix
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				m_values[row][column] = _vals[row][column];
//			}
//		}
//	}
//
//	Matrix3::Matrix3(const float _vals[])
//	{
//		int		arrayIndex = 0;
//
//
//		// Copy 1D array into matix
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column, ++arrayIndex)
//			{
//				m_values[row][column] = _vals[arrayIndex];
//			}
//		}
//	}
//
//
//	Matrix3::Matrix3(const Matrix3& _other)
//	{
//		int		maxSize = 3;
//
//		// Copy other matrix into this matrix
//		for (int row = 0; row < maxSize; ++row)
//		{
//			for (int column = 0; column < maxSize; ++column)
//			{
//				m_values[row][column] = _other[row][column];
//			}
//		}
//	}
//
//	float Matrix3::Determinant(void) const
//	{
//		// Add multiplied left-right diagonals together
//		float		positiveDiags
//		{
//			m_values[0][0] * m_values[1][1] * m_values[2][2] +
//			m_values[0][1] * m_values[1][2] * m_values[2][0] +
//			m_values[0][2] * m_values[1][0] * m_values[2][1]
//		};
//
//		// Add multiplied right-left diagonals together
//		float		negativeDiags
//		{
//			m_values[0][2] * m_values[1][1] * m_values[2][0] +
//			m_values[0][1] * m_values[1][0] * m_values[2][2] +
//			m_values[0][0] * m_values[1][2] * m_values[2][1]
//		};
//
//		// Subtract negative diagonals from positive diagnonals
//		return positiveDiags - negativeDiags;
//	}
//
//	void Matrix3::Identity(float _diag)
//	{
//		int		maxSize = 3;
//
//		// Zero-out matrix except for diagonal
//		for (int row = 0; row < maxSize; ++row)
//		{
//			for (int column = 0; column < maxSize; ++column)
//			{
//				m_values[row][column] = (row == column) ? _diag : 0.f;
//			}
//		}
//	}
//
//
//	Matrix3 Matrix3::Adjugate(void) const
//	{
//		Matrix3			result;
//
//		float			sign = 1;
//
//		// Avoid call to transpose by running one nested loop
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				// Compute minor and transpose (row and column switched)
//				result[column][row] = SubMatrix(row, column)
//									  .Determinant();
//
//				// Minor to cofactor (multiply by sign)
//				result[column][row] *= sign;
//
//				// Flip sign (instead of calling pow(-1, row + colum))
//				sign *= -1;
//			}
//		}
//
//		return result;
//	}
//
//
//
//	Matrix3 Matrix3::Minor(void) const
//	{
//		Matrix3		result;
//
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				// Minor = stripped matrix' determinant
//				result[row][column] = SubMatrix(row, column)
//									  .Determinant();
//			}
//		}
//
//		return result;
//	}
//
//
//	Matrix3 Matrix3::Cofactor(void) const
//	{
//		Matrix3			result;
//
//		float			sign = 1;
//
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				// Compute minor
//				result[row][column] = SubMatrix(row, column)
//									 .Determinant();
//
//				// Minot to cofactor
//				result[row][column] *= sign;
//
//				sign *= -1;
//			}
//		}
//
//		return result;
//	}
//
//	Matrix3 Matrix3::Inverse(void) const
//	{
//		// Perform only one division
//		float			invDeterminant = 1.f / Determinant();
//		Matrix3			result;
//		float			sign = 1;
//
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				// Compute minor and transpose
//				result[column][row] = SubMatrix(row, column)
//									  .Determinant();
//
//				// Minor to cofactor
//				result[column][row] *= sign;
//
//				// Cofactor to inverse
//				result[column][row] *= invDeterminant;
//
//				// Flip next sign
//				sign *= -1;
//			}
//		}
//
//		return result;
//	}
//
//
//	Matrix3 Matrix3::Transpose(void) const
//	{
//		Matrix3		result;
//
//		// Assign opposite row-colum combination for each value
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				result[row][column] = m_values[column][row];
//			}
//		}
//
//		return result;
//
//	}
//
//
//
//	Matrix2<float> Matrix3::SubMatrix(int _row, int _column) const
//	{
//		Matrix2<float>		minor;
//
//		// Go through matrix and ignore row argument
//		for (int thisRow = 0, mat2Row = 0; thisRow < 3; ++thisRow)
//		{
//			if (_row == thisRow)
//				continue;
//
//			for (int thisColumn = 0, mat2Column = 0; thisColumn < 3; ++thisColumn)
//			{
//				// Ignore column parameter
//				if (_column == thisColumn)
//					continue;
//
//				minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
//			}
//
//			++mat2Row;
//		}
//
//		// Get stripped 2x2 matrix
//		return minor;
//	}
//
//
//	Matrix3& Matrix3::operator=(const Matrix3& _rhs)
//	{
//		*this = _rhs.m_values;
//
//		return *this;
//	}
//
//	Matrix3& Matrix3::operator=(const float _rhs[][3])
//	{
//		// Copy double array
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				m_values[row][column] = _rhs[row][column];
//			}
//		}
//
//		return *this;
//	}
//
//	Matrix3& Matrix3::operator=(const float _rhs[9])
//	{
//		int		arrayIndex = 0;
//
//		// Copy 1D array
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column, ++arrayIndex)
//			{
//				m_values[row][column] = _rhs[arrayIndex];
//			}
//		}
//
//		return *this;
//	}
//
//
//
//	Matrix3 Matrix3::operator+(const Matrix3& _rhs) const
//	{
//		Matrix3		result;
//
//		// Add all components
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				result.m_values[row][column] =
//				m_values[row][column] + _rhs[row][column];
//			}
//		}
//
//		return result;
//	}
//
//	Matrix3 Matrix3::operator-(const Matrix3& _rhs) const
//	{
//		Matrix3		result;
//
//		// Subtract all components
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				result.m_values[row][column] =
//				m_values[row][column] - _rhs[row][column];
//			}
//		}
//
//		return result;
//	}
//
//	Matrix3 Matrix3::operator*(const Matrix3& _rhs) const
//	{
//		Matrix3		result;
//
//		// Go through *this object's rows
//		for (int thisRow = 0; thisRow < 3; thisRow++)
//		{
//			// Go through rhs object's rows
//			for (int rightColumn = 0; rightColumn < 3; rightColumn++)
//			{
//				// Row * column accumulator
//				float	currentNum = 0.f;
//
//				// Go through rhs's columns
//				for (int rightRow = 0; rightRow < 3; rightRow++)
//				{
//					currentNum += m_values[thisRow][rightRow] *
//					_rhs[rightRow][rightColumn];
//				}
//
//				result.m_values[thisRow][rightColumn] = currentNum;
//			}
//		}
//
//		return result;
//	}
//
//
//	Matrix3 Matrix3::operator*(float _rhs) const
//	{
//		Matrix3		result;
//
//		// Multiply all components by scalar
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				result[row][column] = m_values[row][column] * _rhs;
//			}
//		}
//
//		return result;
//	}
//
//
//	Vector3<float>  Matrix3::operator*(const Vector3<float>& _rhs) const
//	{
//		Vector3<float>		result(0.f);
//		float				num;
//
//		// Multiply vector by *this object
//		for (int row = 0; row < 3; ++row)
//		{
//			// Accumulator
//			num = 0.f;
//
//			for (int column = 0; column < 3; ++column)
//			{
//				num += m_values[row][column] * _rhs[column];
//			}
//
//			result[row] = num;
//		}
//
//		return result;
//	}
//
//
//
//	Matrix3 Matrix3::operator/(float _rhs) const
//	{
//		// Multiply by one over divisor
//		return *this * (1.f / _rhs);
//	}
//
//
//
//	Matrix3& ion::math::Matrix3::operator+=(const Matrix3& _rhs)
//	{
//		// Add and assign
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				m_values[row][column] += _rhs[row][column];
//			}
//		}
//
//		return *this;
//	}
//
//
//	Matrix3& ion::math::Matrix3::operator-=(const Matrix3& _rhs)
//	{
//		//Subtract and assign
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				m_values[row][column] -= _rhs[row][column];
//			}
//		}
//
//		return *this;
//	}
//
//
//	Matrix3& Matrix3::operator*=(const Matrix3& _rhs)
//	{
//		Matrix3		result;
//
//		// Go through *this object's rows
//		for (int thisRow = 0; thisRow < 3; thisRow++)
//		{
//			// Go through rhs object's rows
//			for (int rightColumn = 0; rightColumn < 3; rightColumn++)
//			{
//				float	currentNum = 0.f;
//
//				// Go through rhs object's column
//				for (int rightRow = 0; rightRow < 3; rightRow++)
//				{
//					currentNum += m_values[thisRow][rightRow] *
//					_rhs[rightRow][rightColumn];
//				}
//
//				// Store result
//				result.m_values[thisRow][rightColumn] = currentNum;
//			}
//		}
//
//		// Assign result to *this
//		*this = result;
//
//		return *this;
//	}
//
//
//	Matrix3& Matrix3::operator*=(float _rhs)
//	{
//		// Multiply by scalar
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				 m_values[row][column] *= _rhs;
//			}
//		}
//
//		return *this;
//	}
//
//	Matrix3& Matrix3::operator/=(float _rhs)
//	{
//		// Multiply by one over divisor
//		*this *= (1.f / _rhs);
//
//		return *this;
//	}
//
//
//	bool Matrix3::operator==(const Matrix3& _rhs) const
//	{
//		// Check all components for equality
//		for (int row = 0; row < 3; ++row)
//		{
//			for (int column = 0; column < 3; ++column)
//			{
//				if (!ion::math::AlmostEqual(m_values[row][column],
//					_rhs.m_values[row][column]))
//				{
//					return false;
//				}
//			}
//		}
//
//		return true;
//	}
//
//
//	bool Matrix3::operator!=(const Matrix3& _rhs) const
//	{
//		// Return opposite of equality
//		return !(*this == _rhs);
//	}
//
//
//	float* ion::math::Matrix3::operator[](int _index)
//	{
//		// Return row
//		return m_values[_index];
//	}
//
//
//
//	float const* Matrix3::operator[](int _index) const
//	{
//		// Return row
//		return m_values[_index];
//	}
//
//}