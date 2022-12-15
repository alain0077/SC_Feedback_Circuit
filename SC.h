#pragma once

#include "SN.h"
#include "AbsError.h"

/// @brief SC演算をまとめたnamespace
namespace SC
{
    namespace Divison
    {
        class Feedback : public AbsError
        {
        private:
            SN _output;

        public:
            Feedback();
            virtual ~Feedback() = default;

            SN  Div(SN divisor, SN dividend);
        };
    }
}