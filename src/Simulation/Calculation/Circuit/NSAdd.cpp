#include "NSAdd.h"

using namespace Circuit;

NSAdd::NSAdd() : Circuit(), sum1_(0), sum2_(0)
{
}

bool NSAdd::Run(const bool& lhs, const bool& rhs)
{
    sum1_ += lhs + rhs;

    if (sum1_ > sum2_) {
            output_ = 1;
            sum2_++;
    } else output_ = 0;

    return output_;
}