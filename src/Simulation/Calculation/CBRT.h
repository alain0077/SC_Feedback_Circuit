#pragma once

#include "SN.h"
#include <Random>

namespace SC
{   
    SN CBRT(const SN& x);
    SN TLCBRT(const SN& x);
    SN FixCBRT(const SN& x);
    SN FixCBRT(const SN& x, const int& depth);
    SN FixCBRT(const SN& x, const std::vector<std::pair<int, std::vector<bool>>>& offset, const int& size = 0);
}