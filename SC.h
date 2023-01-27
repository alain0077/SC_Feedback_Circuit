#pragma once
#include "SN.h"
#include "AbsError.h"
#include "Analysis.h"

/// @brief SC演算をまとめたnamespace
namespace SC
{
    namespace Addition
    {
        class MUX : public Analysis
        {
        public:
            MUX();
            virtual ~MUX() = default;
            
            SN operator() (SN augend, SN addend);
            SN operator() (SN augend, SN addend, SN half);
        };

        class OR : public Analysis
        {
        public:
            OR();
            virtual ~OR() = default;
            
            SN operator() (SN augend, SN addend);
            //SN operator() (SN augend, SN addend, int depth);
        };

        class NSAdd : public Analysis
        {
        public:
            NSAdd();
            virtual ~NSAdd() = default;
            
            SN operator() (SN augend, SN addend);
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

    namespace Min
    {
        class AND : public Analysis
        {
        public:
            AND();
            virtual ~AND() = default;

            SN operator() (SN left, SN right);
        };
    }

    namespace Max
    {
        class OR : public Analysis
        {
        public:
            OR();
            virtual ~OR() = default;

            SN operator() (SN left, SN right);
        };
    }
}