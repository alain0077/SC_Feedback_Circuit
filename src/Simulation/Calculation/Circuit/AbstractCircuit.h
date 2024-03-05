#pragma once

#include <string>
#include <vector>

namespace Circuit {
  class Circuit
  {
  public:
    /// @brief コンストラクタ
    Circuit() : output_(0) {}

    /// @brief デストラクタ
    virtual ~Circuit() = default;

    /// @brief 1入力回路の実装
    virtual bool Run(const bool& input) { return true; }

    /// @brief 2入力回路の実装
    virtual bool Run(const bool& input1, const bool& input2) { return true; }

    /// @brief 3入力回路の実装
    virtual bool Run(const bool& input1, const bool& input2, const bool& input3) { return true; }
    
    /// @brief 回路の定数の設定
    /// @param const_num 定数
    virtual void set_Const(const std::vector<unsigned int>& const_num) {}

    virtual void set_Param(const unsigned int& param) {}

    /// @brief 関数の出力を取得する
    /// @return 出力
    bool get_Output() const { return output_; }

  protected:
    // 関数の出力
    bool output_;
  };
} // namespace Circuit