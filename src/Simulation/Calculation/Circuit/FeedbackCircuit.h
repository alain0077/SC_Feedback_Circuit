#pragma once

#include "AbstractCircuit.h"
#include <initializer_list>
#include <memory>

namespace Circuit {
  class FeedbackCircuit : public Circuit
  {
  public:
    /// @brief コンストラクタ
    FeedbackCircuit();

    /// @brief デストラクタ
    virtual ~FeedbackCircuit();
    
    /// @brief 入力を与えて回路を実行する
    /// @param inputs_to_output 回路の入力（出力関数への入力）
    /// @return 出力
    bool Run(const bool& input_to_output) override;

    /// @brief 入力を与えて回路を実行する
    /// @param inputs_to_output 回路の入力（出力関数への入力）
    /// @return 出力
    bool Run(const std::initializer_list<bool>& inputs_to_output);

    /// @brief 入力を与えて回路を実行する
    /// @param inputs_to_output 回路の入力（出力関数への入力）
    /// @param input_to_feedback 回路の入力（Feedback関数への入力）
    /// @return 出力
    bool Run(const bool& input_to_output, const bool& input_to_feedback) override;

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

  protected:
    /// @brief 出力関数
    std::shared_ptr<Circuit> Output_;

    /// @brief Feedback関数
    std::shared_ptr<Circuit> Feedback_;
  };
} // namespace Circuit