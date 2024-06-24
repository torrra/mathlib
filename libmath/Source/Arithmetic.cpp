#include "libmath/Arithmetic.h"

#include <cmath>

namespace mth
{
    float Absolute(float _val)
    {
        // Multiply by -1 if negative
        return (_val < 0) ? -_val : _val;
    }

    bool AlmostEqual(float _a, float _b, float _epsilon)
    {
        // Check if difference is smaller than epsilon
        return Absolute(_a - _b) <= _epsilon;
    }

    float Round(float _val)
    {
        float       floored = Floor(_val);

        // Round up if decimal part > .5
        if (_val - floored >= 0.5f)
            return floored + 1.f;

        // Round down if not
        else
            return floored;
    }

    float Ceil(float _val)
    {
        float       floored = Floor(_val);

        // Round up if there is a decimal part
        return (floored == _val) ? floored : floored + 1.f;
    }

    float Floor(float _val)
    {
        // Remove decimal part
        return static_cast<float>((int) _val);
    }


    float Wrap(float _val, float _low, float _high)
    {
        if (-_val > _high)
        _val = _high + fmodf(_val - _high, _low - _high);

        else
            _val = _low + fmodf(_val - _low, _high - _low);

        if (_val < _low)
            _val += _high;

        return _val;

    }


    float Clamp(float _val, float _low, float _high)
    {
        // Return highest of low values
        if (_val < _low)
            return _low;

        // Return lowest of high values
        if (_val > _high)
            return _high;

        return _val;
    }

    float Pow(float _val, unsigned int _power)
    {
        if (0 == _power)
            return 1.f;

        if (1 == _power)
            return _val;


        float       valCpy = _val;

        // Multiply value by itself _power times
        for (unsigned int iteration = 1u; iteration < _power; ++iteration)
            _val *= valCpy;

        return _val;
    }

    float SquareRoot(float _val)
    {
        return sqrtf(_val);
    }


    float Min(float _a, float _b)
    {
        // Return smallest
        return (_a < _b) ? _a : _b;
    }


    float Max(float _a, float _b)
    {
        // Return largest
        return (_a > _b) ? _a : _b;
    }


    int Absolute (int _val)
    {
        // Multiply by -1 if < 0
        return (_val < 0) ? -_val : _val;
    }

    unsigned int Factorial(unsigned int _val)
    {
        if (0u == _val || 1u == _val)
            return 1u;

        if (2 == _val)
            return _val;

        unsigned int   valCpy = _val - 1u;

        // Multiply _val by numbers smaller than itself going all the way down to 1
        while (valCpy > 0u)
            _val *= valCpy--;

        return _val;
    }

}