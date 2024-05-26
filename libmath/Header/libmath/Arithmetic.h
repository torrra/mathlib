#pragma once

namespace mth
{
    // Epsilon test
    bool        AlmostEqual(float _a, float _b, float _epsilon = 0.0001f);

    // Round to the nearest integral value
    float       Round(float _val);

    // Round to the nearest integral value (greater or equal)
    float       Ceil(float _val);

    // Round to the nearest integral value (smaller or equal)
    float       Floor(float _val);

    // Wrap value around a set of limits
    float       Wrap(float _val, float _low, float _high);

    // Get value within a range without wrapping
    float       Clamp(float _val, float _low, float _high);

    float       Pow(float _val, unsigned int _power);
    float       SquareRoot(float _val);  //TODO: Re-implement

    // Get smallest value
    float       Min(float _a, float _b);

    // Get largest value
    float       Max(float _a, float _b);

    // Absolute value
    float       Absolute(float _val);

    // Absolute value
    int         Absolute(int _val);

    // Get factorial of an unsigned integral value
    unsigned     Factorial(unsigned int _val);
}
namespace LibMath = mth;
namespace lm = mth;