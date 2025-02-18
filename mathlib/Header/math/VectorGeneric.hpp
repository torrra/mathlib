#ifndef __VECTOR_GENERIC_H__
#define __VECTOR_GENERIC_H__


#include <inttypes.h>

#include "MathGeneric.hpp"

namespace math
{
    // Generic vector class , TDimentions defines the number of components (x, y, z...)
    // TValueType the type of the data it contains
    template <uint8_t TDimensions, CScalarType TValueType>
	class Vector;

    // Partial Vector specialization for 2D vector
    template <CScalarType TValueType>
    using Vector2 = Vector<2, TValueType>;


    // Vector2 aliases for quick use

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int32_t>;


    // Partial specialization for 3D vector
	template <CScalarType TValueType>
	using Vector3 = Vector<3, TValueType>;


    // Vector3 aliases for quick use

	using Vector3f = Vector3<float>;
	using Vector3i = Vector3<int32_t>;
	using Vector3d = Vector3<double>;


    // Partial specialization for 3D vector
    template <CScalarType TValueType>
    using Vector4 = Vector<4, TValueType>;


    // Vector4 aliases for quick use

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int32_t>;
    using Vector4d = Vector4<double>;

}



#endif