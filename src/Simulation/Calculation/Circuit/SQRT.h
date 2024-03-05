#include "FeedbackCircuit.h"
#include <Random>

namespace Circuit {
  class SQRT_Circuit : public FeedbackCircuit
  {
  public:
    /// @brief コンストラクタ
    /// @param rnd 乱数生成器
    SQRT_Circuit(tools::Random rnd);

    /// @brief デストラクタ
    ~SQRT_Circuit() = default;
  };
} // namespace Circuit
