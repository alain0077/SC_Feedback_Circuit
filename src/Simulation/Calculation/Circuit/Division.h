#include "FeedbackCircuit.h"
#include <Random>

namespace Circuit {
  class DIV_Circuit : public FeedbackCircuit
  {
  public:
    /// @brief コンストラクタ
    DIV_Circuit();

    /// @brief デストラクタ
    ~DIV_Circuit() = default;
  };
} // namespace Circuit