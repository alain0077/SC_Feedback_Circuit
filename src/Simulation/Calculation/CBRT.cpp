#include "CBRT.h"
#include "Circuit/CBRT.h"
#include "Circuit/NSAdd.h"

#include <cmath>
#include <vector>

using namespace std;
using namespace SC;
using namespace tools;
using namespace Define;
using namespace Circuit;

namespace {
    /// @brief 乱数生成器
    const Random RNG = Random(0, CBRT_SR_DEPTH - 1);
} // namespace SRのための乱数生成器

SN SC::CBRT(const SN& x)
{
    int n = (int)x.size();
    vector<bool> res(n);

    Random rng = RNG;

    CBRT_Circuit circuit(rng);

    for(int i = 0; i < n; i++)
    {
        res[i] = circuit.Run(x.get_sn(i));
    }

    return SN(cbrt(x.get_ans()), res);
}

SN SC::TLCBRT(const SN& x)
{
    int n = (int)x.size();
    vector<bool> res(n);

    Random rng = RNG;

    /*
    * 定数の生成
    */
    // 乱数生成器  
    auto randN = Random(n);

    // 1/3 
    double a = 1 / 3.0;
    a *= (double)n;
    SN sn3((int)a, randN(), n);
    
    // 1/9
    a = 1 / 9.0;
    a *= (double)n;
    SN sn2 = SN((int)a, randN(), n);
    
    // 5/81
    a = 5 / 81.0;
    a *= (double)n;
    SN sn1 = SN((int)a, randN(), n);

    // NSAdd
    NSAdd ns1;
    NSAdd ns2;

    /*
    * SR
    */
    int sr1;
    int sr2;
    int mask = (1<<CBRT_SR_DEPTH) - 1;

    sr1 = rng();
    sr2 = rng();

    for(int i = 0; i < n; i++)
    {
        // AND
        res[i] = !x.get_sn()[i] && sn1.get_sn(i);

        // NSAdd
        res[i] = ns1.Run(res[i], sn2.get_sn(i));

        // SR
        int ran = rng();
        sr1 <<= 1;
        sr1 &= mask;
        sr1 = sr1 | res[i];
        res[i] = (sr1 >> ran) & 1;

        // AND
        res[i] = !x.get_sn()[i] && res[i];

        // NSAdd
        res[i] = ns2.Run(res[i], sn3.get_sn(i));

        // SR
        ran = rng();
        sr2 <<= 1;
        sr2 &= mask;
        sr2 = sr2 | res[i];
        res[i] = (sr2 >> ran) & 1;

        // NAND
        res[i] = !(res[i] && !x.get_sn(i));
    }

    return SN(cbrt(x.get_ans()), res);
}

SN SC::FixCBRT(const SN& x)
{
    int rn = Random(x.size()/2)();   

    vector<pair<int, vector<bool>>> offset;

    SN sn1 = SN(197, rn, 512);
    SN sn2 = SN(137, rn, 512);

    offset.push_back(make_pair(82, sn1.get_sn()));
    offset.push_back(make_pair(238, sn2.get_sn()));

    return FixCBRT(x, offset);
}

SN SC::FixCBRT(const SN& x, const int& d)
{
    int n = (int)x.size();
    vector<bool> res(n);

    Random rng = RNG;

    CBRT_Circuit circuit(rng);

    int cnt = 0;
    int mask = (1 << d) - 1;

    for(int i = 0; i < n; i++)
    {
        res[i] = circuit.Run(x.get_sn(i));

        // Counter
        if(cnt == mask) cnt++;
        else cnt += x.get_sn()[i]? 0 : 1;

        // If maximum, set output to 1.
        res[i] = res[i] || (cnt == mask);
        
        // bit masking
        cnt &= mask;
    }

    return SN(cbrt(x.get_ans()), res);
}


SN SC::FixCBRT(const SN& x, const vector<pair<int, vector<bool>>>& offset, const int& s)
{
    if(offset.size() != 3) throw runtime_error("SC::FixCBRT：無効な引数offsetが与えられました．");

    int n = (int)x.size();
    vector<bool> res(n);

    Random rng = RNG;

    CBRT_Circuit circuit(rng);

    int size = s <= 0 ? n / 2 : s;
    
    // wait cnt
    int clock_cnt = 1;

    // 1の数
    int cnt = 0;

    // 補正回路の出力
    bool fix_out = 0;

    // bound2 - Nに足すか
    bool flag = offset.back().first == size;

    for(int i = 0; i < n; i++)
    {
        res[i] = circuit.Run(x.get_sn(i));

        // 補正回路
        fix_out = false;

        if(clock_cnt == size)
        {
            int bound1 = offset[0].first;
            int bound2 = offset[1].first;

            if(0 <= cnt && cnt < bound1)
            {
                auto v = offset[0].second;
                fix_out = v[i%v.size()];
            }
            else if(bound1 <= cnt && cnt < bound2)
            {
                auto v = offset[1].second;
                fix_out = v[i%v.size()];
            }
            else
            {
                if(flag)
                {
                    auto v = offset.back().second;
                    fix_out = v[i%v.size()];
                }
                else fix_out = false;
            }
        }
        else
        {
            cnt += (x.get_sn(i)) ? 1 : 0;
            clock_cnt++;
        }

        res[i] = res[i] || fix_out;
    }

    return SN(cbrt(x.get_ans()), res);
}