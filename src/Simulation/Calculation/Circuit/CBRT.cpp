#include "CBRT.h"
#include "Feedback/CBRT.h"
#include "NSAdd.h"
#include <Define.h>

using namespace std;
using namespace tools;
using namespace Circuit;
using namespace Define;

namespace {
  /// @brief 乱数生成器
  const Random RNG = Random(0, CBRT_SR_DEPTH - 1);
} // namespace SRのための乱数生成器

// CBRT_Circuit::CBRT_Circuit(const int& depth) : FeedbackCircuit()
// {
//   _Output = make_shared<NSAdd>();
//   _Feedback = make_shared<FBCBRT>(depth);
// }

CBRT_Circuit::CBRT_Circuit() : FeedbackCircuit()
{
  Output_ = make_shared<NSAdd>();
  Feedback_ = make_shared<FBCBRT>(RNG);
}

CBRT_Circuit::CBRT_Circuit(Random rnd) : FeedbackCircuit()
{
  Output_ = make_shared<NSAdd>();
  Feedback_ = make_shared<FBCBRT>(rnd);
}