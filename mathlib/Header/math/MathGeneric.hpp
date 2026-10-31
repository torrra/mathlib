#ifndef __MATH_GENERICS_H__
#define __MATH_GENERICS_H__

#include <type_traits>
#include <limits>

#define VECTOR_MATRIX_DEFS(baseClass, dimensions)\
template <CScalarType TValueType>\
using baseClass##dimensions = baseClass<dimensions, TValueType>;\
using baseClass##dimensions##f = baseClass##dimensions<float>;\
using baseClass##dimensions##d = baseClass##dimensions<double>;\
using baseClass##dimensions##i = baseClass##dimensions<int>

#define VECTOR_MATRIX_EXTENDED(baseClass, dimensions)\
using baseClass##dimensions##u = baseClass##dimensions<unsigned int>;\
using baseClass##dimensions##l = baseClass##dimensions<long>;\
using baseClass##dimensions##ll = baseClass##dimensions<long long>;\
using baseClass##dimensions##ul = baseClass##dimensions<unsigned long>;\
using baseClass##dimensions##ull = baseClass##dimensions<unsigned long long>;\
using baseClass##dimensions##c = baseClass##dimensions<char>;\
using baseClass##dimensions##uc = baseClass##dimensions<unsigned char>


#define VECTOR_MATRIX_FIXED(baseClass, dimensions)\
using baseClass##dimensions##i8 = baseClass##dimensions<int8_t>;\
using baseClass##dimensions##u8 = baseClass##dimensions<uint8_t>;\
using baseClass##dimensions##i16 = baseClass##dimensions<int16_t>;\
using baseClass##dimensions##u16 = baseClass##dimensions<uint16_t>;\
using baseClass##dimensions##i32 = baseClass##dimensions<int32_t>;\
using baseClass##dimensions##u32 = baseClass##dimensions<uint32_t>;\
using baseClass##dimensions##i64 = baseClass##dimensions<int64_t>;\
using baseClass##dimensions##u64 = baseClass##dimensions<uint64_t>;\

namespace math
{
    using DimensionType = unsigned int;

    template <DimensionType TMinimum, DimensionType TEvaluatedDimension>
    struct IsGreaterThan
    {
        static constexpr bool value = TEvaluatedDimension > TMinimum;
    };

    template <DimensionType TMaximum, DimensionType TEvaluatedDimension>
    struct IsSmallerThan
    {
        static constexpr bool value = TEvaluatedDimension < TMaximum;
    };

    template <DimensionType TEvaluatedDimension>
    struct IsGreaterThanZero
    {
        static constexpr bool value = IsGreaterThan<0, TEvaluatedDimension>::value;
    };


    // Constrain type to a number:
    // int, float, etc... excluding pointers
    template <typename TEvaluatedType>
    concept CScalarType =
    std::is_arithmetic<TEvaluatedType>::value;


    // Constrain type to a built-in integral type
    // int, unsigned int, etc... excluding pointers
    template <typename TEvaluatedType>
    concept CIntegralType =
    std::is_integral<TEvaluatedType>::value;


    // Constrain template to an unsigned integral type
    template <typename TEvaluatedType>
    concept CUnsignedType =
    std::is_unsigned<TEvaluatedType>::value;

    template <typename TEvaluatedType>
    concept CFloatingType =
    std::is_floating_point<TEvaluatedType>::value;


    // Constrain type to a type that can be manipulated through addition,
    // subtraction, and multiplication (between two object of this type).
    // Does NOT account for division. Use CDivisibleObject
    template <typename TEvaluatedType>
    concept CArithmeticType = requires (TEvaluatedType a, TEvaluatedType b)
    {
     // These statements are never actually ran,
     // we just check if they can compile to determine
     // if the evaluated type meets the requirements

      a + b;
      a - b;
      a * b;
    };


    // Constrain type to one that can be added, subtracted, multiplied,
    // AND divided (applies to two objects of the same type)
    template <typename TEvaluatedType>
    concept CDivisibleType = CArithmeticType<TEvaluatedType> &&
    requires (TEvaluatedType a, TEvaluatedType b)
    {
      a / b;
    };


    template <CUnsignedType TEvaluatedType>
    constexpr bool unsignedAdditionOverflow(TEvaluatedType a, TEvaluatedType b)
    {
        return b > std::numeric_limits<TEvaluatedType>::max() - a;
    }

    template <CUnsignedType TEvaluatedType>
    constexpr bool uSubtractionOverflow(TEvaluatedType a, TEvaluatedType b)
    {
        return b < std::numeric_limits<TEvaluatedType>::min() + a;
    }



}

namespace LibMath = math;
namespace lm = LibMath;

#endif