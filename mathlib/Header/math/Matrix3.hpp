#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include "MatrixGeneric.hpp"

namespace math
{
    VECTOR_MATRIX_DEFS(Matrix, 3);

#ifdef DEFINE_MAT_EXTENDED
    VECTOR_MATRIX_EXTENDED(Matrix, 3);
#endif // DEFINE_MAT_EXTENDED

#ifdef DEFINE_MAT_FIXED
    VECTOR_MATRIX_FIXED(Vector, 3);
#endif // DEFINE_MAT_FIXED

}

#endif