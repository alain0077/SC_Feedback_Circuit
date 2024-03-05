#include "SQRT.h"
#include "Circuit/SQRT.h"

#include <cmath>

using namespace std;
using namespace tools;
using namespace SC;
using namespace Circuit;

SN SC::SQRT(const SN& x, Random rng)
{
    auto n = x.size();
    vector<bool> res(n);
    
    SQRT_Circuit circuit(rng);

    for(size_t i = 0; i < n; i++)
    {
        res[i] = circuit.Run(x.get_sn()[i]);
    }

    return SN(sqrt(x.get_ans()), res);
}