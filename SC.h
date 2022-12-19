#pragma once

#include "SN.h"
#include "AbsError.h"
#include "Analysis.h"

/// @brief SC演算をまとめたnamespace
namespace SC
{
    namespace Divison
    {
        class CORDIV : public Analysis
        {
        public:
            CORDIV();
            virtual ~CORDIV() = default;

            SN operator() (SN divisor, SN dividend);
        };

        class Feedback : public Analysis
        {
        public:
            Feedback();
            virtual ~Feedback() = default;

            SN operator() (SN divisor, SN dividend);
        };
    }

    namespace Multiplication
    {
        class AND : public Analysis
        {
        public:
            AND();
            virtual ~AND() = default;

            SN operator() (SN multiplier, SN multiplicand);
        };
    }
}