#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"

namespace math
{
    VECTOR_MATRIX_DEFS(Vector, 4);

#ifdef DEFINE_VEC_EXTENDED
    VECTOR_MATRIX_EXTENDED(Vector, 4);
#endif // DEFINE_VEC_EXTENDED

#ifdef DEFINE_VEC_FIXED
    VECTOR_MATRIX_FIXED(Vector, 4);
#endif // DEFINE_VEC_FIXED
}

#endif