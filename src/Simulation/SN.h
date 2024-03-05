#pragma once
#include <Define.h>

#include <algorithm>
#include <cmath>
#include <optional>
#include <vector>

namespace SC {
  class SN
  {
  private:
    /// @brief SNの生成精度
    std::uint16_t N_;

    /// @brief SNの生成時にLFSRの値と比較した定数
    /// @note 演算などで生成された出力SNの場合はstd::nulloptを設定する．
    std::optional<std::uint16_t> x_;

    /// @brief SNの生成時にLFSRに与えたseed値
    /// @note 演算などで生成された出力SNの場合はstd::nulloptを設定する．
    std::optional<std::uint16_t> seed_;

    /// @brief SNのビット列
    std::vector<bool> sn_;

    /// @brief SNの値
    double val_;

    /// @brief 本来の値
    double ans_;

  public:
    /// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し、値などを変数に登録
    /// @param x 定数
    /// @param seed 乱数生成器のseed
    /// @param N ビット長
    SN(std::uint16_t x, std::uint16_t seed, std::uint16_t N);

    /// @brief コンストラクタ，指定したビット列のSNを生成
    /// @param ans 本来の値
    /// @param sn SNのビット列
    SN(double ans, std::vector<bool> sn);

    /// @brief デストラクタ
    ~SN() = default;

    /// @brief SNのビット長を取得
    /// @return SNのビット長
    std::size_t size() const { return sn_.size(); }

    /// @brief SNを取得
    /// @return SN
    std::vector<bool> get_sn() const { return sn_; }
    
    /// @brief SNのiビット目を取得
    /// @param i iビット目
    /// @return iビット目
    /// @note std::vector::operator[]の動作に従う．
    bool get_sn(int i) const { return sn_[i]; }

    /// @brief SNの生成時の定数を取得
    /// @return SNの生成時の定数，演算の結果などであればnullopt
    decltype(x_) get_const() const { return x_; }

    /// @brief SNの生成時のseed値を取得
    /// @return SNの生成時のseed値，演算の結果などであればnullopt
    decltype(seed_) get_seed() const { return seed_; }

    /// @brief SNの値を取得
    /// @return SNの値
    double get_val() const { return val_; }

    /// @brief SNの本来の値を取得
    /// @return SNの本来の値
    double get_ans() const { return ans_; }
  };

  /// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  /// @param N ビット長
  SN SNG(std::uint16_t x, std::uint16_t seed, std::uint16_t N);

  /// @brief 2つのSNの相関の強さを取得
  /// @param sn 比較対象
  /// @note サイズの違うSNを与えると小さい方に合わせて処理をする．
  double SCC(const std::vector<bool>& lhs, const std::vector<bool>& rhs);

  /// @brief 2つのSNの相関の強さを取得
  /// @param sn 比較対象
  /// @note サイズの違うSNを与えると小さい方に合わせて処理をする．
  double SCC(const SN& lhs, const SN& rhs);
}