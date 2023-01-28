#include "SC.h"

using namespace SC::Min;

AND::AND() : Analysis()
{
}

SN AND::operator() (SN left, SN right)
{
    auto min = left.get_sn() & right.get_sn();

    double ans = left.get_ans() < right.get_ans() ? left.get_ans() : right.get_ans();

    double val = (double)min.count() / (double) Define::N;

    double scc = left.SCC(right);

    Update_Analysis(ans, val, scc);

    return SN(ans, val, min);
}