#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <cmath>
#include <limits>

#include "MathGeneric.hpp"

namespace math
{

    // Absolute value
    template <CScalarType TValueType> inline
    TValueType       Absolute(TValueType val)                          noexcept;


    // Epsilon test
    template <CScalarType TValueType> inline
    bool             AlmostEqual
    (
        TValueType a, TValueType b,
        TValueType epsilon = static_cast<TValueType>(1e-4)
    )                                                                   noexcept;


    // Round to the nearest integral value
    template <CScalarType TValueType> inline
    TValueType       Round(TValueType val)                             noexcept;


    // Round to the nearest integral value (greater or equal)
    template <CScalarType TValueType> inline
    TValueType       Ceil(TValueType val)                              noexcept;



    // Round to the nearest integral value (smaller or equal)
    template <CScalarType TValueType> inline
    TValueType       Floor(TValueType val)                             noexcept;


    // Wrap value around a set of limits
    template <CScalarType TValueType> inline
    TValueType       Wrap
    (
        TValueType val, TValueType low, TValueType high
    )                                                                   noexcept;

    // Get value within a range without wrapping
    template <CScalarType TValueType> inline
    TValueType       Clamp
    (
        TValueType val, TValueType low, TValueType high
    )                                                                   noexcept;


    // Raise number to an integral power
    template <CScalarType TValueType, CUnsignedType TPowerType> inline
    TValueType       Pow(TValueType val, TPowerType power)            noexcept;


    //TODO: Re-implement our own function
    template <CScalarType TValueType> inline
    TValueType       SquareRoot(TValueType val)                        noexcept;

    // Get smallest value
    template <CScalarType TValueType> inline
    TValueType       Min(TValueType a, TValueType b)                  noexcept;

    // Get largest value
    template <CScalarType TValueType> inline
    TValueType       Max(TValueType a, TValueType b)                  noexcept;



    // Get factorial of an unsigned integral value
    template <CIntegralType TValueType> inline
    TValueType      Factorial(TValueType val)                          noexcept;


    template <CScalarType TValueType> inline
    TValueType      Modulus(TValueType toDivide, TValueType divisor)  noexcept;





// ---- Implementation ----



    template <CScalarType TValueType> inline
    TValueType Absolute(TValueType val) noexcept
    {
        // Unsigned types cannot be negative
        if constexpr (std::is_unsigned<TValueType>::value)
            return val;

        else
            // Multiply by -1 if negative
            return (val < static_cast<TValueType>(0)) ? -val : val;
    }


    template <CScalarType TValueType> inline
    bool  AlmostEqual(TValueType a, TValueType b, TValueType epsilon) noexcept
    {
        // Cannot use negative differences with unsigned types,
        // ensure difference will be positive
        if constexpr (std::is_unsigned<TValueType>::value)
        {
            return Max(a, b) - Min(a, b) <= epsilon;
        }

        // Check if difference is smaller than epsilon
        else
            return Absolute(a - b) <= epsilon;
    }

    template <CScalarType TValueType> inline
    TValueType Modulus(TValueType toDivide, TValueType divisor) noexcept
    {
        // Integral modulo, floating point types
        // are handled below
        return toDivide % divisor;
    }


// ---- Modulus specializations ----

    template<> inline
    double Modulus<double>(double toDivide, double divisor) noexcept
    {
        return fmod(toDivide, divisor);
    }

    template <> inline
    float Modulus<float>(float toDivide, float divisor) noexcept
    {
        return fmodf(toDivide, divisor);
    }

    template<> inline
    long double Modulus<long double>(long double toDivide, long double divisor) noexcept
    {
        return fmodl(toDivide, divisor);
    }


// !Modulus specializations


    template <CScalarType TValueType> inline
    TValueType Floor(TValueType val) noexcept
    {
        // Integral types do not need to be manipulated.
        // Floating point cases handled below
        return val;
    }


// ---- Floor specializations ----

    // Strip down decimal part and match size if possible

    template <> inline
    float Floor(float val) noexcept
    {
        return static_cast<float>
        (
            static_cast<int32_t>(val)
        );
    }


    template <> inline
    double Floor(double val) noexcept
    {
        return static_cast<double>
        (
            static_cast<int64_t>(val)
        );
    }


    template <> inline
    long double Floor(long double val) noexcept
    {
        return static_cast<long double>
        (
            // No standard 128 bit integer
            // available, so resort to 64
            static_cast<int64_t>(val)
        );
    }

// !Floor specializations


    template <CScalarType TValueType> inline
    TValueType Round(TValueType val) noexcept
    {
        return val;
    }


// ---- Round specializations ----

    template <> inline
    float Round(float val) noexcept
    {

        float      floored = Floor<float>(val);

        // Round up if decimal part >= .5
        if (val - floored >= 0.5f)
            return floored + 1.f;

        // Round down if not
        else
            return floored;

    }


    template <> inline
    double Round(double val) noexcept
    {

        double      floored = Floor<double>(val);

        // Round up if decimal part >= .5
        if (val - floored >= 0.5)
            return floored + 1.0;

        // Round down if not
        else
            return floored;

    }

    template <> inline
    long double Round(long double val) noexcept
    {

        long double      floored = Floor<long double>(val);

        // Round up if decimal part >= .5
        if (val - floored >= 0.5l)
            return floored + 1.0l;

        // Round down if not
        else
            return floored;

    }


// !Round specializations

    template <CScalarType TValueType> inline
    TValueType Ceil(TValueType val) noexcept
    {
        // No need to round integral values.
        // Floating point types handled below
        return val;
    }

// ---- Ceil specializations ----

    template <> inline
    float Ceil(float val) noexcept
    {
        float      floored = Floor<float>(val);

        if (AlmostEqual<float>(val, floored))
            return floored;


        // Round up if any decimal part > 0 is found
        else
            return floored + static_cast<float>(1);
    }


    template <> inline
    double Ceil(double val) noexcept
    {
        double      floored = Floor<double>(val);

        if (AlmostEqual<double>(val, floored))
            return floored;


        // Round up if any decimal part > 0 is found
        else
            return floored + static_cast<double>(1);
    }


    template <> inline
    long double Ceil(long double val) noexcept
    {
        long double      floored = Floor<long double>(val);

        if (AlmostEqual<long double>(val, floored))
            return floored;


        // Round up if any decimal part > 0 is found
        else
            return floored + static_cast<long double>(1);
    }


// !Ceil specializations


   // Get value within a range without wrapping
   template <CScalarType TValueType> inline
   TValueType Clamp(TValueType val, TValueType low, TValueType high) noexcept
   {
       // Return highest of low values
       if (val < low)
           return low;

       // Return lowest of high values
       if (val > high)
           return high;

       return val;
   }



   template <CScalarType TValueType> inline
   TValueType Wrap(TValueType val, TValueType low, TValueType high) noexcept
   {
       if (-val > high)
           val = high + Modulus(val - high, low - high);

       else
           val = low + Modulus(val - low, high - low);

       if (val < low)
           val += high;

       return val;
   }



   template <CScalarType TValueType, CUnsignedType TPowerType> inline
   TValueType Pow(TValueType val, TPowerType power) noexcept
   {
       if (static_cast<TPowerType>(0) == power)
           return static_cast<TValueType>(1);

       if (static_cast<TPowerType>(1) == power)
           return val;


       TValueType       valCopy = val;

       // Multiply value by itself power times
       for (TPowerType iteration = static_cast<TPowerType>(1); iteration < power; ++iteration)
           val *= valCopy;

       return val;
   }



   template <CScalarType TValueType> inline
   TValueType SquareRoot(TValueType val) noexcept
   {
       return static_cast<TValueType>
       (
           sqrt(static_cast<double>(val))
       );
   }



   // ---- SquareRoot specializations ----

   template<> inline
   float SquareRoot<float>(float val) noexcept
   {
       return sqrtf(val);
   }


   template<> inline
   long double SquareRoot<long double>(long double val) noexcept
   {
       return sqrtl(val);
   }



   // !SquareRoot specializations



   template <CScalarType TValueType> inline
   TValueType Min(TValueType a, TValueType b) noexcept
   {
       // Return smallest
       return (a < b) ? a : b;
   }


   template <CScalarType TValueType> inline
   TValueType Max(TValueType a, TValueType b) noexcept
   {
       // Return largest
       return (a > b) ? a : b;
   }


   template <CIntegralType TValueType> inline
   TValueType Factorial(TValueType val) noexcept
   {
       TValueType       zero = static_cast<TValueType>(0),
                        one = static_cast<TValueType>(1);


       if (zero == val || one == val)
           return one;

       if (static_cast<TValueType>(2) == val)
           return val;

       TValueType     result = Absolute(val),
           valCopy = result - one;


       // Multiply val by numbers smaller than itself going all the way down to 1
       while (valCopy > zero)
           result *= valCopy--;

       // Restore negative sign if type permits it and value is < 0
       if constexpr (!std::is_unsigned<TValueType>::value)
           result *= (val < static_cast<TValueType>(0)) ? -one : one;

       return result;
   }

// !Implementation
}

namespace LibMath = math;
namespace lm = LibMath;

#endif

