#include "SQRT.h"
#include <Define.h>

using namespace tools;
using namespace Circuit;
using namespace Define;

namespace {
    /// @brief 乱数生成器
    const Random RNG = Random(0, SQRT_SR_DEPTH - 1);
} // namespace SRのための乱数生成器

FBSQRT::FBSQRT() : FBSQRT::FBSQRT(RNG)
{
}

FBSQRT::FBSQRT(Random rng) : Circuit()
{
    rng_ = rng;

    int d = rng_.max() + 1;
    mask_ = (1<<d) - 1;
    sr_ = 0;
}

bool FBSQRT::Run(const bool& x)
{
    int ran = rng_();

    sr_ <<= 1;
    sr_ &= x;

    output_ = (sr_ >> ran) & 1;

    // AND
    output_ &= x;

    return output_;
}