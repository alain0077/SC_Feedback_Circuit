#include "AND.h"

using namespace Circuit;

AND::AND() : Circuit()
{
}

bool AND::Run(const bool& lhs, const bool& rhs)
{
    output_ = lhs & rhs;

    return output_;
}