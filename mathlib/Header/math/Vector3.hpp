#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <string>
#include <cmath>
#include <sstream>

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"

#include "Trigonometry.hpp"
#include "Arithmetic.hpp"
#include "Angle.hpp"
#include "Vector2.hpp"
//#include "VectorQuatOperations.hpp"



namespace math
{

    template <CScalarType TValueType>
    using Vector3 = Vector<3, TValueType>;

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    using Vector3i = Vector3<int32_t>;

}

#endif