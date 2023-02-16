#include "SQRT_Feedback.h"

using namespace Feedback;

FBSQRT::FBSQRT(const int& d) : Function(), _depth(d), _mask((1<<d) - 1)
{
    _rng.range(0,d-1);
    _sr = _rng();
}

void FBSQRT::Run(const bool& x)
{
    int ran = _rng();

    _sr <<= 1;
    _sr &= x;

    _output = (_sr >> ran) & 1;

    // AND
    _output &= x;
}