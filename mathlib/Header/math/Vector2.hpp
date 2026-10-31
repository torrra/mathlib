#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"

namespace math
{

    VECTOR_MATRIX_DEFS(Vector, 2);

#ifdef DEFINE_VEC_EXTENDED
    VECTOR_MATRIX_EXTENDED(Vector, 2);
#endif // DEFINE_VEC_EXTENDED

#ifdef DEFINE_VEC_FIXED
    VECTOR_MATRIX_FIXED(Vector, 2);
#endif // DEFINE_VEC_FIXED
}

#endif