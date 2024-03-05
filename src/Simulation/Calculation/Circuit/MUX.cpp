#include "MUX.h"

using namespace Circuit;

MUX::MUX() : Circuit()
{
}

bool MUX::Run(const bool& lhs, const bool& rhs, const bool& control)
{
    output_ = control ? lhs : rhs;

    return output_;
}