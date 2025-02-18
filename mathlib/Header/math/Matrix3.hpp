#ifndef __MATRIX3_H__
#define __MATRIX3_H__


#include "MathGeneric.hpp"
#include "MatrixGeneric.hpp"

#include "Vector3.hpp"
#include "Matrix2.hpp"

namespace math
{
    template <CScalarType TValueType>
	class Matrix<3, TValueType>
	{
    private:
        using TMatrixType = Matrix<3, TValueType>;
        using TColumnType = Vector3<TValueType>;

    public:


        // Constructors / destructor

    inline                   Matrix(void) = default;
    inline                   Matrix(const TValueType diag);
    inline                   Matrix(const TValueType vals[][3]);
    inline                   Matrix(const TValueType vals[]);
    inline                   Matrix(const TMatrixType& other);

    inline                   ~Matrix(void) = default;

        // Get this matrix' determinant
    inline    TValueType      Determinant(void)                   const;

        // Turn this matrix into an identity matrix with a given diagonal
    inline    void            Identity( TValueType diag =
                                        static_cast<TValueType>(1)
                                       );

        // Get this matrix' transposed cofactor matrix
    inline   TMatrixType         Adjugate(void)                      const;

        // Get a matrix of all 2x2 submatrices' determinants within
        // this matrix
    inline   TMatrixType         Minor(void)                         const;

        // Get a matrix of this matrix' cofactors taken from all 2x2
        // matrices within it
    inline   TMatrixType         Cofactor(void)                      const;

        // Get inverse of this matrix
    inline   TMatrixType         Inverse(void)                       const;

        // Get a transposed copy of this matrix
    inline   TMatrixType         Transpose(void)                     const;

        // Get this matrix stripped of a row and a column
    inline
    Matrix2<TValueType>  SubMatrix(int row, int column)    const;

    inline   TMatrixType&        operator=(const TMatrixType& rhs);
    inline   TMatrixType&        operator=(const TValueType rhs[][3]);
    inline   TMatrixType&        operator=(const TValueType rhs[9]);

        // Matrix / matrix operators

    inline   TMatrixType         operator+(const TMatrixType& rhs)      const;
    inline   TMatrixType         operator-(const TMatrixType& rhs)      const;
    inline   TMatrixType         operator*(const TMatrixType& rhs)      const;

    inline    Vector3<TValueType>
    operator*(const Vector3<TValueType>& rhs)                      const;

        // Multiply all numbers of a copy of this matrix by a scalar factor
    inline   TMatrixType         operator*(TValueType factor)         const;

        // Divide all numbers of a copy of this matrix by a scalar factor
    inline  TMatrixType         operator/(TValueType factor)          const;

        // Matrix / matrix assignment operators

     inline   TMatrixType&        operator+=(const TMatrixType& rhs);
     inline   TMatrixType&        operator-=(const TMatrixType& rhs);
     inline   TMatrixType&        operator*=(const TMatrixType& rhs);

        // Multiply all numbers of a copy of this matrix by a scalar factor
    inline   TMatrixType&        operator*=(TValueType factor);

        // Divide all numbers of a copy of this matrix by a scalar factor
    inline   TMatrixType&        operator/=(TValueType factor);

    inline    bool            operator==(const TMatrixType& rhs)     const;
    inline    bool            operator!=(const TMatrixType& rhs)     const;

        // Access a row (no bound checking)
    inline    TColumnType&   operator[](int index);

        // Access a row (no bound checking)
    inline    TColumnType    operator[](int index)                const;


    private:

        TColumnType       m_values[3];

    };











    // ---- Implementation ----




    template <CScalarType TValueType> inline
 Matrix<3, TValueType>::Matrix(const TValueType diag)
 {
 	Identity(diag);
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType>::Matrix(const TValueType vals[][3])
 {
 	// Copy 3x3 array into matix
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			m_values[row][column] = vals[row][column];
 		}
 	}
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType>::Matrix(const TValueType vals[])
 {
 	int		arrayIndex = 0;


 	// Copy 1D array into matrix
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column, ++arrayIndex)
 		{
 			m_values[row][column] = vals[arrayIndex];
 		}
 	}
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType>::Matrix(const Matrix<3, TValueType>& other)
 {
 	int		maxSize = 3;

 	// Copy other matrix into this matrix
 	for (int row = 0; row < maxSize; ++row)
 	{
 		for (int column = 0; column < maxSize; ++column)
 		{
 			m_values[row][column] = other[row][column];
 		}
 	}
 }



 template <CScalarType TValueType> inline
 TValueType Matrix<3, TValueType>::Determinant(void) const
 {
 	// Add multiplied left-right diagonals together
 	TValueType		positiveDiags
 	{
 		m_values[0][0] * m_values[1][1] * m_values[2][2] +
 		m_values[0][1] * m_values[1][2] * m_values[2][0] +
 		m_values[0][2] * m_values[1][0] * m_values[2][1]
 	};

 	// Add multiplied right-left diagonals together
 	TValueType		negativeDiags
 	{
 		m_values[0][2] * m_values[1][1] * m_values[2][0] +
 		m_values[0][1] * m_values[1][0] * m_values[2][2] +
 		m_values[0][0] * m_values[1][2] * m_values[2][1]
 	};

 	// Subtract negative diagonals from positive diagnonals
 	return positiveDiags - negativeDiags;
 }


 template <CScalarType TValueType> inline
 void Matrix<3, TValueType>::Identity(TValueType diag)
 {
 	int		maxSize = 3;

 	// Zero-out matrix except for diagonal
 	for (int row = 0; row < maxSize; ++row)
 	{
 		for (int column = 0; column < maxSize; ++column)
 		{
 			m_values[row][column] = (row == column) ? diag : 0.f;
 		}
 	}
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::Adjugate(void) const
 {
 	Matrix<3, TValueType>			result;

 	TValueType			sign = 1;

 	// Avoid call to transpose by running one nested loop
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			// Compute minor and transpose (row and column switched)
 			result[column][row] = SubMatrix(row, column)
 								  .Determinant();

 			// Minor to cofactor (multiply by sign)
 			result[column][row] *= sign;

 			// Flip sign (instead of calling pow(-1, row + colum))
 			sign *= -1;
 		}
 	}

 	return result;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::Minor(void) const
 {
 	Matrix<3, TValueType>		result;

 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			// Minor = stripped matrix' determinant
 			result[row][column] = SubMatrix(row, column)
 								  .Determinant();
 		}
 	}

 	return result;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::Cofactor(void) const
 {
 	Matrix<3, TValueType>			result;

 	TValueType			sign = 1;

 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			// Compute minor
 			result[row][column] = SubMatrix(row, column)
 								 .Determinant();

 			// Minot to cofactor
 			result[row][column] *= sign;

 			sign *= -1;
 		}
 	}

 	return result;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::Inverse(void) const
 {
 	// Perform only one division
 	TValueType			invDeterminant = 1.f / Determinant();
 	Matrix<3, TValueType>			result;
 	TValueType			sign = 1;

 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			// Compute minor and transpose
 			result[column][row] = SubMatrix(row, column)
 								  .Determinant();

 			// Minor to cofactor
 			result[column][row] *= sign;

 			// Cofactor to inverse
 			result[column][row] *= invDeterminant;

 			// Flip next sign
 			sign *= -1;
 		}
 	}

 	return result;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::Transpose(void) const
 {
 	Matrix<3, TValueType>		result;

 	// Assign opposite row-colum combination for each value
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			result[row][column] = m_values[column][row];
 		}
 	}

 	return result;

 }



 template <CScalarType TValueType> inline
 Matrix2<TValueType> Matrix<3, TValueType>::SubMatrix(int row, int column) const
 {
 	Matrix2<TValueType>		minor;

 	// Go through matrix and ignore row argument
 	for (int thisRow = 0, mat2Row = 0; thisRow < 3; ++thisRow)
 	{
 		if (row == thisRow)
 			continue;

 		for (int thisColumn = 0, mat2Column = 0; thisColumn < 3; ++thisColumn)
 		{
 			// Ignore column parameter
 			if (column == thisColumn)
 				continue;

 			minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
 		}

 		++mat2Row;
 	}

 	// Get stripped 2x2 matrix
 	return minor;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator=(const Matrix<3, TValueType>& rhs)
 {
     for (uint8_t row = 0; row < 3; ++row)
         m_values[row] = rhs.m_values[row];

 	return *this;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator=(const TValueType rhs[][3])
 {
 	// Copy double array
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			m_values[row][column] = rhs[row][column];
 		}
 	}

 	return *this;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator=(const TValueType rhs[9])
 {
 	int		arrayIndex = 0;

 	// Copy 1D array
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column, ++arrayIndex)
 		{
 			m_values[row][column] = rhs[arrayIndex];
 		}
 	}

 	return *this;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::operator+(const Matrix<3, TValueType>& rhs) const
 {
 	Matrix<3, TValueType>		result;

 	// Add all components
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			result.m_values[row][column] =
 			m_values[row][column] + rhs[row][column];
 		}
 	}

 	return result;
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::operator-(const Matrix<3, TValueType>& rhs) const
 {
 	Matrix<3, TValueType>		result;

 	// Subtract all components
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			result.m_values[row][column] =
 			m_values[row][column] - rhs[row][column];
 		}
 	}

 	return result;
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::operator*(const Matrix<3, TValueType>& rhs) const
 {
 	Matrix<3, TValueType>		result;

 	// Go through *this object's rows
 	for (int thisRow = 0; thisRow < 3; thisRow++)
 	{
 		// Go through rhs object's rows
 		for (int rightColumn = 0; rightColumn < 3; rightColumn++)
 		{
 			// Row * column accumulator
 			TValueType	currentNum = 0.f;

 			// Go through rhs's columns
 			for (int rightRow = 0; rightRow < 3; rightRow++)
 			{
 				currentNum += m_values[rightRow][thisRow] *
 				rhs[rightColumn][rightRow];
 			}

 			result.m_values[rightColumn][thisRow] = currentNum;
 		}
 	}

 	return result;
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::operator*(TValueType rhs) const
 {
 	Matrix<3, TValueType>		result;

 	// Multiply all components by scalar
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			result[row][column] = m_values[row][column] * rhs;
 		}
 	}

 	return result;
 }


 template <CScalarType TValueType> inline
 Vector3<TValueType>  Matrix<3, TValueType>::operator*(const Vector3<TValueType>& rhs) const
 {
 	Vector3<TValueType>		result(0.f);
 	TValueType				num;

 	// Multiply vector by *this object
 	for (int row = 0; row < 3; ++row)
 	{
 		// Accumulator
 		num = 0.f;

 		for (int column = 0; column < 3; ++column)
 		{
 			num += m_values[row][column] * rhs[column];
 		}

 		result[row] = num;
 	}

 	return result;
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType> Matrix<3, TValueType>::operator/(TValueType rhs) const
 {
 	// Multiply by one over divisor
 	return *this * (1.f / rhs);
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator+=(const Matrix<3, TValueType>& rhs)
 {
 	// Add and assign
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			m_values[row][column] += rhs[row][column];
 		}
 	}

 	return *this;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator-=(const Matrix<3, TValueType>& rhs)
 {
 	//Subtract and assign
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			m_values[row][column] -= rhs[row][column];
 		}
 	}

 	return *this;
 }



 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator*=(const Matrix<3, TValueType>& rhs)
 {
 	Matrix<3, TValueType>		result;

 	// Go through *this object's rows
 	for (int thisRow = 0; thisRow < 3; thisRow++)
 	{
 		// Go through rhs object's rows
 		for (int rightColumn = 0; rightColumn < 3; rightColumn++)
 		{
 			TValueType	currentNum = 0.f;

 			// Go through rhs object's column
 			for (int rightRow = 0; rightRow < 3; rightRow++)
 			{
 				currentNum += m_values[thisRow][rightRow] *
 				rhs[rightRow][rightColumn];
 			}

 			// Store result
 			result.m_values[thisRow][rightColumn] = currentNum;
 		}
 	}

 	// Assign result to *this
 	*this = result;

 	return *this;
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator*=(TValueType rhs)
 {
 	// Multiply by scalar
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			 m_values[row][column] *= rhs;
 		}
 	}

 	return *this;
 }


 template <CScalarType TValueType> inline
 Matrix<3, TValueType>& Matrix<3, TValueType>::operator/=(TValueType rhs)
 {
 	// Multiply by one over divisor
 	*this *= (1.f / rhs);

 	return *this;
 }



 template <CScalarType TValueType> inline
 bool Matrix<3, TValueType>::operator==(const Matrix<3, TValueType>& rhs) const
 {
 	// Check all components for equality
 	for (int row = 0; row < 3; ++row)
 	{
 		for (int column = 0; column < 3; ++column)
 		{
 			if (!math::AlmostEqual(m_values[row][column],
 				rhs.m_values[row][column]))
 			{
 				return false;
 			}
 		}
 	}

 	return true;
 }



 template <CScalarType TValueType> inline
 bool Matrix<3, TValueType>::operator!=(const Matrix<3, TValueType>& rhs) const
 {
 	// Return opposite of equality
 	return !(*this == rhs);
 }


 template <CScalarType TValueType> inline
 Vector3<TValueType>&    Matrix<3, TValueType>::operator[](int index)
 {
 	// Return row
 	return m_values[index];
 }


 template <CScalarType TValueType> inline
 Vector3<TValueType>  Matrix<3, TValueType>::operator[](int index) const
 {
 	// Return row
 	return m_values[index];
 }






}

namespace lm = math;
namespace LibMath = math;

#endif