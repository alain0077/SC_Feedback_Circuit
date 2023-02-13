#include "NSAdd.h"

using namespace Feedback;

NSAdd::NSAdd() : Function(), sum1(0), sum2(0)
{
}

void NSAdd::Run(const bool& lhs, const bool& rhs)
{
    sum1 += lhs + rhs;

    if (sum1 > sum2) {
            _output = 1;
            sum2++;
    } else _output = 0;
}