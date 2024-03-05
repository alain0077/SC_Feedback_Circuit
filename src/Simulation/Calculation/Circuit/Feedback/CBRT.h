#pragma once
#include "AbstractFunction.h"
#include <Random>

namespace Circuit {
    class FBCBRT : public Circuit
    {
    public:
        /// @brief Constructor
        FBCBRT();

        /// @brief Set random number generator
        FBCBRT(tools::Random rng);

        virtual ~FBCBRT() = default;

        /// @brief Feedback Function for SQRT
        bool Run(const bool& x) override;

    private:
        // shift register
        int sr1_;
        int sr2_;

        // bit mask
        int mask_;

        // random nunber generator
        tools::Random rng_;
    };
} // namespace Circuit