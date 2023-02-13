#pragma once
#include "AbstractFunction.h"

namespace Feedback
{
    class AND : public Function
    {
    public:
        AND();
        virtual ~AND() = default;

        /// @brief AND
        void Run(const bool& lhs, const bool& rhs) override;
    };
}