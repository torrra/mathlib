/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: ArithmeticGenerics.hpp

DESCTIPTION: Basic arithmetic function templates. Implementation below

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types
CIntegralType only accepts integral numeric types

*/

#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <cmath>
#include <limits>

#include "IonWarnings.hpp"
#include "MathGeneric.hpp"

namespace ion::math
{
    // Epsilon test
    template <CScalarType TValueType>
    bool             AlmostEqual
    (
        TValueType _a, TValueType _b,

        // Use the type's built-in epsilon if none is provided
        TValueType _epsilon = std::numeric_limits<TValueType>::epsilon()
    )                                                                   noexcept;


    // Round to the nearest integral value
    template <CScalarType TValueType>

    TValueType       Round(TValueType _val)                             noexcept;

    // Round to the nearest integral value (greater or equal)
    template <CScalarType TValueType>
    TValueType       Ceil(TValueType _val)                              noexcept;

    // Round to the nearest integral value (smaller or equal)
    template <CScalarType TValueType>
    TValueType       Floor(TValueType _val)                             noexcept;

    // Wrap value around a set of limits
    template <CScalarType TValueType>
    TValueType       Wrap
    (
        TValueType _val, TValueType _low, TValueType _high
    )                                                                   noexcept;

    // Get value within a range without wrapping
    template <CScalarType TValueType>
    TValueType       Clamp
    (
        TValueType _val, TValueType _low, TValueType _high
    )                                                                   noexcept;

    // Raise number to an integral power
    template <CScalarType TValueType, CUnsignedType TPowerType>
    TValueType       Pow(TValueType _val, TPowerType _power)            noexcept;


    //TODO: Re-implement our own function
    template <CScalarType TValueType>
    TValueType       SquareRoot(TValueType _val)                        noexcept;

    // Get smallest value
    template <CScalarType TValueType>
    TValueType       Min(TValueType _a, TValueType _b)                  noexcept;

    // Get largest value
    template <CScalarType TValueType>
    TValueType       Max(TValueType _a, TValueType _b)                  noexcept;

    // Absolute value
    template <CScalarType TValueType>
    TValueType       Absolute(TValueType _val)                          noexcept;


    // Get factorial of an unsigned integral value
    template <CIntegralType TValueType>
    TValueType      Factorial(TValueType _val)                          noexcept;


    template <CScalarType TValueType>
    TValueType      Modulus(TValueType _toDivide, TValueType _divisor)  noexcept;




// ---- Implementation ----



    template <CScalarType TValueType>
    TValueType Absolute(TValueType _val) noexcept
    {
        // Multiply by -1 if negative
        return (_val < static_cast<TValueType>(0)) ? -_val : _val;
    }


    template <CScalarType TValueType>
    bool  AlmostEqual(TValueType _a, TValueType _b, TValueType _epsilon) noexcept
    {
        // Check if difference is smaller than epsilon
        return Absolute(_a - _b) <= _epsilon;
    }

    template <CScalarType TValueType>
    TValueType Modulus(TValueType _toDivide, TValueType _divisor) noexcept
    {
        // Integral modulo, floating point types
        // are handled below
        return _toDivide % _divisor;
    }


// ---- Modulus specializations ----

    template<>
    double Modulus<double>(double _toDivide, double _divisor) noexcept
    {
        return fmod(_toDivide, _divisor);
    }

    template <>
    float Modulus<float>(float _toDivide, float _divisor) noexcept
    {
        return fmodf(_toDivide, _divisor);
    }

    template<>
    long double Modulus<long double>(long double _toDivide, long double _divisor) noexcept
    {
        return fmodl(_toDivide, _divisor);
    }


// !Modulus specializations


    template <CScalarType TValueType>
    TValueType Floor(TValueType _val) noexcept
    {
        // Integral types do not need to be manipulated
        // floating point cases handled below
        return _val;
    }


// ---- Floor specializations ----

    // Strip down decimal part and match size if possible

    template <>
    float Floor(float _val) noexcept
    {
        return static_cast<float>
        (
            static_cast<int32_t>(_val)
        );
    }


    template <>
    double Floor(double _val) noexcept
    {
        return static_cast<double>
        (
            static_cast<int64_t>(_val)
        );
    }


    template <>
    long double Floor(long double _val) noexcept
    {
        return static_cast<long double>
        (
            // No standard 128 bit integer
            // available, so resort to 64
            static_cast<int64_t>(_val)
        );
    }

// !Floor specializations


#ifdef ION_MSVC_COMPILER

    // Rounding with decimal parts will be unreachable for integral types,
    // which will trigger an MSVC compiler warning.
    // It is actually intended behavior to never reach this part,
    // but this will be properly fixed

    // HACK: disable unreachable warning for rounding functions
    ION_PUSH_WARNINGS()
    ION_DISABLE_WARNING(ION_UNREACHABLE_CODE)

#endif


    template <CScalarType TValueType>
    TValueType Round(TValueType _val) noexcept
    {


        // Integral values do not need to be manipulated.
        // If statement can be constexpr as is_integral will be
        // evaluated in compile time
        if constexpr (std::is_integral<TValueType>::value)
            return _val;


        TValueType      floored = Floor<TValueType>(_val);

        // Round up if decimal part >= .5
        if (_val - floored >= static_cast<TValueType>(0.5))
            return floored + static_cast<TValueType>(1);

        // Round down if not
        else
            return floored;

    }


    template <CScalarType TValueType>
    TValueType Ceil(TValueType _val) noexcept
    {
        // Integral values do not need to be manipulated.
        // If statement can be constexpr as is_integral will be
        // resolved in compile time
        if constexpr (std::is_integral<TValueType>::value)
            return _val;

        TValueType      floored = Floor<TValueType>(_val);

        if(AlmostEqual<TValueType>(_val, floored))
            return floored;


        // Round up if any decimal part > 0 is found
        else
            return floored + static_cast<TValueType>(1);
    }

#ifdef ION_MSVC_COMPILER

    ION_POP_WARNINGS()

#endif



   // Get value within a range without wrapping
   template <CScalarType TValueType>
   TValueType Clamp(TValueType _val, TValueType _low, TValueType _high) noexcept
   {
       // Return highest of low values
       if (_val < _low)
           return _low;

       // Return lowest of high values
       if (_val > _high)
           return _high;

       return _val;
   }



   template <CScalarType TValueType>
   TValueType Wrap(TValueType _val, TValueType _low, TValueType _high)
   {
       if (-_val > _high)
           _val = _high + Modulus(_val - _high, _low - _high);

       else
           _val = _low + Modulus(_val - _low, _high - _low);

       if (_val < _low)
           _val += _high;

       return _val;
   }



   template <CScalarType TValueType, CUnsignedType TPowerType>
   TValueType Pow(TValueType _val, TPowerType _power) noexcept
   {
       if (static_cast<TPowerType>(0) == _power)
           return static_cast<TValueType>(1);

       if (static_cast<TPowerType>(1) == _power)
           return _val;


       TValueType       valCopy = _val;

       // Multiply value by itself _power times
       for (TPowerType iteration = static_cast<TPowerType>(1); iteration < _power; ++iteration)
           _val *= valCopy;

       return _val;
   }



   template <CScalarType TValueType>
   TValueType SquareRoot(TValueType _val) noexcept
   {
       return static_cast<TValueType>
       (
           sqrt(static_cast<double>(_val))
       );
   }



   // ---- SquareRoot specializations ----

   template<>
   float SquareRoot<float>(float _val) noexcept
   {
       return sqrtf(_val);
   }


   template<>
   long double SquareRoot<long double>(long double _val) noexcept
   {
       return sqrtl(_val);
   }



   // !SquareRoot specializations




// !Implementation
}

#endif
