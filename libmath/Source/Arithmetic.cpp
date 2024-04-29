#include "libmath/Arithmetic.h"

namespace mth
{
    float absolute(float _val)
    {
        return (_val < 0) ? -_val : _val;
    }

    bool almostEqual(float _a, float _b, float _epsilon)
    {
        return absolute(_a - _b) <= _epsilon;
    }

    float round(float _val)
    {
        float       floored = floor(_val);

        if (_val - floored >= 0.5f)
            return floored + 1.f;

        else
            return floored;
    }

    float ceil(float _val)
    {
        float       floored = floor(_val);

        return (floored == _val) ? floored : floored + 1.f;
    }

    float floor(float _val)
    {
        return static_cast<float>((int) _val);
    }


    float wrap(float _val, float _low, float _high)
    {
        float       abs = absolute(_val);

        if (_val > _high)
        {
            float   count = floor(abs / _high);

            abs -= count * _high;
        }

        return _low + abs;
    }


    float clamp(float _val, float _low, float _high)
    {
        if (_val < _low)
            return _low;
        
        if (_val > _high)
            return _high;

        return _val;
    }

    float pow(float _val, unsigned int _power)
    {
        if (0 == _power)
            return 1.f;

        if (1 == _power)
            return _val;


        float       valCpy = _val;

        for (unsigned int iteration = 1u; iteration < _power; ++iteration)
            _val *= valCpy;

        return _val;
    }


    float min(float _a, float _b)
    {
        return (_a < _b) ? _a : _b;
    }


    float max(float _a, float _b)
    {
        return (_a > _b) ? _a : _b;
    }

    
    int absolute (int _val)
    {
        return (_val < 0) ? -_val : _val;
    }

    unsigned int factorial(unsigned int _val)
    {
        if (0u == _val || 1u == _val)
            return 1u;

        if (2 == _val)
            return _val;

        unsigned int   valCpy = _val - 1u;

        while (valCpy > 0u) 
            _val *= valCpy--;

        return _val;
    }

}