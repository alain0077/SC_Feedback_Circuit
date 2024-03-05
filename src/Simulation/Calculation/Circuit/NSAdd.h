#pragma once
#include "AbstractCircuit.h"

namespace Circuit {
    class NSAdd : public Circuit
    {
    public:
        NSAdd();
        virtual ~NSAdd() = default;

        /// @brief NSAdd
        bool Run(const bool& lhs, const bool& rhs) override;
    
    private:
        // Accumulator
        unsigned short sum1_;
        unsigned short sum2_;
    };
}