#pragma once
#include "AbstractFunction.h"
#include <Random>
#include <vector>

namespace Circuit
{
    class FBSQRT : public Circuit
    {
    public:
        /// @brief Constructor
        FBSQRT();

        /// @brief Set random number generator
        FBSQRT(tools::Random rng);
        
        virtual ~FBSQRT() = default;

        /// @brief Feedback Function for SQRT
        bool Run(const bool& x) override;
    
    private:
        // shift register
        int sr_;

        // bit mask
        int mask_;

        // random nunber generator
        tools::Random rng_;
    };
}