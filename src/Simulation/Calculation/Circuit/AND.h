#pragma once
#include "AbstractCircuit.h"

namespace Circuit {
  class AND : public Circuit
  {
  public:
    AND();
    virtual ~AND() = default;

    /// @brief AND
    bool Run(const bool& lhs, const bool& rhs) override;
  };
} // namespace Circuit