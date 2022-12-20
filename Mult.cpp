#include "SC.h"

using namespace SC::Multiplication;

AND::AND() : Analysis()
{
}

SN AND::operator() (SN multiplier, SN multiplicand)
{
    auto sn = multiplicand.get_sn() & multiplier.get_sn();

    double ans = multiplicand.get_ans() * multiplier.get_ans();

    double val = (double)sn.count() / (double) Define::N;

    // SCC
    double scc = multiplier.SCC(multiplicand);
    
    Update_Analysis(ans, val, scc);

    return SN(ans, val, sn);
}