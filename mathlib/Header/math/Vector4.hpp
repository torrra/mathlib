#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"
#include "Vector3.hpp"

namespace math
{
	template <CScalarType TValueType>
	using Vector4 = Vector<4, TValueType>;

	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int32_t>;
}

#endif