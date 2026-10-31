#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"

namespace math
{

    template <CScalarType TValueType>
    using Vector2 = Vector<2, TValueType>;


    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int32_t>;

}

#endif