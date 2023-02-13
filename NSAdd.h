#pragma once
#include "AbstractFunction.h"

namespace Feedback
{
    class NSAdd : public Function
    {
    public:
        NSAdd();
        virtual ~NSAdd() = default;

        /// @brief NSAdd
        void Run(const bool& lhs, const bool& rhs) override;
    
    private:
        // Accumulator
        int sum1;
        int sum2;
    };
}