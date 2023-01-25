#pragma once

#include "Define.h"
#include <vector>
#include <bitset>
#include <cmath>

/*
  Stochastic Numberのクラス
*/
class SN
{
private:
  const static unsigned int N = Define::N;       // SNのビット長:N
  const static unsigned short B = Define::B;       // LFSRのビット数:B
  const static bool flag = Define::PRNG; // SNGの擬似乱数生成器のフラグ

  std::bitset<N> _sn;  // SNのビット列
  double _val;    // SNの値
  double _ans;   // 本来の分子の値

  /// @brief 最長Fibonacci LFSRの構成において、XORの入力へ繋がるビットの設定
  /// @return XORの配置位置を示す配列
  std::vector<int> get_seq_linear();

  /// @brief 最長Nonliner LFSRの構成において、XORの入力へ繋がるビットの設定
  /// @return XORの配置位置を示す配列
  std::vector<int> get_seq_nonlinear();

  /// @brief Fibonacci LFSR（線形帰還シフトレジスタ）
  /// @param x 目的の定数
  /// @param seed 乱数生成器のseed
  /// @return 準乱数列
  std::vector<int> lfsr(int x, int seed);

  /// @brief nonliner LFSR（非線形帰還シフトレジスタ）
  /// @param x 目的の定数
  /// @param seed 乱数生成器のseed
  /// @return 準乱数列
  std::vector<int> nonlinear_lfsr(int x, int seed);

  /// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  void SNG(int x, int seed);

  /// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換，複数のSNGでLFSRを共有する時のビットシフトに対応
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  /// @param shift ビットシフトするビット長
  void SNG(int x, int seed, int shift);

public:
  /// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し，値などを変数に登録
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  SN(int x, int seed);

  /// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し，値などを変数に登録，複数のSNGでLFSRを共有する時のビットシフトに対応
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  /// @param shift ビットシフトするビット長
  SN(int x, int seed, int shift);

  /// @brief コンストラクタ，指定したビット列のSNを生成
  /// @param ans 本来の値
  /// @param val SNの値
  /// @param sn SNのビット列
  SN(double ans, double val, std::bitset<N> sn);

  /// @brief SNを再生成する．
  /// @param seed 乱数生成器のseed
  SN ReSNG(int seed);

  // 保持しているSNとその値を表示 
  void print_bs();

  // SNを取得
  std::bitset<N> get_sn() { return _sn; };

  // SNの値を取得
  double get_val() { return _val; };

  // SNの本来の分子の値を取得
  double get_ans() { return _ans; };

  /// @brief 2つのSNの相関の強さを取得
  /// @param sn 比較対象
  double SCC(SN sn);
};