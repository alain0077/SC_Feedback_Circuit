#include "AND.h"

using namespace Feedback;

AND::AND() : Function()
{
}

void AND::Run(const bool& lhs, const bool& rhs)
{
    _output = lhs & rhs;
}