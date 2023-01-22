#include "SC.h"
#include "Random.h"

using namespace SC::Divison;

/*
 * Division
*/
CORDIV::CORDIV() : Analysis()
{
}

SN CORDIV::operator() (SN divisor, SN dividend)
{
    auto rng = Random();

    int rn = rng();
    const int N = Define::N;

    std::bitset<N> mux;

    //D-FF
    int d = 0;

    for (int i = 0; i < N; i++) {
        
        mux[i] = divisor.get_sn()[i]? dividend.get_sn()[i] : d;

        d = mux[i];
    }

    // 本来の値を計算
    double ans = dividend.get_ans() / divisor.get_ans();

    // 出力SNの値を計算
    double val = (double)mux.count()/(double)Define::N;

    // SCC
    double scc = divisor.SCC(dividend);

    Update_Analysis(ans, val, scc);

    return SN(ans, val, mux);
}


Feedback::Feedback() : Analysis()
{
}

SN Feedback::operator() (SN divisor, SN dividend)
{
    //emitの出力
    bool block;
    block = 0;
    
    //NS Addの出力
    std::bitset<Define::N> nsadd;
    
    //Accumlaterの初期化
    int sum1 = 0, sum2 = 0;
    
    for (int i = 0; i < Define::N; i++) {
        sum1 += dividend.get_sn()[i] + block;

        if (sum1 > sum2) {
            nsadd[i] = 1;
            sum2++;
        }
        else nsadd[i] = 0;
        
        block = nsadd[i] && (!divisor.get_sn()[i]);
    }

    // 本来の値を計算
    double ans = dividend.get_ans() / divisor.get_ans();

    // 出力SNの値を計算
    double val = (double)nsadd.count()/(double)Define::N;

    // SCC
    double scc = divisor.SCC(dividend);

    // Errorクラスの値を更新
    Update_Analysis(ans, val, scc);

    return SN(ans, val, nsadd);
}