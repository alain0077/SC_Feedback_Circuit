#pragma once
#include "SN.h"
#include <Random>

namespace SC
{
    /// @brief SRの深さ
    const static int SQRT_SR_DEPTH = 5;

    SN SQRT(const SN& x, tools::Random rng = tools::Random(0, SQRT_SR_DEPTH - 1));
}