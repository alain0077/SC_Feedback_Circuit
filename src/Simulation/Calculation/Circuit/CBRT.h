#include "FeedbackCircuit.h"
#include <Random>

namespace Circuit {
  class CBRT_Circuit : public FeedbackCircuit
  {
  public:
    /// @brief コンストラクタ
    /// @param rnd 乱数生成器
    CBRT_Circuit();

    /// @brief コンストラクタ
    /// @param rnd 乱数生成器
    CBRT_Circuit(tools::Random rnd);

    /// @brief デストラクタ
    ~CBRT_Circuit() = default;
  };
} // namespace Circuit