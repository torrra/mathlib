#include "libmath/Matrix3.h"
#include "libmath/Matrix2.h"

#include "libmath/Arithmetic.h"

namespace mth
{
	Matrix3::Matrix3(const float _diag)
	{
		Identity(_diag);
	}

	Matrix3::Matrix3(const float _vals[][3])
	{
		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				m_values[row][column] = _vals[row][column];
			}
		}
	}

	Matrix3::Matrix3(const float _vals[])
	{
		int		arrayIndex = 0;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column, ++arrayIndex)
			{
				m_values[row][column] = _vals[arrayIndex];
			}
		}
	}


	Matrix3::Matrix3(const Matrix3& _other)
	{
		int		maxSize = 3;

		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = _other[row][column];
			}
		}
	}

	float Matrix3::Determinant(void) const
	{
		float		positiveDiags
		{
			m_values[0][0] * m_values[1][1] * m_values[2][2] +
			m_values[0][1] * m_values[1][2] * m_values[2][0] +
			m_values[0][2] * m_values[1][0] * m_values[2][1]
		};

		float		negativeDiags
		{
			m_values[0][2] * m_values[1][1] * m_values[2][0] +
			m_values[0][1] * m_values[1][0] * m_values[2][2] +
			m_values[0][0] * m_values[1][2] * m_values[2][1]
		};

		return positiveDiags - negativeDiags;
	}

	void Matrix3::Identity(float _diag)
	{
		int		maxSize = 3;

		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = (row == column) ? _diag : 0.f;
			}
		}
	}


	Matrix3 Matrix3::Adjugate(void) const
	{
		Matrix3			result;

		float			minusOne = -1;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result[column][row] = SubMatrix(row, column).Determinant();

				result[column][row] *= Pow(minusOne, row + column);
			}
		}

		return result;
	}



	Matrix3 Matrix3::Minor(void) const
	{
		Matrix3		result;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result[row][column] = SubMatrix(row, column).Determinant();
			}
		}

		return result;
	}


	Matrix3 Matrix3::Cofactor(void) const
	{
		Matrix3			result;

		float			minusOne = -1;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result[row][column] = SubMatrix(row, column).Determinant();

				result[row][column] *= Pow(minusOne, row + column);
			}
		}

		return result;
	}

	Matrix3 Matrix3::Inverse(void) const
	{
		float			invDeterminant = 1.f / Determinant();
		Matrix3			result;
		float			minusOne = -1;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result[column][row] = SubMatrix(row, column).Determinant();

				result[column][row] *= Pow(minusOne, row + column);
				result[column][row] *= invDeterminant;

			}
		}

		return result;
	}


	Matrix3 Matrix3::Transpose(void) const
	{
		Matrix3 result;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result[row][column] = m_values[column][row];
			}
		}

		return result;

	}



	Matrix2 Matrix3::SubMatrix(int _row, int _column) const
	{
		Matrix2 minor;

		for (int thisRow = 0, mat2Row = 0; thisRow < 3; ++thisRow)
		{
			if (_row == thisRow)
				continue;

			for (int thisColumn = 0, mat2Column = 0; thisColumn < 3; ++thisColumn)
			{
				if (_column == thisColumn)
					continue;

				minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
			}

			++mat2Row;
		}

		return minor;
	}


	Matrix3& Matrix3::operator=(const Matrix3& _rhs)
	{
		*this = _rhs.m_values;

		return *this;
	}

	Matrix3& Matrix3::operator=(const float _rhs[][3])
	{
		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				m_values[row][column] = _rhs[row][column];
			}
		}

		return *this;
	}

	Matrix3& Matrix3::operator=(const float _rhs[9])
	{
		int		arrayIndex = 0;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column, ++arrayIndex)
			{
				m_values[row][column] = _rhs[arrayIndex];
			}
		}

		return *this;
	}



	Matrix3 Matrix3::operator+(const Matrix3& _rhs) const
	{
		Matrix3		result;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result.m_values[row][column] = m_values[row][column] + _rhs[row][column];
			}
		}

		return result;
	}

	Matrix3 Matrix3::operator-(const Matrix3& _rhs) const
	{
		Matrix3 result;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result.m_values[row][column] = m_values[row][column] - _rhs[row][column];
			}
		}

		return result;
	}

	Matrix3 Matrix3::operator*(const Matrix3& _rhs) const
	{
		Matrix3		result;

		for (int thisRow = 0; thisRow < 3; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 3; rightColumn++)
			{
				float	currentNum = 0.f;

				for (int rightRow = 0; rightRow < 3; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * _rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		return result;
	}


	Matrix3 Matrix3::operator*(float _rhs) const
	{
		Matrix3		result;

		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				result[row][column] = m_values[row][column] * _rhs;
			}
		}

		return result;
	}

	Matrix3 Matrix3::operator/(float _rhs) const
	{
		return *this * (1.f / _rhs);
	}



	Matrix3& mth::Matrix3::operator+=(const Matrix3& _rhs)
	{
		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				m_values[row][column] += _rhs[row][column];
			}
		}

		return *this;
	}


	Matrix3& mth::Matrix3::operator-=(const Matrix3& _rhs)
	{
		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				m_values[row][column] -= _rhs[row][column];
			}
		}

		return *this;
	}


	Matrix3& Matrix3::operator*=(const Matrix3& _rhs)
	{
		Matrix3		result;

		for (int thisRow = 0; thisRow < 3; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 3; rightColumn++)
			{
				float	currentNum = 0.f;

				for (int rightRow = 0; rightRow < 3; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * _rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		*this = result;

		return *this;
	}


	Matrix3& Matrix3::operator*=(float _rhs)
	{
		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				 m_values[row][column] *= _rhs;
			}
		}

		return *this;
	}

	Matrix3& Matrix3::operator/=(float _rhs)
	{
		*this *= (1.f / _rhs);

		return *this;
	}


	bool Matrix3::operator==(const Matrix3& _rhs) const
	{
		for (int row = 0; row < 3; ++row)
		{
			for (int column = 0; column < 3; ++column)
			{
				if (!mth::AlmostEqual(m_values[row][column],
					_rhs.m_values[row][column]))
					return false;
			}
		}

		return true;
	}


	bool Matrix3::operator!=(const Matrix3& _rhs) const
	{
		return !(*this == _rhs);
	}


	float* mth::Matrix3::operator[](int _index)
	{
		return m_values[_index];
	}



	float const* Matrix3::operator[](int _index) const
	{
		return m_values[_index];
	}

}