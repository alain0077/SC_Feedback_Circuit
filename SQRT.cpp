#include "SQRT.h"
#include "SQRT_Feedback.h"
#include "NSAdd.h"
#include "FeedbackCircuit.h"

#include <cmath>

#define N Define::N

using namespace std;
using namespace SC;
using namespace Feedback;

SN SC::SQRT(const SN& x)
{
    bitset<N> res;

    NSAdd output;
    FBSQRT feedback;

    FeedbackCircuit circuit(&output, &feedback);

    for(int i = 0; i < N; i++)
    {
        res[i] = circuit.Run(x.get_sn()[i]);
    }

    return SN(sqrt(x.get_ans()), (double)res.count()/(double)N, res);
}