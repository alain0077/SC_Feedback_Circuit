#include "SC.h"
#include "Random.h"

using namespace SC::Divison;

/*
 * Division
*/
CORDIV::CORDIV() : AbsError()
{
}

SN CORDIV::operator() (SN divisor, SN dividend)
{
    auto rng = Random();

    int rn = rng();
    const int N = Define::N;

    divisor = divisor.regeneration(rn);
    dividend = dividend.regeneration(rn);

    std::bitset<N> mux;

    //D-FF
    int d = 0;

    for (int i = 0; i < N; i++) {
        
        mux[i] = divisor.get_out()[i]? dividend.get_out()[i] : d;

        d = mux[i];
    }

    // 本来の値を計算
    double ans = dividend.get_ans() / divisor.get_ans();

    // 出力SNの値を計算
    double val = (double)mux.count()/(double)Define::N;

    Update_Error(ans, val);

    return SN(mux, val, ans);
}


Feedback::Feedback() : AbsError()
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
        sum1 += dividend.get_out()[i] + block;

        if (sum1 > sum2) {
            nsadd[i] = 1;
            sum2++;
        }
        else nsadd[i] = 0;
        
        block = nsadd[i] && (!divisor.get_out()[i]);
    }

    // 本来の値を計算
    double ans = dividend.get_ans() / divisor.get_ans();

    // 出力SNの値を計算
    double val = (double)nsadd.count()/(double)Define::N;


    Update_Error(ans, val);

    return SN(nsadd, val, ans);
}