#include "libmath/Matrix4.h"
#include "libmath/Matrix3.h"

#include "libmath/Arithmetic.h"

namespace ion::math
{
	Matrix4::Matrix4(const float _diag)
	{
		Identity(_diag);
	}

	Matrix4::Matrix4(const float _vals[][4])
	{
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

		float		result = 0.f, minusOne = -1.f;
		int			stripedRow = 0;

		for (int cofactor = 0; cofactor < 4; ++cofactor)
		{
			minor = SubMatrix(stripedRow, cofactor);
			result += m_values[stripedRow][cofactor] * minor.Determinant() * Pow(minusOne, cofactor);

		}

		return result;

	}

	void Matrix4::Identity(float _diag)
	{
		int		maxSize = 4;

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

		float			minusOne = -1;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[column][row] = SubMatrix(row, column).Determinant();

				result[column][row] *= Pow(minusOne, row + column);
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
				result[row][column] = SubMatrix(row, column).Determinant();
			}
		}

		return result;
	}


	Matrix4 Matrix4::Cofactor(void) const
	{
		Matrix4			result;

		float			minusOne = -1;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = SubMatrix(row, column).Determinant();

				result[row][column] *= Pow(minusOne, row + column);
			}
		}

		return result;
	}

	Matrix4 Matrix4::Inverse(void) const
	{
		float			invDeterminant = 1.f / Determinant();
		Matrix4			result;
		float			minusOne = -1;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[column][row] = SubMatrix(row, column).Determinant();

				result[column][row] *= Pow(minusOne, row + column);
				result[column][row] *= invDeterminant;

			}
		}

		return result;
	}


	Matrix4 Matrix4::Transpose(void) const
	{
		Matrix4 result;

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
		Matrix3 minor;

		for (int thisRow = 0, mat2Row = 0; thisRow < 4; ++thisRow)
		{
			if (_row == thisRow)
				continue;

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

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] = m_values[row][column] + _rhs[row][column];
			}
		}

		return result;
	}

	Matrix4 Matrix4::operator-(const Matrix4& _rhs) const
	{
		Matrix4 result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] = m_values[row][column] - _rhs[row][column];
			}
		}

		return result;
	}

	Matrix4 Matrix4::operator*(const Matrix4& _rhs) const
	{
		Matrix4		result;

		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				float	currentNum = 0.f;

				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * _rhs[rightRow][rightColumn];
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

		for (int row = 0; row < 4; ++row)
		{
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
		return *this * (1.f / _rhs);
	}



	Matrix4& ion::math::Matrix4::operator+=(const Matrix4& _rhs)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] += _rhs[row][column];
			}
		}

		return *this;
	}


	Matrix4& ion::math::Matrix4::operator-=(const Matrix4& _rhs)
	{
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

		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				float	currentNum = 0.f;

				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * _rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		*this = result;

		return *this;
	}


	Matrix4& Matrix4::operator*=(float _rhs)
	{
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
		*this *= (1.f / _rhs);

		return *this;
	}


	bool Matrix4::operator==(const Matrix4& _rhs) const
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				if (!ion::math::AlmostEqual(m_values[row][column],
					_rhs.m_values[row][column]))
					return false;
			}
		}

		return true;
	}


	bool Matrix4::operator!=(const Matrix4& _rhs) const
	{
		return !(*this == _rhs);
	}


	float* ion::math::Matrix4::operator[](int _index)
	{
		return m_values[_index];
	}



	float const* Matrix4::operator[](int _index) const
	{
		return m_values[_index];
	}

}