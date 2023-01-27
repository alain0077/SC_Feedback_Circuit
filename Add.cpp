#include "SC.h"
#include "Random.h"

using namespace SC::Addition;

MUX::MUX() : Analysis()
{
}

SN MUX::operator() (SN augend, SN addend)
{
    // 1/2
    SN half = SN(1.0/2.0, Random()());

    // Calculation
    auto and1 = augend.get_sn() & (~half.get_sn()); 
    auto and2 = augend.get_sn() & half.get_sn();
    auto or = and1 | and2;

    double ans = augend.get_ans() + addend.get_ans(); ans /= 2.0;

    double val = (double)or.count() / (double) Define::N;

    double scc = augend.SCC(addend);

    Update_Analysis(ans, val, scc);

    return SN(ans, val, or);
}

SN MUX::operator() (SN augend, SN addend, SN half)
{
    // Calculation
    auto and1 = augend.get_sn() & (~half.get_sn()); 
    auto and2 = augend.get_sn() & half.get_sn();
    auto or = and1 | and2;

    double ans = augend.get_ans() + addend.get_ans(); ans /= 2.0;

    double val = (double)or.count() / (double) Define::N;

    double scc = augend.SCC(addend);

    Update_Analysis(ans, val, scc);

    return SN(ans, val, or);
}

OR::OR() : Analysis()
{
}

SN OR::operator() (SN augend, SN addend)
{
    // Calculation
    auto or = augend.get_sn() & (~addend.get_sn()); 

    double ans = augend.get_ans() + addend.get_ans();

    ans = ans > 1.0 ? 1.0 : ans;

    double val = (double)or.count() / (double) Define::N;

    double scc = augend.SCC(addend);

    Update_Analysis(ans, val, scc);

    return SN(ans, val, or);
}

/*
SN OR::operator() (SN augend, SN addend, int depth)
{
    // Calculation
    auto or = augend.get_sn() & (~addend.get_sn()); 

    double ans = augend.get_ans() + addend.get_ans();

    ans = ans > 1.0 ? 1.0 : ans;

    double val = (double)or.count() / (double) Define::N;

    double scc = augend.SCC(addend);

    Update_Analysis(ans, val, scc);

    return SN(ans, val, or);
}
*/

NSAdd::NSAdd() : Analysis()
{
}

SN NSAdd::operator() (SN augend, SN addend)
{
    // Calculation
    // NS Addの出力
    std::bitset<Define::N> nsadd;
    
    // Accumlaterの初期化
    int sum1 = 0, sum2 = 0;
    
    for (int i = 0; i < Define::N; i++) {
        sum1 += augend.get_sn()[i] + addend.get_sn()[i];

        if (sum1 > sum2) {
            nsadd[i] = 1;
            sum2++;
        }
        else nsadd[i] = 0;
    }

    double ans = augend.get_ans() + addend.get_ans();

    ans = ans > 1.0 ? 1.0 : ans;

    double val = (double)nsadd.count() / (double) Define::N;

    double scc = augend.SCC(addend);

    Update_Analysis(ans, val, scc);

    return SN(ans, val, nsadd);
}