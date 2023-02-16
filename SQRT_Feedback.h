#pragma once
#include "AbstractFunction.h"
#include "Random.h"
#include <vector>

namespace Feedback
{
    class FBSQRT : public Function
    {
    public:
        /// @brief Set depth of shift register
        FBSQRT(const int& depth = 5);
        virtual ~FBSQRT() = default;

        /// @brief Feedback Function for SQRT
        void Run(const bool& x) override;
    
    private:
        // shift register
        int _sr;

        // bit mask
        int _mask;

        // depth
        int _depth;

        // random nunber generator
        Random _rng;
    };
}