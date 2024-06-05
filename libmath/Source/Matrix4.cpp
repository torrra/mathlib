#include "libmath/Matrix4.h"
#include "libmath/Matrix3.h"

#include "libmath/Arithmetic.h"

namespace mth
{
	Matrix4::Matrix4(const float _diag)
	{
		Identity(_diag);
	}

	Matrix4::Matrix4(const float _vals[][4])
	{
		// Copy 3x3 array into matrix
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] = _vals[row][column];
			}
		}
	}

	Matrix4::Matrix4(const float _vals[])
	{
		int		arrayIndex = 0;

		// Copy 1D array into matrix
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column, ++arrayIndex)
			{
				m_values[row][column] = _vals[arrayIndex];
			}
		}
	}


	Matrix4::Matrix4(const Matrix4& _other)
	{
		int		maxSize = 4;

		// Copy other matrix into this matrix
		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = _other[row][column];
			}
		}
	}

	float Matrix4::Determinant(void) const
	{
		Matrix3     minor;

		float		result = 0.f, sign = 1.f;
		int			stripedRow = 0;

		for (int cofactor = 0; cofactor < 4; ++cofactor)
		{
			// Reduce matrix
			minor = SubMatrix(stripedRow, cofactor);

			// Get its signed determinant
			result += m_values[stripedRow][cofactor] *
					  minor.Determinant() * sign;

			// Flip next sign
			sign *= -1.f;
		}

		return result;

	}

	void Matrix4::Identity(float _diag)
	{
		int		maxSize = 4;

		// Zero out everything except diagonal
		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = (row == column) ? _diag : 0.f;
			}
		}
	}


	Matrix4 Matrix4::Adjugate(void) const
	{
		Matrix4			result;

		float			sign = 1.f;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				// Reduce matrix and get determinant (+ transpose)
				result[column][row] = SubMatrix(row, column).Determinant();

				// Get cofactor
				result[column][row] *= sign;

				sign *= -1.f;
			}
		}

		return result;
	}



	Matrix4 Matrix4::Minor(void) const
	{
		Matrix4		result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				// Reduce matrix and get determinant
				result[row][column] = SubMatrix(row, column).Determinant();
			}
		}

		return result;
	}


	Matrix4 Matrix4::Cofactor(void) const
	{
		Matrix4			result;

		float			sign = 1.f;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				// Reduce matrix and get determinant
				result[row][column] = SubMatrix(row, column).Determinant();

				// Get cofactor
				result[row][column] *= sign;

				// Flip next sign
				sign *= -1.f;
			}
		}

		return result;
	}

	Matrix4 Matrix4::Inverse(void) const
	{
		float			invDeterminant = 1.f / Determinant();
		Matrix4			result;
		float			sign = 1;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[column][row] = SubMatrix(row, column).Determinant();

				// Get cofactir and transpose
				result[column][row] *= sign;

				// divide by determinant
				result[column][row] *= invDeterminant;

				sign *= -1.f;

			}
		}

		return result;
	}


	Matrix4 Matrix4::Transpose(void) const
	{
		Matrix4		result;

		// Swap rows and columns
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = m_values[column][row];
			}
		}

		return result;

	}



	Matrix3 Matrix4::SubMatrix(int _row, int _column) const
	{
		Matrix3		minor;

		// Go through each row and ignore parameter row
		for (int thisRow = 0, mat2Row = 0; thisRow < 4; ++thisRow)
		{
			if (_row == thisRow)
				continue;

			// Go through each column and ignore parameter column
			for (int thisColumn = 0, mat2Column = 0; thisColumn < 4; ++thisColumn)
			{
				if (_column == thisColumn)
					continue;

				minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
			}

			++mat2Row;
		}

		return minor;
	}


	Matrix4& Matrix4::operator=(const Matrix4& _rhs)
	{
		*this = _rhs.m_values;

		return *this;
	}

	Matrix4& Matrix4::operator=(const float _rhs[][4])
	{
		// Copy 2D array
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] = _rhs[row][column];
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator=(const float _rhs[16])
	{
		int		arrayIndex = 0;

		// Copy 1D array
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column, ++arrayIndex)
			{
				m_values[row][column] = _rhs[arrayIndex];
			}
		}

		return *this;
	}


	Matrix4 Matrix4::operator+(const Matrix4& _rhs) const
	{
		Matrix4		result;

		// Add all components
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] =
				m_values[row][column] + _rhs[row][column];
			}
		}

		return result;
	}

	Matrix4 Matrix4::operator-(const Matrix4& _rhs) const
	{
		Matrix4		result;

		// Subtract all components
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] =
				m_values[row][column] - _rhs[row][column];
			}
		}

		return result;
	}

	Matrix4 Matrix4::operator*(const Matrix4& _rhs) const
	{
		Matrix4		result;

		// Go through *this object's rows
		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			// Go through rhs object's rows
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				// Row * column accumulator
				float		currentNum = 0.f;

				// Go through rhs's columns
				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] *
								_rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		return result;
	}

	Vector4 Matrix4::operator*(const Vector4& _rhs) const
	{
		Vector4		result;
		float		num;

		// Multiply vector by *this object
		for (int row = 0; row < 4; ++row)
		{
			// Accumulator
			num = 0.f;

			for (int column = 0; column < 4; ++column)
			{
				num += m_values[row][column] * _rhs[column];
			}

			result[row] = num;
		}

		return result;
	}


	Matrix4 Matrix4::operator*(float _rhs) const
	{
		Matrix4		result;

		// Multiply all components by scalar
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = m_values[row][column] * _rhs;
			}
		}

		return result;
	}

	Matrix4 Matrix4::operator/(float _rhs) const
	{
		// Multiply by one over divisor
		return *this * (1.f / _rhs);
	}



	Matrix4& mth::Matrix4::operator+=(const Matrix4& _rhs)
	{
		// Add and assign
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] += _rhs[row][column];
			}
		}

		return *this;
	}


	Matrix4& mth::Matrix4::operator-=(const Matrix4& _rhs)
	{
		//Subtract and assign
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] -= _rhs[row][column];
			}
		}

		return *this;
	}


	Matrix4& Matrix4::operator*=(const Matrix4& _rhs)
	{
		Matrix4		result;

		// Go through *this object's rows
		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			// Go through rhs object's rows
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				float	currentNum = 0.f;

				// Go through rhs object's column
				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * _rhs[rightRow][rightColumn];
				}

				// Store result
				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		// Assign result to *this
		*this = result;

		return *this;
	}


	Matrix4& Matrix4::operator*=(float _rhs)
	{
		// Multiply by scalar
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] *= _rhs;
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator/=(float _rhs)
	{
		// Multiply by one over divisor
		*this *= (1.f / _rhs);

		return *this;
	}


	bool Matrix4::operator==(const Matrix4& _rhs) const
	{
		// Check all components for equality
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				if (!mth::AlmostEqual(m_values[row][column],
					_rhs.m_values[row][column]))
				{
					return false;
				}
			}
		}

		return true;
	}


	bool Matrix4::operator!=(const Matrix4& _rhs) const
	{
		// Return opposite of equality
		return !(*this == _rhs);
	}


	float* mth::Matrix4::operator[](int _index)
	{
		// Return row
		return m_values[_index];
	}



	float const* Matrix4::operator[](int _index) const
	{
		// Return row
		return m_values[_index];
	}

}