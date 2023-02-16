#include "MyDiv.h"
#include "AND.h"
#include "NSAdd.h"
#include "FeedbackCircuit.h"

#define N Define::N

using namespace std;
using namespace SC;
using namespace Feedback;

SN SC::MyDiv(const SN& divisor, const SN& dividend)
{
    bitset<N> res;

    // NSAdd* output  = new NSAdd();
    // AND* feedback = new AND();

    NSAdd output;
    AND feedback;

    FeedbackCircuit circuit(&output, &feedback);

    for(int i = 0; i < N; i++)
    {
        res[i] = circuit.Run(dividend.get_sn()[i], !divisor.get_sn()[i]);
    }

    return SN(dividend.get_ans()/divisor.get_ans(), (double)res.count()/(double)N, res);
}