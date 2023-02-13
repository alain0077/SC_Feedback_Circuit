#pragma once

namespace Feedback
{
    class Function
    {
    public:
        /// @brief コンストラクタ，_outputを0に初期化，
        Function();

        /// @brief デストラクタ
        virtual ~Function() = default;

        /// @brief 出力関数またはFeedback関数の実装（1入力）
        virtual void Run(const bool& input) {};

        /// @brief 出力関数またはFeedback関数の実装 (2入力)
        virtual void Run(const bool& input1, const bool& input2) {};

        /// @brief 出力関数またはFeedback関数の実装 (3入力)
        virtual void Run(const bool& input1, const bool& input2, const bool& input3) {};

        /// @brief 関数の出力を取得する
        /// @return 出力
        bool get_Output() const { return _output; };

    protected:
        // 関数の出力
        bool _output;
    };
}