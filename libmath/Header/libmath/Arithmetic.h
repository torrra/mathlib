#pragma once

namespace mth
{
    // Epsilon test
    bool        almostEqual(float _a, float _b, float _epsilon = 0.0001f);

    // Round to the nearest integral value
    float       round(float _val);

    // Round to the nearest integral value (greater or equal)
    float       ceil(float _val);

    // Round to the nearest integral value (smaller or equal) 
    float       floor(float _val);

    // Wrap value around a set of limits
    float       wrap(float _val, float _low, float _high);
    
    // Get value within a range without wrapping
    float       clamp(float _val, float _low, float _high);

    float       pow(float _val, unsigned int _power);
    // float       sqrt(float _v);  TODO: Re-implement

    // Get smallest value
    float       min(float _a, float _b);
    
    // Get largest value
    float       max(float _a, float _b);

    // Absolute value
    float       absolute(float _val);

    // Absolute value
    int         absolute(int _val);

    // Get factorial of an unsigned integral value
    unsigned int       factorial(unsigned int _val);
}

namespace LibMath = mth;
namespace lm = mth;