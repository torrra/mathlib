#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "MathGeneric.hpp"
#include "MatrixGeneric.hpp"

#include "Matrix3.hpp"
#include "Vector4.hpp"
#include "Vector3.hpp"

namespace math
{
	template <CScalarType TValueType>
	class Matrix<4, TValueType>
	{
	private:

		using TMatrixType = Matrix<4, TValueType>;
		using TRowType = Vector<4, TValueType>;

	public:

		// Constructors / destructor

	inline					Matrix(void) = default;
	inline					Matrix(const TValueType diag);
	inline					Matrix(const TValueType vals[][4]);
	inline					Matrix(const TValueType vals[]);
	inline					Matrix(const Matrix<4, TValueType>& other);

	explicit				Matrix(const Matrix3<TValueType>& mat3);

	inline					~Matrix(void) = default;

		// Get this matrix' determinant
	inline	TValueType           Determinant(void)                   const;

		// Turn this matrix into an identity matrix with a given diagonal
	inline	void            Identity(TValueType diag = static_cast<TValueType>(1));

		// Get this matrix' transposed cofactor matrix
	inline	TMatrixType         Adjugate(void)                      const;

		// Get a matrix of all 3x3 submatrices' determinants within
		// this matrix
	inline	TMatrixType         Minor(void)                         const;

		// Get a matrix of this matrix' cofactors taken from all 3x3
		// matrices within it
	inline	TMatrixType         Cofactor(void)                      const;

		// Get inverse of this matrix
	inline	TMatrixType         Inverse(void)                       const;

		// Get a transposed copy of this matrix
	inline	TMatrixType         Transpose(void)                     const;

		// Get this matrix stripped of a row and a column
	inline	Matrix3<TValueType>         SubMatrix(int row, int column)    const;

		// Change the position to a matrix
	static inline Matrix4<TValueType>	PositionMatrix(Vector3<TValueType>& position);	

		// Change the scale to a matrix
	static inline Matrix4<TValueType>	ScaleMatrix(Vector3<TValueType>& scale);


	// Get rotation matrix from three angles (column-major)
	static inline TMatrixType			RotationMatrix(
			Radian<TValueType> angleX,
			Radian<TValueType> angleY,
			Radian<TValueType> angle
	);


	// Get rotation matrix from three angles stored in a vector (column-major)
	static inline Matrix4<TValueType> RotationMatrix(Vector3<TValueType> angles);

	inline	TMatrixType&		operator=(const TMatrixType& rhs);
	inline	TMatrixType&		operator=(const TValueType rhs[][4]);
	inline	TMatrixType&		operator=(const TValueType rhs[16]);


		// Matrix / matrix operators

	inline	TMatrixType         operator+(const TMatrixType& rhs)      const;
	inline	TMatrixType         operator-(const TMatrixType& rhs)      const;
	inline	TMatrixType         operator*(const TMatrixType& rhs)      const;

		// Multiply a vector 4D by this matrix
	inline	Vector4<TValueType>				operator*(const Vector4<TValueType>& rhs)      const;


		// Multiply all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType         operator*(TValueType factor)            const;

		// Divide all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType         operator/(TValueType factor)            const;


		// Matrix / matrix assignment operators


	inline	TMatrixType&		operator+=(const TMatrixType& rhs);
	inline	TMatrixType&		operator-=(const TMatrixType& rhs);
	inline	TMatrixType&		operator*=(const TMatrixType& rhs);

		// Multiply all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType&		operator*=(TValueType factor);

		// Divide all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType&		operator/=(TValueType factor);

	inline	bool				operator==(const TMatrixType& rhs)     const;
	inline	bool				operator!=(const TMatrixType& rhs)     const;

		// Access a row (no bound checking)
	inline	TRowType&		operator[](int index);

		// Access a row (no bound checking)
	inline	TRowType		operator[](int index)              const;

	operator Matrix3<TValueType>(void)		const;


	private:

		TRowType       m_values[4];

	};







// ---- Implementations ----

	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const TValueType diag)
	{
		Identity(diag);
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const TValueType vals[][4])
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] = vals[row][column];
			}
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const TValueType vals[])
	{
		int		arrayIndex = 0;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column, ++arrayIndex)
			{
				m_values[row][column] = vals[arrayIndex];
			}
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const Matrix<4, TValueType>& other)
	{
		int		maxSize = 4;

		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = other[row][column];
			}
		}
	}

	template<CScalarType TValueType>
	inline Matrix<4, TValueType>::Matrix(const Matrix3<TValueType>& mat3)
	{
		m_values[0][0] = mat3[0][0];
		m_values[0][1] = mat3[0][1];
		m_values[0][2] = mat3[0][2];
		m_values[0][3] = static_cast<TValueType>(0);

		m_values[1][0] = mat3[1][0];
		m_values[1][1] = mat3[1][1];
		m_values[1][2] = mat3[1][2];
		m_values[1][3] = static_cast<TValueType>(0);

		m_values[2][0] = mat3[2][0];
		m_values[2][1] = mat3[2][1];
		m_values[2][2] = mat3[2][2];
		m_values[2][3] = static_cast<TValueType>(0);

		m_values[3][0] = static_cast<TValueType>(0);
		m_values[3][1] = static_cast<TValueType>(0);
		m_values[3][2] = static_cast<TValueType>(0);
		m_values[3][3] = static_cast<TValueType>(1);
	}


	template <CScalarType TValueType> inline
	TValueType Matrix<4, TValueType>::Determinant(void) const
	{
		Matrix3<TValueType>     minor;

		TValueType		result = static_cast<TValueType>(0), minusOne = static_cast<TValueType>(-1);
		int				stripedRow = 0;

		for (unsigned int cofactor = 0; cofactor < 4; ++cofactor)
		{
			minor = SubMatrix(stripedRow, cofactor);
			result += m_values[stripedRow][cofactor] * minor.Determinant() * Pow(minusOne, cofactor);

		}

		return result;

	}


	template <CScalarType TValueType> inline
	void Matrix<4, TValueType>::Identity(TValueType diag)
	{
		int		maxSize = 4;

		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = (row == column) ? diag : static_cast<TValueType>(0);
			}
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Adjugate(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			throw std::logic_error("Cannot compute unsigned adjugate matrix");

		else
		{
			Matrix<4, TValueType>			result;

			TValueType			minusOne = -1;

			for (unsigned int row = 0; row < 4; ++row)
			{
				for (unsigned int column = 0; column < 4; ++column)
				{
					result[column][row] = SubMatrix(row, column).Determinant();

					result[column][row] *= Pow(minusOne, row + column);
				}
			}

			return result;
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Minor(void) const
	{
		Matrix<4, TValueType>		result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = SubMatrix(row, column).Determinant();
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Cofactor(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			throw std::logic_error("Cannot compute unsigned cofactor matrix");

		else
		{
			Matrix<4, TValueType>			result;

			TValueType			minusOne = -1;

			for (unsigned int row = 0; row < 4; ++row)
			{
				for (unsigned int column = 0; column < 4; ++column)
				{
					result[row][column] = SubMatrix(row, column).Determinant();

					result[row][column] *= Pow(minusOne, row + column);
				}
			}

			return result;
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Inverse(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			throw std::logic_error("Cannot compute unsigned inverse matrix");

		else
		{
			TValueType						invDeterminant = static_cast<TValueType>(1) / Determinant();
			Matrix<4, TValueType>			result;
			TValueType						minusOne = -1;

			for (unsigned int row = 0; row < 4; ++row)
			{
				for (unsigned int column = 0; column < 4; ++column)
				{
					result[column][row] = SubMatrix(row, column).Determinant();

					result[column][row] *= Pow(minusOne, row + column);
					result[column][row] *= invDeterminant;

				}
			}

			return result;
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Transpose(void) const
	{
		Matrix<4, TValueType> result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = m_values[column][row];
			}
		}

		return result;

	}


	template <CScalarType TValueType> inline
	Matrix3<TValueType> Matrix<4, TValueType>::SubMatrix(int row, int column) const
	{
		Matrix3<TValueType> minor;

		for (int thisRow = 0, mat2Row = 0; thisRow < 4; ++thisRow)
		{
			if (row == thisRow)
				continue;

			for (int thisColumn = 0, mat2Column = 0; thisColumn < 4; ++thisColumn)
			{
				if (column == thisColumn)
					continue;

				minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
			}

			++mat2Row;
		}

		return minor;
	}

	template<CScalarType TValueType>
	inline Matrix4<TValueType> 
	Matrix<4, TValueType>::PositionMatrix(Vector3<TValueType>& position)
	{
		TMatrixType positionMatrix;

		positionMatrix.Identity();

		positionMatrix[0][3] = position.X();
		positionMatrix[1][3] = position.Y();
		positionMatrix[2][3] = position.Z();

		return positionMatrix;
	}

	template<CScalarType TValueType>
	inline Matrix <4, TValueType> 
	Matrix<4, TValueType>::ScaleMatrix(Vector3<TValueType>& scale)
	{
		TMatrixType scaleMatrix;

		scaleMatrix.Identity();

		scaleMatrix[0][0] = scale.X();
		scaleMatrix[1][1] = scale.Y();
		scaleMatrix[2][2] = scale.Z();

		return scaleMatrix;
	}

	template<CScalarType TValueType>
	inline Matrix<4, TValueType> Matrix<4, TValueType>::RotationMatrix(
		Radian<TValueType> angleX,
		Radian<TValueType> angleY,
		Radian<TValueType> angleZ
	)
	{
		if constexpr (std::is_unsigned_v<TValueType> || std::is_integral_v<TValueType>)
			throw std::logic_error("Cannot compute unsigned or integral rotation matrix");


		else
		{
			TValueType				cosYaw = Cos(angleZ), sinYaw = Sin(angleZ);
			TValueType				cosPitch = Cos(angleX), sinPitch = Sin(angleX);
			TValueType				cosRoll = Cos(angleY), sinRoll = Sin(angleY);

			TMatrixType				rotationMatrix;

			// Assign COLUMN-MAJOR rotation matrix

			rotationMatrix[0][0] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
			rotationMatrix[0][1] = sinRoll * cosPitch;
			rotationMatrix[0][2] = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
			rotationMatrix[0][3] = static_cast<TValueType>(0);

			rotationMatrix[1][0] = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
			rotationMatrix[1][1] = cosRoll * cosPitch;
			rotationMatrix[1][2] = sinRoll * sinYaw + cosYaw * sinPitch * cosRoll;
			rotationMatrix[1][3] = static_cast<TValueType>(0);

			rotationMatrix[2][0] = sinYaw * cosPitch;
			rotationMatrix[2][1] = -sinPitch;
			rotationMatrix[2][2] = cosYaw * cosPitch;
			rotationMatrix[2][3] = static_cast<TValueType>(0);


			rotationMatrix[3][0] = static_cast<TValueType>(0);
			rotationMatrix[3][1] = static_cast<TValueType>(0);
			rotationMatrix[3][2] = static_cast<TValueType>(0);
			rotationMatrix[3][3] = static_cast<TValueType>(1);

			return rotationMatrix;
		}

	}

	template<CScalarType TValueType>
	inline Matrix4<TValueType>
	Matrix<4, TValueType>::RotationMatrix(Vector3<TValueType> angles)
	{
		Radian<TValueType>		angleX(angles.X()),
								angleY(angles.Y()),
								angleZ(angles.Z());

		return RotationMatrix(angleX, angleY, angleZ);
	}



	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator=(const Matrix<4, TValueType>& rhs)
	{
		for (uint8_t row = 0; row < 4; ++row)
			this->m_values[row] = rhs.m_values[row];

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator=(const TValueType rhs[][4])
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] = rhs[row][column];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator=(const TValueType rhs[16])
	{
		int		arrayIndex = 0;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column, ++arrayIndex)
			{
				m_values[row][column] = rhs[arrayIndex];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator+(const Matrix<4, TValueType>& rhs) const
	{
		Matrix<4, TValueType>		result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] = m_values[row][column] + rhs[row][column];
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator-(const Matrix<4, TValueType>& rhs) const
	{
		Matrix<4, TValueType> result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] = m_values[row][column] - rhs[row][column];
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator*(const Matrix<4, TValueType>& rhs) const
	{
		Matrix<4, TValueType>		result;

		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				TValueType	currentNum = static_cast<TValueType>(0);

				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[rightRow][thisRow] * rhs[rightColumn][rightRow];
				}

				result.m_values[rightColumn][thisRow] = currentNum;
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Matrix<4, TValueType>::operator*(const Vector4<TValueType>& rhs) const
	{
		Vector4<TValueType>		result;
		TValueType				num;

		for (int row = 0; row < 4; ++row)
		{
			num = static_cast<TValueType>(0);

			for (int column = 0; column < 4; ++column)
			{
				num += m_values[row][column] * rhs[column];
			}

			result[row] = num;
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator*(TValueType rhs) const
	{
		Matrix<4, TValueType>		result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = m_values[row][column] * rhs;
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator/(TValueType rhs) const
	{
		return *this * (static_cast<TValueType>(1) / rhs);
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& math::Matrix<4, TValueType>::operator+=(const Matrix<4, TValueType>& rhs)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] += rhs[row][column];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& math::Matrix<4, TValueType>::operator-=(const Matrix<4, TValueType>& rhs)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] -= rhs[row][column];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator*=(const Matrix<4, TValueType>& rhs)
	{
		Matrix<4, TValueType>		result;

		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				TValueType	currentNum = static_cast<TValueType>(0);

				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		*this = result;

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator*=(TValueType rhs)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] *= rhs;
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator/=(TValueType rhs)
	{
		*this *= (static_cast<TValueType>(1) / rhs);

		return *this;
	}


	template <CScalarType TValueType> inline
	bool Matrix<4, TValueType>::operator==(const Matrix<4, TValueType>& rhs) const
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				if (!math::AlmostEqual(m_values[row][column],
					rhs.m_values[row][column]))
					return false;
			}
		}

		return true;
	}

	template <CScalarType TValueType> inline
	bool Matrix<4, TValueType>::operator!=(const Matrix<4, TValueType>& rhs) const
	{
		return !(*this == rhs);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Matrix<4, TValueType>::operator[](int index)
	{
		return m_values[index];
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Matrix<4, TValueType>::operator[](int index) const
	{
		return m_values[index];
	}


	template<CScalarType TValueType>
	inline  Matrix<4, TValueType>::operator Matrix3<TValueType>(void) const
	{
		Matrix3<TValueType> mat3;

		mat3[0][0] = m_values[0][0];
		mat3[0][1] = m_values[0][1];
		mat3[0][2] = m_values[0][2];

		mat3[1][0] = m_values[1][0];
		mat3[1][1] = m_values[1][1];
		mat3[1][2] = m_values[1][2];

		mat3[2][0] = m_values[2][0];
		mat3[2][1] = m_values[2][1];
		mat3[2][2] = m_values[2][2];

		return mat3;
	}

}

namespace lm = math;
namespace LibMath = lm;

#endif