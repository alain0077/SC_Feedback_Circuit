#include "Division.h"
#include "AND.h"
#include "NSAdd.h"

using namespace std;
using namespace Circuit;

DIV_Circuit::DIV_Circuit() : FeedbackCircuit()
{
  Output_ = make_shared<NSAdd>();
  Feedback_ = make_shared<AND>();
}