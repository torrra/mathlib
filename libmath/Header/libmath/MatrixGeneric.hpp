#ifndef __MATRIX_GENERIC_H__
#define __MATRIX_GENERIX_H__

#include <inttypes.h>

#include "libmath/MathGeneric.hpp"
#include "libmath/Vector2.h"
#include "libmath/Vector3.h"
#include "libmath/Vector4.h"


namespace ion::math
{
    template <uint8_t TDimensions, CScalarType TValueType>
    class Matrix;


    template <CScalarType TValueType>
    using Matrix2 = Matrix<2, TValueType>;

    using Matrix2f = Matrix2<float>;
    using Matrix2d = Matrix2<double>;
    using Matrix2i = Matrix2<int32_t>;

    // template <uint8_t TDimensions, CScalarType TValuetype> inline
    // Matrix<TDimensions, TValueType>::Matrix(const TValueType _diag)
	// {
	// 	Identity(_diag);
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>::Matrix(const TValueType _vals[][TDimensions])
	// {
	// 	// Copy TDimensionsxTDimensions array into matix
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			m_values[row][column] = _vals[row][column];
	// 		}
	// 	}
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>::Matrix(const TValueType _vals[])
	// {
	// 	int		arrayIndex = 0;


	// 	// Copy 1D array into matix
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column, ++arrayIndex)
	// 		{
	// 			m_values[row][column] = _vals[arrayIndex];
	// 		}
	// 	}
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>::Matrix(const Matrix<TDimensions, TValueType>& _other)
	// {
	// 	int		maxSize = TDimensions;

	// 	// Copy other matrix into this matrix
	// 	for (int row = 0; row < maxSize; ++row)
	// 	{
	// 		for (int column = 0; column < maxSize; ++column)
	// 		{
	// 			m_values[row][column] = _other[row][column];
	// 		}
	// 	}
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// TValueType Matrix<TDimensions, TValueType>::Determinant(void) const
	// {
	// 	// Add multiplied left-right diagonals together
	// 	TValueType		positiveDiags
	// 	{
	// 		m_values[0][0] * m_values[1][1] * m_values[2][2] +
	// 		m_values[0][1] * m_values[1][2] * m_values[2][0] +
	// 		m_values[0][2] * m_values[1][0] * m_values[2][1]
	// 	};

	// 	// Add multiplied right-left diagonals together
	// 	TValueType		negativeDiags
	// 	{
	// 		m_values[0][2] * m_values[1][1] * m_values[2][0] +
	// 		m_values[0][1] * m_values[1][0] * m_values[2][2] +
	// 		m_values[0][0] * m_values[1][2] * m_values[2][1]
	// 	};

	// 	// Subtract negative diagonals from positive diagnonals
	// 	return positiveDiags - negativeDiags;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// void Matrix<TDimensions, TValueType>::Identity(TValueType _diag)
	// {
	// 	int		maxSize = TDimensions;

	// 	// Zero-out matrix except for diagonal
	// 	for (int row = 0; row < maxSize; ++row)
	// 	{
	// 		for (int column = 0; column < maxSize; ++column)
	// 		{
	// 			m_values[row][column] = (row == column) ? _diag : 0.f;
	// 		}
	// 	}
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Adjugate(void) const
	// {
	// 	Matrix<TDimensions, TValueType>			result;

	// 	TValueType			sign = 1;

	// 	// Avoid call to transpose by running one nested loop
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			// Compute minor and transpose (row and column switched)
	// 			result[column][row] = SubMatrix(row, column)
	// 								  .Determinant();

	// 			// Minor to cofactor (multiply by sign)
	// 			result[column][row] *= sign;

	// 			// Flip sign (instead of calling pow(-1, row + colum))
	// 			sign *= -1;
	// 		}
	// 	}

	// 	return result;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Minor(void) const
	// {
	// 	Matrix<TDimensions, TValueType>		result;

	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			// Minor = stripped matrix' determinant
	// 			result[row][column] = SubMatrix(row, column)
	// 								  .Determinant();
	// 		}
	// 	}

	// 	return result;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Cofactor(void) const
	// {
	// 	Matrix<TDimensions, TValueType>			result;

	// 	TValueType			sign = 1;

	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			// Compute minor
	// 			result[row][column] = SubMatrix(row, column)
	// 								 .Determinant();

	// 			// Minot to cofactor
	// 			result[row][column] *= sign;

	// 			sign *= -1;
	// 		}
	// 	}

	// 	return result;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Inverse(void) const
	// {
	// 	// Perform only one division
	// 	TValueType			invDeterminant = 1.f / Determinant();
	// 	Matrix<TDimensions, TValueType>			result;
	// 	TValueType			sign = 1;

	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			// Compute minor and transpose
	// 			result[column][row] = SubMatrix(row, column)
	// 								  .Determinant();

	// 			// Minor to cofactor
	// 			result[column][row] *= sign;

	// 			// Cofactor to inverse
	// 			result[column][row] *= invDeterminant;

	// 			// Flip next sign
	// 			sign *= -1;
	// 		}
	// 	}

	// 	return result;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Transpose(void) const
	// {
	// 	Matrix<TDimensions, TValueType>		result;

	// 	// Assign opposite row-colum combination for each value
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			result[row][column] = m_values[column][row];
	// 		}
	// 	}

	// 	return result;

	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix2 Matrix<TDimensions, TValueType>::SubMatrix(int _row, int _column) const
	// {
	// 	Matrix2		minor;

	// 	// Go through matrix and ignore row argument
	// 	for (int thisRow = 0, mat2Row = 0; thisRow < TDimensions; ++thisRow)
	// 	{
	// 		if (_row == thisRow)
	// 			continue;

	// 		for (int thisColumn = 0, mat2Column = 0; thisColumn < TDimensions; ++thisColumn)
	// 		{
	// 			// Ignore column parameter
	// 			if (_column == thisColumn)
	// 				continue;

	// 			minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
	// 		}

	// 		++mat2Row;
	// 	}

	// 	// Get stripped 2x2 matrix
	// 	return minor;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator=(const Matrix<TDimensions, TValueType>& _rhs)
	// {
	// 	*this = _rhs.m_values;

	// 	return *this;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator=(const TValueType _rhs[][TDimensions])
	// {
	// 	// Copy double array
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			m_values[row][column] = _rhs[row][column];
	// 		}
	// 	}

	// 	return *this;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator=(const TValueType _rhs[9])
	// {
	// 	int		arrayIndex = 0;

	// 	// Copy 1D array
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column, ++arrayIndex)
	// 		{
	// 			m_values[row][column] = _rhs[arrayIndex];
	// 		}
	// 	}

	// 	return *this;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator+(const Matrix<TDimensions, TValueType>& _rhs) const
	// {
	// 	Matrix<TDimensions, TValueType>		result;

	// 	// Add all components
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			result.m_values[row][column] =
	// 			m_values[row][column] + _rhs[row][column];
	// 		}
	// 	}

	// 	return result;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator-(const Matrix<TDimensions, TValueType>& _rhs) const
	// {
	// 	Matrix<TDimensions, TValueType>		result;

	// 	// Subtract all components
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			result.m_values[row][column] =
	// 			m_values[row][column] - _rhs[row][column];
	// 		}
	// 	}

	// 	return result;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator*(const Matrix<TDimensions, TValueType>& _rhs) const
	// {
	// 	Matrix<TDimensions, TValueType>		result;

	// 	// Go through *this object's rows
	// 	for (int thisRow = 0; thisRow < TDimensions; thisRow++)
	// 	{
	// 		// Go through rhs object's rows
	// 		for (int rightColumn = 0; rightColumn < TDimensions; rightColumn++)
	// 		{
	// 			// Row * column accumulator
	// 			TValueType	currentNum = 0.f;

	// 			// Go through rhs's columns
	// 			for (int rightRow = 0; rightRow < TDimensions; rightRow++)
	// 			{
	// 				currentNum += m_values[thisRow][rightRow] *
	// 				_rhs[rightRow][rightColumn];
	// 			}

	// 			result.m_values[thisRow][rightColumn] = currentNum;
	// 		}
	// 	}

	// 	return result;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator*(TValueType _rhs) const
	// {
	// 	Matrix<TDimensions, TValueType>		result;

	// 	// Multiply all components by scalar
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			result[row][column] = m_values[row][column] * _rhs;
	// 		}
	// 	}

	// 	return result;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// VectorTDimensions<TValueType>  Matrix<TDimensions, TValueType>::operator*(const VectorTDimensions<TValueType>& _rhs) const
	// {
	// 	VectorTDimensions<TValueType>		result(0.f);
	// 	TValueType				num;

	// 	// Multiply vector by *this object
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		// Accumulator
	// 		num = 0.f;

	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			num += m_values[row][column] * _rhs[column];
	// 		}

	// 		result[row] = num;
	// 	}

	// 	return result;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator/(TValueType _rhs) const
	// {
	// 	// Multiply by one over divisor
	// 	return *this * (1.f / _rhs);
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& ion::math::Matrix<TDimensions, TValueType>::operator+=(const Matrix<TDimensions, TValueType>& _rhs)
	// {
	// 	// Add and assign
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			m_values[row][column] += _rhs[row][column];
	// 		}
	// 	}

	// 	return *this;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& ion::math::Matrix<TDimensions, TValueType>::operator-=(const Matrix<TDimensions, TValueType>& _rhs)
	// {
	// 	//Subtract and assign
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			m_values[row][column] -= _rhs[row][column];
	// 		}
	// 	}

	// 	return *this;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator*=(const Matrix<TDimensions, TValueType>& _rhs)
	// {
	// 	Matrix<TDimensions, TValueType>		result;

	// 	// Go through *this object's rows
	// 	for (int thisRow = 0; thisRow < TDimensions; thisRow++)
	// 	{
	// 		// Go through rhs object's rows
	// 		for (int rightColumn = 0; rightColumn < TDimensions; rightColumn++)
	// 		{
	// 			TValueType	currentNum = 0.f;

	// 			// Go through rhs object's column
	// 			for (int rightRow = 0; rightRow < TDimensions; rightRow++)
	// 			{
	// 				currentNum += m_values[thisRow][rightRow] *
	// 				_rhs[rightRow][rightColumn];
	// 			}

	// 			// Store result
	// 			result.m_values[thisRow][rightColumn] = currentNum;
	// 		}
	// 	}

	// 	// Assign result to *this
	// 	*this = result;

	// 	return *this;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator*=(TValueType _rhs)
	// {
	// 	// Multiply by scalar
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			 m_values[row][column] *= _rhs;
	// 		}
	// 	}

	// 	return *this;
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator/=(TValueType _rhs)
	// {
	// 	// Multiply by one over divisor
	// 	*this *= (1.f / _rhs);

	// 	return *this;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// bool Matrix<TDimensions, TValueType>::operator==(const Matrix<TDimensions, TValueType>& _rhs) const
	// {
	// 	// Check all components for equality
	// 	for (int row = 0; row < TDimensions; ++row)
	// 	{
	// 		for (int column = 0; column < TDimensions; ++column)
	// 		{
	// 			if (!ion::math::AlmostEqual(m_values[row][column],
	// 				_rhs.m_values[row][column]))
	// 			{
	// 				return false;
	// 			}
	// 		}
	// 	}

	// 	return true;
	// }



    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// bool Matrix<TDimensions, TValueType>::operator!=(const Matrix<TDimensions, TValueType>& _rhs) const
	// {
	// 	// Return opposite of equality
	// 	return !(*this == _rhs);
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// TValueType* ion::math::Matrix<TDimensions, TValueType>::operator[](int _index)
	// {
	// 	// Return row
	// 	return m_values[_index];
	// }


    // template <uint8_t TDimensions, CScalarType TValuetype> inline
	// TValueType const* Matrix<TDimensions, TValueType>::operator[](int _index) const
	// {
	// 	// Return row
	// 	return m_values[_index];
	// }






}

#endif