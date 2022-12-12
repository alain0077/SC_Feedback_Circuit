#include "SN.h"
#include <iostream>

using namespace std;

/// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し、値などを変数に登録
/// @param x 定数
/// @param seed 乱数生成器のseed
/// @param flag 0：LFSR，0以外：nonliner LFSR
SN::SN(int x, int seed, int flag)
{
    // LFSRのためのmaskの設定
    //mask = N - 1;

    SNG(x, seed, flag);
    nume = (double)x;
    deno = N;
    val = (double)sn.count() / (double)N;
}

/// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
/// @param x 定数
/// @param seed 乱数生成器のseed
/// @param flag 0：LFSR，0以外：nonliner LFSR
void SN::SNG(int x, int seed, int flag)
{
    // LFSRまたは，nonliner LFSRより準乱数列を生成
    vector<int> lds = flag? nonlinear_lfsr(x, seed) : lfsr(x, seed);

    // Comparator
    for (int i = 0; i < N; i++) {
        // lfsrは1～N-1の範囲の値を出力するため，>=で比較
        if (!flag && x >= lds[i]) sn.set(i);
        // nonlinear lfsrは0～N-1の範囲の値を出力するため，>で比較
        else if(flag && x > lds[i]) sn.set(i);
    }
}

/// @brief Garois LFSR（線形帰還シフトレジスタ）
/// @param x 目的の定数
/// @param seed 乱数生成器のseed
/// @return 準乱数列
vector<int> SN::lfsr(int x, int seed)
{
    // shift register
    int sr = seed;

    // XORの位置情報について取得
    vector<int> list = get_seq_linear();

    // return
    vector<int> res;

    for(int i = 0; i < N; i++) {
        res.push_back(sr);

        // 最下位ビットを抽出
        int lsb = sr & 1;

        // 1ビット右シフト
        sr >>= 1;

        // 上位にビットに最下位ビットを挿入
        sr |= (lsb << (B - 1));

        // 配置したxorについて演算する
        for (auto l : list) sr ^= (lsb << l);
    }

    return res;
}

/// @brief nonliner LFSR（非線形帰還シフトレジスタ）
/// @param x 目的の定数
/// @param seed 乱数生成器のseed
/// @return 準乱数列
vector<int> SN::nonlinear_lfsr(int x, int seed)
{
    // shift register
    int sr = seed;

    // XORの位置情報について取得
    vector<int> list = get_seq_nonlinear();

    // return
    vector<int> res;

    for(int i = 0; i < N; i++) {
        res.push_back(sr);

        // 最下位ビット以外がゼロかどうかの判定
        int nor = sr == 0 || sr == 1;

        // フェードバック関数の結果を格納する変数
        int b = nor;

        // 配置したxorについて演算する
        for(auto l : list) b ^= (sr >> l) & 1;

        // 1ビット右シフト
        sr >>= 1;
        
        // 上位にビットにフィードバック関数の結果を挿入
        sr |= b << (B-1);
    }

    return res;
}

// 保持しているSNとその値を表示 
void SN::print_bs()
{
    cout << sn << " = " << sn.count() << "/" << N << " = " << val << endl;
}

// SNを取得
bitset<SN::N> SN::get_out()
{
    return sn;
}

// SNの値を取得
double SN::get_val()
{
    return val;
}

// 2つのSNの相関の強さを取得
double SN::SCC(SN sn2)
{
    bitset<N> input1 = sn;
    bitset<N> input2 = sn2.sn;
    bitset<N> sn3 = input1 & input2;

    double p12 = (double)sn3.count() / (double)N;
    double p1 = (double)input1.count() / (double)N;
    double p2 = (double)input2.count() / (double)N;

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

/// @brief 最長Garois LFSRの構成において、XORの入力へ繋がるビットの設定
/// @return XORの配置位置を示す配列
vector<int> SN::get_seq_linear()
{
    if (B == 3)
        return { 1 };
    if (B == 4)
        return { 2 };
    if (B == 5)
        return { 2 };
    if (B == 6)
        return { 4 };
    if (B == 7)
        return { 5 };
    if (B == 8)
        return { 5, 4, 3 };
    if (B == 9)
        return { 4 };
    if (B == 10)
        return { 6 };
    if (B == 11)
        return { 8 };
    if (B == 12)
        return { 10, 9, 3 };

    return {};
}

/// @brief 最長Nonliner LFSRの構成において、XORの入力へ繋がるビットの設定
/// @return XORの配置位置を示す配列
vector<int> SN::get_seq_nonlinear()
{
    if (B == 3)
        return { 2, 0 };
    if (B == 4)
        return { 3, 0 };
    if (B == 5)
        return { 3, 0 };
    if (B == 6)
        return { 5, 0 };
    if (B == 7)
        return { 6, 0 };
    if (B == 8)
        return { 6, 5, 4, 0 };
    if (B == 9)
        return { 5, 0 };
    if (B == 10)
        return { 7, 0 };
    if (B == 11)
        return { 9, 0 };
    if (B == 12)
        return { 11, 10, 4, 0 };

    return {};
}