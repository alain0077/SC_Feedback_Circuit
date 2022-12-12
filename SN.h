#include "Define.h"
#include <algorithm>
#include <vector>
#include <bitset>
#include <cmath>
#include <map>

/*
  Stochastic Numberのクラス
*/
class SN
{
private:
  const static int N = Define::N;     // SNのビット長:N
  const static int B = Define::B;     // LFSRのビット数:B

  std::bitset<N> sn;  // SNのビット列
  double val;    // SNの値
  double nume;   // 本来の分子の値
  int deno;      // 分母の値

  /// @brief 最長Garois LFSRの構成において、XORの入力へ繋がるビットの設定
  /// @return XORの配置位置を示す配列
  std::vector<int> get_seq_linear();

  /// @brief 最長Nonliner LFSRの構成において、XORの入力へ繋がるビットの設定
  /// @return XORの配置位置を示す配列
  std::vector<int> get_seq_nonlinear();

  /// @brief Garois LFSR（線形帰還シフトレジスタ）
  /// @param x 目的の定数
  /// @param seed 乱数生成器のseed
  /// @return 準乱数列
  std::vector<int> lfsr(int x, int seed);

  /// @brief nonliner LFSR（非線形帰還シフトレジスタ）
  /// @param x 目的の定数
  /// @param seed 乱数生成器のseed
  /// @return 準乱数列
  std::vector<int> nonlinear_lfsr(int x, int seed);

public:
  /// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し、値などを変数に登録
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  /// @param flag 0：LFSR，0以外：nonliner LFSR
  SN(int x, int seed, int flag = 0);

  /// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  /// @param flag 0：LFSR，0以外：nonliner LFSR
  void SNG(int x, int seed, int flag);

  // 保持しているSNとその値を表示 
  void print_bs();

  // SNを取得
  std::bitset<N> get_out();

  // SNの値を取得
  double get_val();

  /// @brief 2つのSNの相関の強さを取得
  /// @param sn2 比較対象
  
  double SCC(SN sn2);
};