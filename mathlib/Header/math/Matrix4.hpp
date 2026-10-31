#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "MatrixGeneric.hpp"

namespace math
{
    VECTOR_MATRIX_DEFS(Matrix, 4);

#ifdef DEFINE_MAT_EXTENDED
    VECTOR_MATRIX_EXTENDED(Matrix, 4);
#endif // DEFINE_MAT_EXTENDED

#ifdef DEFINE_MAT_FIXED
    VECTOR_MATRIX_FIXED(Vector, 4);
#endif // DEFINE_MAT_FIXED
}

#endif