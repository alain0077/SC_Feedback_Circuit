#include "SN.h"
#include <iostream>

#define flag Define::PRNG

using namespace std;
using namespace SC;

// プロトタイプ宣言
vector<uint16_t> lfsr(uint16_t, uint16_t, uint8_t);
vector<uint16_t> nonlinear_lfsr(uint16_t, uint16_t, uint8_t);
vector<uint8_t> get_seq_linear(uint8_t);
vector<uint8_t> get_seq_nonlinear(uint8_t);

/// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し、値などを変数に登録
/// @param x 定数
/// @param seed 乱数生成器のseed
/// @param n ビット長
SN::SN(uint16_t x, uint16_t seed, uint16_t n)
{
    N_ = n;
    x_ = x;
    seed_ = seed;
    sn_ = SNG(x, seed, N_).get_sn();
    ans_ = (double)x  / (double)N_;
    val_ = (double)count(sn_.begin(), sn_.end(), true) / (double)N_;
}

/// @brief コンストラクタ，指定したビット列のSNを生成．
/// @param ans 本来の値
/// @param sn SNのビット列
SN::SN(double ans, vector<bool> sn)
{
    ans_ = ans;
    sn_ = sn;
    N_ = sn_.size();
    x_ = nullopt;
    seed_ = nullopt;
    val_ = (double)count(sn_.begin(), sn_.end(), true)/(double)N_;
}

/// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
/// @param x 定数
/// @param seed 乱数生成器のseed
/// @param n ビット長
SN SC::SNG(uint16_t x, uint16_t seed, uint16_t n)
{
    uint8_t b = ceil(log2(n));
    vector<bool> sn;

    // LFSRまたは，nonliner LFSRより準乱数列を生成
    auto lds = flag? nonlinear_lfsr(seed, n, b) : lfsr(seed, n, b);

    // Comparator
    for (int i = 0; i < n; i++) {
        // lfsrは1～N-1の範囲の値を出力するため，>=で比較
        if (!flag && x >= lds[i]) sn.push_back(1);
        // nonlinear lfsrは0～N-1の範囲の値を出力するため，>で比較
        else if(flag && x > lds[i]) sn.push_back(1);
        else sn.push_back(0);
    }

    return SN((double)x / (double)n, sn);
}

// 2つのSNの相関の強さを取得
double SC::SCC(const vector<bool>& lhs, const vector<bool>& rhs)
{
    auto n = std::min(lhs.size(), rhs.size());
    vector<bool> bit;

    for(decltype(n) i = 0; i < n; i++) {
        bit.push_back(lhs[i] & rhs[i]);
    }

    double p12 = (double)count(bit.begin(), bit.end(), true) / (double)n;
    double p1 = (double)count(lhs.begin(), lhs.end(), true) / (double)n;
    double p2 = (double)count(rhs.begin(), rhs.end(), true) / (double)n;

    double omega = p12 - (p1 * p2);
    double scc;

    double a = p1 + p2 - 1;
    double b = 0;

    if (omega > 0) {
        scc = omega / (min(p1, p2) - (p1 * p2));
    }
    else {
        scc = omega / ((p1 * p2) - max(a, b));
    }

    if (isnan(scc)) {
        return 0;
    }

    return scc;
}

// 2つのSNの相関の強さを取得
double SC::SCC(const SN& lhs, const SN& rhs)
{
    return SCC(lhs.get_sn(), rhs.get_sn());
}

/// @brief Fibonacci LFSR（線形帰還シフトレジスタ）
/// @param seed 乱数生成器のseed
/// @param n ビット長
/// @param b ビット数
/// @return 準乱数列
vector<uint16_t> lfsr(uint16_t seed, uint16_t n, uint8_t b)
{
    // bit mask
    decltype(seed) mask = (1 << b) - 1;

    // shift register
    decltype(seed) sr = seed;

    // XORの位置情報について取得
    auto list = get_seq_linear(b);

    // return
    vector<decltype(seed)> res;

    for(int i = 0; i < n; i++) {
        res.push_back(sr);

        // 最上位ビットを抽出
        auto msb = (sr & (1 << (b - 1))) == (1 << (b - 1));

        // 配置したxorについて演算する（次の最下位ビットの決定）
        for (auto l : list) msb ^= (sr & (1 << l)) == (1 << l);

        // 1ビット左シフト
        sr <<= 1;

        // 最下位ビットにxorの演算結果を挿入
        sr |= msb;

        // bit masking
        sr &= mask;
    }

    return res;
}

/// @brief nonliner LFSR（非線形帰還シフトレジスタ）
/// @param seed 乱数生成器のseed
/// @param n ビット長
/// @param b ビット数
/// @return 準乱数列
vector<uint16_t> nonlinear_lfsr(uint16_t seed, uint16_t n, uint8_t b)
{
    // shift register
    auto sr = seed;

    // XORの位置情報について取得
    auto list = get_seq_nonlinear(b);

    // return
    vector<decltype(seed)> res;

    for(decltype(n) i = 0; i < n; i++) {
        res.push_back(sr);

        // 最下位ビット以外がゼロかどうかの判定
        auto nor = sr == 0 || sr == 1;

        // フィードバック関数の結果を格納する変数
        auto f = nor;

        // 配置したxorについて演算する
        for(auto l : list) f ^= (sr >> l) & 1;

        // 1ビット右シフト
        sr >>= 1;
        
        // 上位にビットにフィードバック関数の結果を挿入
        sr |= f << (b-1);
    }

    return res;
}

/// @brief 最長Fibonacci LFSRの構成において、XORの入力へ繋がるビットの設定
/// @param b ビット数
/// @return XORの配置位置を示す配列
vector<uint8_t> get_seq_linear(uint8_t b)
{
    if (b == 3)
        return { 1 };
    if (b == 4)
        return { 2 };
    if (b == 5)
        return { 2 };
    if (b == 6)
        return { 4 };
    if (b == 7)
        return { 5 };
    if (b == 8)
        return { 5, 4, 3 };
    if (b == 9)
        return { 4 };
    if (b == 10)
        return { 6 };
    if (b == 11)
        return { 8 };
    if (b == 12)
        return { 10, 9, 3 };

    return {};
}

/// @brief 最長Nonliner LFSRの構成において、XORの入力へ繋がるビットの設定
/// @param b ビット数
/// @return XORの配置位置を示す配列
vector<uint8_t> get_seq_nonlinear(uint8_t b)
{
    if (b == 3)
        return { 2, 0 };
    if (b == 4)
        return { 3, 0 };
    if (b == 5)
        return { 3, 0 };
    if (b == 6)
        return { 5, 0 };
    if (b == 7)
        return { 6, 0 };
    if (b == 8)
        return { 6, 5, 4, 0 };
    if (b == 9)
        return { 5, 0 };
    if (b == 10)
        return { 7, 0 };
    if (b == 11)
        return { 9, 0 };
    if (b == 12)
        return { 11, 10, 4, 0 };

    return {};
}