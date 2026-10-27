#ifndef __MATRIX_GENERIC_H__
#define __MATRIX_GENERIC_H__

#include <inttypes.h>

#include "MathGeneric.hpp"



namespace math
{
    template <DimensionType TDimensions = 4, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
    class Matrix
	{
	private:

		using TRowType = Vector<TDimensions, TValueType>;

	public:

		// Constructors / destructor

		inline					Matrix(void) = default;
		inline					Matrix(const TValueType diag);
		inline					Matrix(const TValueType vals[][TDimensions]);
		inline					Matrix(const TValueType vals[]);
		inline					Matrix(const Matrix& other);

		template <DimensionType TOtherMatrixSize = TDimensions - 1>
		explicit				Matrix(const Matrix<TOtherMatrixSize, TValueType>& other);

		inline					~Matrix(void) = default;

		// Get this matrix' determinant
		inline	TValueType           Determinant(void)                   const;

		// Turn this matrix into an identity matrix with a given diagonal
		inline	void            Identity(TValueType diag = static_cast<TValueType>(1));

		// Get this matrix' transposed cofactor matrix
		inline	Matrix         Adjugate(void)                      const;

		// Get a matrix of all 3x3 submatrices' determinants within
		// this matrix
		inline	Matrix         Minor(void)                         const;

		// Get a matrix of this matrix' cofactors taken from all 3x3
		// matrices within it
		inline	Matrix         Cofactor(void)                      const;

		// Get inverse of this matrix
		inline	Matrix         Inverse(void)                       const;

		// Get a transposed copy of this matrix
		inline	Matrix         Transpose(void)                     const;

		// Get this matrix stripped of a row and a column
		// sub-matrix size cannot be greater than origin matrix size - 1
		template <DimensionType TOtherMatrixSize = TDimensions - 1> requires IsSmallerThan<TDimensions - 1, TOtherMatrixSize>::value
		inline	Matrix<TOtherMatrixSize, TValueType>  SubMatrix(DimensionType row, DimensionType column)    const;

		// Change the position to a matrix
		static inline Matrix<4, TValueType>	PositionMatrix(const Vector3<TValueType>& position);

		// Change the scale to a matrix
		static inline Matrix<4, TValueType>	ScaleMatrix(const Vector3<TValueType>& scale);


		// Get rotation matrix from three angles (column-major)
		static inline Matrix<4, TValueType>	 RotationMatrix(
			Radian<TValueType> angleX,
			Radian<TValueType> angleY,
			Radian<TValueType> angle
		);


		// Get rotation matrix from three angles stored in a vector (column-major)
		static inline Matrix<4, TValueType> RotationMatrix(Vector3<TValueType> angles);

		inline	Matrix& operator=(const Matrix& rhs);
		inline	Matrix& operator=(const TValueType rhs[][TDimensions]);
		inline	Matrix& operator=(const TValueType rhs[]);


		// Matrix / matrix operators

		inline	Matrix         operator+(const Matrix& rhs)      const;
		inline	Matrix         operator-(const Matrix& rhs)      const;
		inline	Matrix         operator*(const Matrix& rhs)      const;

		// Multiply a vector TDimensionsD by this matrix
		inline	Vector<TDimensions, TValueType>				operator*(const Vector<TDimensions, TValueType>& rhs)      const;


		// Multiply all numbers of a copy of this matrix by a scalar factor
		inline	Matrix         operator*(TValueType factor)            const;

		// Divide all numbers of a copy of this matrix by a scalar factor
		inline	Matrix         operator/(TValueType factor)            const;


		// Matrix / matrix assignment operators


		inline	Matrix& operator+=(const Matrix& rhs);
		inline	Matrix& operator-=(const Matrix& rhs);
		inline	Matrix& operator*=(const Matrix& rhs);

		// Multiply all numbers of a copy of this matrix by a scalar factor
		inline	Matrix& operator*=(TValueType factor);

		// Divide all numbers of a copy of this matrix by a scalar factor
		inline	Matrix& operator/=(TValueType factor);

		inline	bool				operator==(const Matrix& rhs)     const;
		inline	bool				operator!=(const Matrix& rhs)     const;

		// Access a row (no bound checking)
		inline	TRowType& operator[](int index);

		// Access a row (no bound checking)
		inline	TRowType		operator[](int index)              const;

		template <DimensionType TOtherMatrixSize = TDimensions - 1>
		operator Matrix<TOtherMatrixSize, TValueType>(void)		const;


	private:

		template <DimensionType TOtherMatrixSize>  inline
		void InitializeFromDifferentSizedArg(const Matrix<TOtherMatrixSize, TValueType>& other);

		TRowType       m_values[TDimensions];

	};


	// ---- Implementations ----

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>::Matrix(const TValueType diag)
	{
		Identity(diag);
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>::Matrix(const TValueType vals[][TDimensions])
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				m_values[row][column] = vals[row][column];
			}
		}
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>::Matrix(const TValueType vals[])
	{
		DimensionType		arrayIndex = 0;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column, ++arrayIndex)
			{
				m_values[row][column] = vals[arrayIndex];
			}
		}
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>::Matrix(const Matrix<TDimensions, TValueType>& other)
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				m_values[row][column] = other[row][column];
			}
		}
	}

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
	template <DimensionType TOtherMatrixSize>  inline
	inline Matrix<TDimensions, TValueType>::Matrix(const Matrix<TOtherMatrixSize, TValueType>& other)
	{
		InitializeFromDifferentSizedArg(other);
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
	TValueType Matrix<TDimensions, TValueType>::Determinant(void) const
	{
		if constexpr (TDimensions == 2)
		{
			return (m_values[0][0] * m_values[1][1]) -
				(m_values[0][1] * m_values[1][0]);
		}

		else if constexpr (TDimensions == 3)
		{
			// Add multiplied left-right diagonals together
			TValueType		positiveDiags
			(
				m_values[0][0] * m_values[1][1] * m_values[2][2] +
				m_values[0][1] * m_values[1][2] * m_values[2][0] +
				m_values[0][2] * m_values[1][0] * m_values[2][1]
			);

			// Add multiplied right-left diagonals together
			TValueType		negativeDiags
			(
				m_values[0][2] * m_values[1][1] * m_values[2][0] +
				m_values[0][1] * m_values[1][0] * m_values[2][2] +
				m_values[0][0] * m_values[1][2] * m_values[2][1]
			);

			// Subtract negative diagonals from positive diagnonals
			return positiveDiags - negativeDiags;
		}

		else
		{
			Matrix<TDimensions - 1, TValueType>     minor;

			TValueType		result = static_cast<TValueType>(0), minusOne = static_cast<TValueType>(-1);
			DimensionType	stripedRow = 0;

			for (DimensionType cofactor = 0; cofactor < TDimensions; ++cofactor)
			{
				minor = SubMatrix<TDimensions - 1>(stripedRow, cofactor);
				result += m_values[stripedRow][cofactor] * minor.Determinant() * Pow(minusOne, cofactor);

			}

			return result;
		}

	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		void Matrix<TDimensions, TValueType>::Identity(TValueType diag)
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				m_values[row][column] = (row == column) ? diag : static_cast<TValueType>(0);
			}
		}
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Adjugate(void) const
	{
		// can't create an unsigned adjugate matrix
		if constexpr (std::is_unsigned<TValueType>::value)
			return *this;

		else if constexpr (TDimensions == 2)
		{
			// Transpose cofactors
			return Matrix<2, TValueType>(m_values[1][1], -m_values[0][1],
				-m_values[1][0], m_values[0][0]);
		}

		else
		{
			Matrix<TDimensions, TValueType>			result;

			TValueType			minusOne = -1;

			for (DimensionType row = 0; row < TDimensions; ++row)
			{
				for (DimensionType column = 0; column < TDimensions; ++column)
				{
					result[column][row] = SubMatrix(row, column).Determinant();

					//result[column][row] *= Pow(minusOne, row + column);

					result[row][column] *= minusOne;
					minusOne *= static_cast<TValueType>(-1);
				}
			}

			return result;
		}

	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Minor(void) const
	{
		Matrix<TDimensions, TValueType>		result;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				result[row][column] = SubMatrix(row, column).Determinant();
			}
		}

		return result;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Cofactor(void) const
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			return *this;

		else
		{
			Matrix<TDimensions, TValueType>			result;

			TValueType			minusOne = -1;

			for (DimensionType row = 0; row < TDimensions; ++row)
			{
				for (DimensionType column = 0; column < TDimensions; ++column)
				{
					result[row][column] = SubMatrix(row, column).Determinant();

					//result[row][column] *= Pow(minusOne, row + column);

					result[row][column] *= minusOne;
					minusOne *= static_cast<TValueType>(-1);
				}
			}

			return result;
		}

	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Inverse(void) const
	{
		// can't create unsigned inverse matirix
		if constexpr (std::is_unsigned<TValueType>::value)
			return *this;

		else
		{
			TValueType						invDeterminant = static_cast<TValueType>(1) / Determinant();
			Matrix<TDimensions, TValueType>			result;
			TValueType						minusOne = -1;

			for (DimensionType row = 0; row < TDimensions; ++row)
			{
				for (DimensionType column = 0; column < TDimensions; ++column)
				{
					result[column][row] = SubMatrix(row, column).Determinant();

					result[column][row] *= Pow(minusOne, row + column);
					result[column][row] *= invDeterminant;

				}
			}

			return result;
		}

	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::Transpose(void) const
	{
		Matrix<TDimensions, TValueType> result;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				result[row][column] = m_values[column][row];
			}
		}

		return result;

	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
	template <DimensionType TOtherMatrixSize> requires IsSmallerThan<TDimensions - 1, TOtherMatrixSize>::value
	Matrix<TOtherMatrixSize, TValueType> Matrix<TDimensions, TValueType>::SubMatrix(DimensionType row, DimensionType column) const
	{
		Matrix<TOtherMatrixSize, TValueType> minor;

		for (DimensionType thisRow = 0, mat2Row = 0; thisRow < TDimensions; ++thisRow)
		{
			if (row == thisRow)
				continue;

			for (DimensionType thisColumn = 0, mat2Column = 0; thisColumn < TDimensions; ++thisColumn)
			{
				if (column == thisColumn)
					continue;

				minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
			}

			++mat2Row;
		}

		return minor;
	}

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
	inline Matrix<4, TValueType>
	Matrix<TDimensions, TValueType>::PositionMatrix(const Vector3<TValueType>& position)
	{
		Matrix<4, TValueType> positionMatrix;

		positionMatrix.Identity();

		positionMatrix[3][0] = position.GetX();
		positionMatrix[3][1] = position.GetY();
		positionMatrix[3][2] = position.GetZ();

		return positionMatrix;
	}

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
	inline Matrix <4, TValueType>
    Matrix<TDimensions, TValueType>::ScaleMatrix(const Vector3<TValueType>& scale)
	{
		Matrix scaleMatrix;

		scaleMatrix.Identity();

		scaleMatrix[0][0] = scale.GetX();
		scaleMatrix[1][1] = scale.GetY();
		scaleMatrix[2][2] = scale.GetZ();

		return scaleMatrix;
	}

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
	inline Matrix <4, TValueType> Matrix<TDimensions, TValueType>::RotationMatrix(
		Radian<TValueType> angleX,
		Radian<TValueType> angleY,
		Radian<TValueType> angleZ
	)
	{
		if constexpr (std::is_unsigned<TValueType>::value)
			return Matrix<TDimensions, TValueType>();

		else
		{
			TValueType				cosYaw = Cos(angleZ), sinYaw = Sin(angleZ);
			TValueType				cosPitch = Cos(angleX), sinPitch = Sin(angleX);
			TValueType				cosRoll = Cos(angleY), sinRoll = Sin(angleY);

			Matrix				rotationMatrix;

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

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
	inline Matrix <4, TValueType>
	Matrix<TDimensions, TValueType>::RotationMatrix(Vector3<TValueType> angles)
	{
		Radian<TValueType>		angleX(angles.X()),
			angleY(angles.Y()),
			angleZ(angles.Z());

		return RotationMatrix(angleX, angleY, angleZ);
	}



	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator=(const Matrix<TDimensions, TValueType>& rhs)
	{
		for (uint8_t row = 0; row < TDimensions; ++row)
			this->m_values[row] = rhs.m_values[row];

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator=(const TValueType rhs[][TDimensions])
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				m_values[row][column] = rhs[row][column];
			}
		}

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator=(const TValueType rhs[16])
	{
		DimensionType		arrayIndex = 0;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column, ++arrayIndex)
			{
				m_values[row][column] = rhs[arrayIndex];
			}
		}

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator+(const Matrix<TDimensions, TValueType>& rhs) const
	{
		Matrix<TDimensions, TValueType>		result;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				result.m_values[row][column] = m_values[row][column] + rhs[row][column];
			}
		}

		return result;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator-(const Matrix<TDimensions, TValueType>& rhs) const
	{
		Matrix<TDimensions, TValueType> result;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				result.m_values[row][column] = m_values[row][column] - rhs[row][column];
			}
		}

		return result;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator*(const Matrix<TDimensions, TValueType>& rhs) const
	{
		Matrix<TDimensions, TValueType>		result;

		for (int thisRow = 0; thisRow < TDimensions; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < TDimensions; rightColumn++)
			{
				TValueType	currentNum = static_cast<TValueType>(0);

				for (int rightRow = 0; rightRow < TDimensions; rightRow++)
				{
					currentNum += m_values[rightRow][thisRow] * rhs[rightColumn][rightRow];
				}

				result.m_values[rightColumn][thisRow] = currentNum;
			}
		}

		return result;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Vector<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator*(const Vector<TDimensions, TValueType>& rhs) const
	{
		Vector<TDimensions, TValueType>		result;
		TValueType				num;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			num = static_cast<TValueType>(0);

			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				num += m_values[row][column] * rhs[column];
			}

			result[row] = num;
		}

		return result;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator*(TValueType rhs) const
	{
		Matrix<TDimensions, TValueType>		result;

		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				result[row][column] = m_values[row][column] * rhs;
			}
		}

		return result;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator/(TValueType rhs) const
	{
		return *this * (static_cast<TValueType>(1) / rhs);
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& math::Matrix<TDimensions, TValueType>::operator+=(const Matrix<TDimensions, TValueType>& rhs)
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				m_values[row][column] += rhs[row][column];
			}
		}

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& math::Matrix<TDimensions, TValueType>::operator-=(const Matrix<TDimensions, TValueType>& rhs)
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				m_values[row][column] -= rhs[row][column];
			}
		}

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator*=(const Matrix<TDimensions, TValueType>& rhs)
	{
		Matrix<TDimensions, TValueType>		result;

		for (int thisRow = 0; thisRow < TDimensions; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < TDimensions; rightColumn++)
			{
				TValueType	currentNum = static_cast<TValueType>(0);

				for (int rightRow = 0; rightRow < TDimensions; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		*this = result;

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator*=(TValueType rhs)
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				m_values[row][column] *= rhs;
			}
		}

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Matrix<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator/=(TValueType rhs)
	{
		*this *= (static_cast<TValueType>(1) / rhs);

		return *this;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		bool Matrix<TDimensions, TValueType>::operator==(const Matrix<TDimensions, TValueType>& rhs) const
	{
		for (DimensionType row = 0; row < TDimensions; ++row)
		{
			for (DimensionType column = 0; column < TDimensions; ++column)
			{
				if (!math::AlmostEqual(m_values[row][column],
					rhs.m_values[row][column]))
					return false;
			}
		}

		return true;
	}

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		bool Matrix<TDimensions, TValueType>::operator!=(const Matrix<TDimensions, TValueType>& rhs) const
	{
		return !(*this == rhs);
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Vector<TDimensions, TValueType>& Matrix<TDimensions, TValueType>::operator[](int index)
	{
		return m_values[index];
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value inline
		Vector<TDimensions, TValueType> Matrix<TDimensions, TValueType>::operator[](int index) const
	{
		return m_values[index];
	}

	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value 
	template <DimensionType TOtherMatrixSize> inline
	Matrix<TDimensions, TValueType>::operator Matrix<TOtherMatrixSize, TValueType>(void) const
	{
		Matrix<TOtherMatrixSize, TValueType> otherMatrix;

		otherMatrix.InitializeFromDifferentSizedArg(*this);
		return otherMatrix;
	}


	template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThan<1, TDimensions>::value
	template <DimensionType TOtherMatrixSize>  inline
	void Matrix<TDimensions, TValueType>::InitializeFromDifferentSizedArg(const Matrix<TOtherMatrixSize, TValueType>& other)
	{
		constexpr DimensionType maxSize = (TDimensions < TOtherMatrixSize) ? TDimensions : TOtherMatrixSize;

		for (DimensionType row = 0; row < maxSize; ++row)
		{
			for (DimensionType column = 0; column < max; ++column)
			{
				m_values[row][column] = other[row][column];
			}
		}

		// Fill the rest of the matrix with 0 (and 1 in the diagonal)
		// if this is bigger than the copied matrix
		if constexpr (TOtherMatrixSize < TDimensions)
		{
			for (DimensionType row = TOtherMatrixSize; row < TDimensions; ++row)
			{
				for (DimensionType column = 0; column < TDimensions; ++column)
				{
					if (row == column)
						m_values[row][column] = static_cast<TValueType>(1);

					else
						m_values[row][column] = static_cast<TValueType>(0);
				}
			}
		}
	}



    template <CScalarType TValueType>
    using Matrix2 = Matrix<2, TValueType>;

    using Matrix2f = Matrix2<float>;
    using Matrix2d = Matrix2<double>;
    using Matrix2i = Matrix2<int32_t>;


    template <CScalarType TValueType>
    using Matrix3 = Matrix<3, TValueType>;

    using Matrix3f = Matrix3<float>;
    using Matrix3d = Matrix3<double>;
    using Matrix3i = Matrix3<int32_t>;



    template <CScalarType TValueType>
    using Matrix4 = Matrix<4, TValueType>;

    using MatrixTDimensionsf = Matrix4<float>;
    using MatrixTDimensionsd = Matrix4<double>;
    using MatrixTDimensionsi = Matrix4<int32_t>;

}

#endif