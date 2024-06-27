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


    template <CScalarType TValueType>
    using Matrix3 = Matrix<3, TValueType>;

    using Matrix3f = Matrix3<float>;
    using Matrix3d = Matrix3<double>;
    using Matrix3i = Matrix3<int32_t>;

}

#endif