#include "MyDiv.h"
#include "Circuit/Division.h"

using namespace std;
using namespace SC;
using namespace Circuit;

SN SC::MyDiv(const SN& divisor, const SN& dividend)
{
    int n = (int)std::min(divisor.size(), dividend.size());
    vector<bool> res(n);

    DIV_Circuit circuit;

    for(int i = 0; i < n; i++)
    {
        res[i] = circuit.Run(dividend.get_sn()[i], !divisor.get_sn()[i]);
    }

    return SN(dividend.get_ans()/divisor.get_ans(), res);
}