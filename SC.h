#pragma once

#include "Define.h"
#include "SN.h"
#include <vector>

/// @brief SC演算をまとめたnamespace
namespace SC
{
    namespace Divison
    {
        /// @brief Correlated Division，相関を利用した割り算．
        /// @param divisor 除数
        /// @param dividend 被除数
        /// @return 商
        SN CORDIV(SN divisor, SN dividend);

        /// @brief 提案手法，フィードバックによる割り算．
        /// @param divisor 除数
        /// @param dividend 被除数
        /// @return 商
        SN FDIV(SN divisor, SN dividend);

        
    }
}