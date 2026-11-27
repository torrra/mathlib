#ifndef __VECTOR_QUAT_OPERATIONS_H__
#define __VECTOR_QUAT_OPERATIONS_H__

namespace math::internal
{

	template<CScalarType TValueType>
	::math::Vector<3, TValueType> QuatRotate(const::math::Vector<3, TValueType>& vec,
		Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
	{
		return ::math::Quaternion<TValueType>(angleX, angleY, angleZ).Rotate(vec);
	}

}


#endif
