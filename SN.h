#include "Define.h"
#include <algorithm>
#include <bitset>
#include <cmath>

/*
  Stochastic Numberのクラス
*/
class SN {
    const static int N = Define::N;     // SNのビット長:N
    const static int B = Define::B;     // LFSRのビット数:B

    std::bitset<N> sn;  // SNのビット列
    double val;    // SNの値
    double nume;   // 本来の分子の値
    int deno;      // 分母の値

    // ビットシフト用の値
    int shift1;  int shift2;  int shift3;  int shift4;
    int mask;

public:
    /*
      コンストラクタ
      数値xを初期値seedのLFSRでSNに変換し、値などを変数に登録
      複数のSNGでLFSRを共有する時のビットシフトに対応
    */
    SN(int x, int seed, int shift);

    /*
      数値xを初期値seedのLFSRでSNに変換
      上記の初期化の際に用いる
      複数のSNGでLFSRを共有する時のビットシフトに対応
    */
    std::bitset<N> SNG(int x, int seed, int shift);

    /*
      ビットシフト用の値の設定
    */
    void set_shift(int shift);

    /*
      LFSRから出力された乱数をビットシフトする
    */
    int bit_shift(int lfsr, int shift);

    // 保持しているSNとその値を表示 
    void print_bs();

    // SNを取得
    std::bitset<N> get_out();

    // SNの値を取得
    double get_val()
    {
        return this->val;
    }

    // 2つのSNの相関の強さを取得
    double SCC(SN sn2);
};