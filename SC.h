#pragma once

#include "SN.h"
#include "AbsError.h"

/// @brief SC演算をまとめたnamespace
namespace SC
{
    namespace Divison
    {
        class CORDIV : public AbsError
        {
        public:
            CORDIV();
            virtual ~CORDIV() = default;

            SN operator() (SN divisor, SN dividend);
        };

        class Feedback : public AbsError
        {
        public:
            Feedback();
            virtual ~Feedback() = default;

            SN operator() (SN divisor, SN dividend);
        };
    }
}