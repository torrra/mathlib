#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <string>
#include <cmath>
#include <sstream>

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"

//#include "VectorQuatOperations.hpp"


namespace math
{

    VECTOR_MATRIX_DEFS(Vector, 3);

#ifdef DEFINE_VEC_EXTENDED
    VECTOR_MATRIX_EXTENDED(Vector, 3);
#endif // DEFINE_VEC_EXTENDED

#ifdef DEFINE_VEC_FIXED
    VECTOR_MATRIX_FIXED(Vector, 3);
#endif // DEFINE_VEC_FIXED
}

#endif