#pragma once
#include "Define.h"
#include "AbstractFunction.h"
#include <initializer_list>
#include <bitset>

namespace Feedback
{
    class FeedbackCircuit
    {
    public:
        /// @brief コンストラクタ
        /// @param output 出力関数
        /// @param feedback Feedback関数
        FeedbackCircuit(Function* output, Function* feedback);

        /// @brief デストラクタ
        virtual ~FeedbackCircuit() = default;
        
        /// @brief 入力を与えて回路を実行する
        /// @param inputs_to_output 回路の入力（出力関数への入力）
        /// @return 出力
        bool Run(const bool& input_to_output);

        /// @brief 入力を与えて回路を実行する
        /// @param inputs_to_output 回路の入力（出力関数への入力）
        /// @return 出力
        bool Run(const std::initializer_list<bool>& inputs_to_output);

        /// @brief 入力を与えて回路を実行する
        /// @param inputs_to_output 回路の入力（出力関数への入力）
        /// @param input_to_feedback 回路の入力（Feedback関数への入力）
        /// @return 出力
        bool Run(const bool& input_to_output, const bool& input_to_feedback);

        /// @brief 入力を与えて回路を実行する
        /// @param inputs_to_output 回路の入力（出力関数への入力）
        /// @param input_to_feedback 回路の入力（Feedback関数への入力）
        /// @return 出力
        bool Run(const std::initializer_list<bool>& inputs_to_output, const bool& input_to_feedback);

        /// @brief 入力を与えて回路を実行する
        /// @param input_to_output 回路の入力（出力関数への入力）
        /// @param inputs_to_feedback 回路の入力（Feedback関数への入力）
        /// @return 出力
        bool Run(const bool& input_to_output, const std::initializer_list<bool>& inputs_to_feedback);

        /// @brief 入力を与えて回路を実行する
        /// @param inputs_to_output 回路の入力（出力関数への入力）
        /// @param inputs_to_feedback Feedback関数への入力（あれば）
        /// @return 出力
        bool Run(const std::initializer_list<bool>& inputs_to_output, const std::initializer_list<bool>& inputs_to_feedback);

    private:
        /// @brief 出力関数
        Function* _Output;

        /// @brief Feedback関数
        Function* _Feedback;
    };
}