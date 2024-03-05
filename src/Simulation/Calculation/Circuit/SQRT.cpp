#include "SQRT.h"
#include "Feedback/SQRT.h"
#include "NSAdd.h"

using namespace std;
using namespace tools;
using namespace Circuit;

SQRT_Circuit::SQRT_Circuit(Random rng) : FeedbackCircuit()
{
  Output_ = make_shared<NSAdd>();
  Feedback_ = make_shared<FBSQRT>(rng);
}