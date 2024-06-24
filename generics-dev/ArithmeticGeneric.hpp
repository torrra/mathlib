/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: ArithmeticGenerics.h

DESCTIPTION: Basic arithmetic function template. Implementation below

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types
CIntegralType only accepts integral numeric types

*/

#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <cmath>

#include "MathGeneric.hpp"

namespace ion::math
{
    // Epsilon test
    template <CScalarType TValueType>
    bool             AlmostEqual(TValueType _a, TValueType _b, TValueType _epsilon = TValueType(1e-3));

    // Round to the nearest integral value
    template <CScalarType TValueType>
    
    TValueType       Round(TValueType _val);

    // Round to the nearest integral value (greater or equal)
    template <CScalarType TValueType>
    TValueType       Ceil(TValueType _val);

    // Round to the nearest integral value (smaller or equal)
    template <CScalarType TValueType>
    TValueType       Floor(TValueType _val);

    // Wrap value around a set of limits
    template <CScalarType TValueType>
    TValueType       Wrap(TValueType _val, TValueType _low, TValueType _high);

    // Get value within a range without wrapping
    template <CScalarType TValueType>
    TValueType       Clamp(TValueType _val, TValueType _low, TValueType _high);

    template <CScalarType TValueType>
    TValueType       Pow(TValueType _val, unsigned int _power);


    template <CScalarType TValueType>
    TValueType       SquareRoot(TValueType _val);  //TODO: Re-implement

    // Get smallest value
    template <CScalarType TValueType>
    TValueType       Min(TValueType _a, TValueType _b);

    // Get largest value
    template <CScalarType TValueType>
    TValueType       Max(TValueType _a, TValueType _b);

    // Absolute value
    template <CScalarType TValueType>
    TValueType       Absolute(TValueType _val);


    // Get factorial of an unsigned integral value
    template <CIntegralType TValueType>
    TValueType      Factorial(TValueType _val);


    template <CScalarType TValueType>
    TValueType      Modulo(TValueType _toDivide, TValueType _divisor);




// ---- Implementation ----

#pragma region Implementation

    template <CScalarType TValueType>
    TValueType Absolute(TValueType _val)
    {
        // Multiply by -1 if negative
        return (_val < static_cast<TValueType>(0)) ? -_val : _val;
    }


    template <CScalarType TValueType>
    bool  AlmostEqual(TValueType _a, TValueType _b, TValueType _epsilon)
    {
        // Check if difference is smaller than epsilon
        return Absolute(_a - _b) <= _epsilon;
    }

    template <CScalarType TValueType>
    TValueType Modulo(TValueType _toDivide, TValueType _divisor)
    {
        // Integral modulo, flaoting point types
        // are handled below
        return _toDivide % _divisor;
    }

#pragma region Modulo specializations

    template<>
    double Modulo<double>(double _toDivide, double _divisor)
    {
        return fmod(_toDivide, _divisor);
    }

    template <>
    float Modulo<float>(float _toDivide, float _divisor)
    {
        return fmodf(_toDivide, _divisor);
    }

    template<>
    long double Modulo<long double>(long double _toDivide, long double _divisor)
    {
        return fmodl(_toDivide, _divisor);
    }

#pragma endregion Modulo specializations


    template <CScalarType TValueType>
    TValueType Floor(TValueType _val)
    {
        // Integral types do not need to be manipulated
        // floatig point cases handled below
        return _val;
    }


#pragma region Floor specialization

 
    template <>
    float Floor(float _val)
    {
        return static_cast<float>
        (
            static_cast<int32_t>(_val)
        );
    }


    template <>
    double Floor(double _val)
    {
        return static_cast<double>
        (
            static_cast<int64_t>(_val)
        );
    }


    template <>
    long double Floor(long double _val)
    {
        return static_cast<long double>
        (
            static_cast<int64_t>(_val)
        );
    }

#pragma endregion Floor specialization

#pragma endregion Implementations
}


#endif
