#ifndef __MATRIX2_H__
#define __MATRIX2_H__

#include "MatrixGeneric.hpp"

namespace math
{
    VECTOR_MATRIX_DEFS(Matrix, 2);

#ifdef DEFINE_MAT_EXTENDED
    VECTOR_MATRIX_EXTENDED(Matrix, 2);
#endif // DEFINE_MAT_EXTENDED

#ifdef DEFINE_MAT_FIXED
    VECTOR_MATRIX_FIXED(Vector, 2);
#endif // DEFINE_MAT_FIXED
}

#endif