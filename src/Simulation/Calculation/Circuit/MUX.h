#pragma once
#include "AbstractCircuit.h"

namespace Circuit {
    class MUX : public Circuit
    {
    public:
        MUX();
        virtual ~MUX() = default;

        /// @brief MUX (control ? lhs : rhs)
        bool Run(const bool& lhs, const bool& rhs, const bool& control) override;
    };
} // namespace Circuit