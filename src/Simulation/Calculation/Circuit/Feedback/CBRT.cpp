#include "CBRT.h"
#include <Define.h>

using namespace tools;
using namespace Circuit;
using namespace Define;

namespace {
    /// @brief 乱数生成器
    const Random RNG = Random(0, CBRT_SR_DEPTH - 1);
} // namespace SRのための乱数生成器

// FBCBRT::FBCBRT(const int& d) : Circuit(), mask_((1<<d) - 1)
// {
//     rng_.range(0,d-1);
//     sr1_ = 0;
//     sr2_ = (1<<d) - 1;
// }

FBCBRT::FBCBRT() : FBCBRT::FBCBRT(RNG)
{
}

FBCBRT::FBCBRT(Random rng) : Circuit()
{
    rng_ = rng;

    int d = rng_.max() + 1;
    mask_ = (1<<d) - 1;
    sr1_ = 0;
    sr2_ = (1<<d) - 1;
}

bool FBCBRT::Run(const bool& x)
{
    // SR
    int ran = rng_();
    sr1_ <<= 1;
    sr1_ &= mask_;
    sr1_ |= x;
    output_ = (sr1_ >> ran) & 1;

    // AND
    output_ &= x;

    // NOT
    output_ = !output_;

    // SR
    ran = rng_();
    sr2_ <<= 1;
    sr2_ &= mask_;
    sr2_ |= output_;
    output_ = (sr2_ >> ran) & 1;

    // AND
    output_ &= x;

    return output_;
}