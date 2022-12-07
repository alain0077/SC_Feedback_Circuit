#include "SN.h"
#include <vector>
#include <iostream>

using namespace std;

// 最長LFSRの構成において、XORの入力へ繋がるビットの設定
vector<int> get_seq(int N)
{
    if (N == 4)
        return { 1 << 1, 1 };
    if (N == 8)
        return { 1 << 2, 1 << 1 };
    if (N == 16)
        return { 1 << 3, 1 << 2 };
    if (N == 32)
        return { 1 << 4, 1 << 2 };
    if (N == 64)
        return { 1 << 5, 1 << 4 };
    if (N == 128)
        return { 1 << 6, 1 << 5 };
    if (N == 256)
        return { 1 << 7, 1 << 5, 1 << 4, 1 << 3 };
    if (N == 512)
        return { 1 << 8, 1 << 4 };
    if (N == 1024)
        return { 1 << 9, 1 << 6 };
    if (N == 2048)
        return { 1 << 10, 1 << 8 };
    if (N == 4096)
        return { 1 << 11, 1 << 10, 1 << 9, 1 << 3 };
    if (N == 8192)
        return { 1 << 12, 1 << 11, 1 << 10, 1 << 7 };

    return {};
}

/*
 * コンストラクタ
 * 数値xを初期値seedのLFSRでSNに変換し、値などを変数に登録
 * 複数のSNGでLFSRを共有する時のビットシフトに対応
*/
SN::SN(int x, int seed, int shift)
{
    // LFSRのためのmaskの設定
    mask = Define::N - 1;

    bitset<N> input = SN::SNG(x, seed, shift);
    sn = input;
    nume = (double)x;
    deno = N;
    val = (double)input.count() / (double)N;
} 

/*
 * 数値xを初期値seedのLFSRでSNに変換
 * 上記の初期化の際に用いる
 * 複数のSNGでLFSRを共有する時のビットシフトに対応
*/
bitset<SN::N> SN::SNG(int x, int seed, int shift)
{
    bitset<N> sn;
    int lfsr = seed;
    int set0 = 1;
    int shift_lfsr; // ビットシフト後の値

    // 最長LFSRの構成において、XORの入力へ繋がるビットの設定
    vector<int> seq = get_seq(N);

    set_shift(shift); // ビットシフト用の値の設定

    for (int i = 0; i < N; i++) {
        shift_lfsr = bit_shift(lfsr, shift);

        if (x > shift_lfsr) {
            sn.set(i);
        }

        bool t_bit = (lfsr & seq[0]) != 0;
        for (int j = 1; j < seq.size(); j++) {
            bool s_bit = (lfsr & seq[j]) != 0;
            t_bit = t_bit ^ s_bit;
        }
        lfsr = lfsr << 1;
        if (t_bit) {
            lfsr = lfsr | 1;
        }
    }
    return sn;
}

/*
 * ビットシフト用の値の設定
*/
void SN::set_shift(int shift)
{
    shift1 = pow(2.0, shift) - 1;     shift2 = mask - shift1;
    shift3 = shift1 << (B - shift);  shift4 = mask - shift3;
}

/*
 * LFSRから出力された乱数をビットシフトする
*/
int SN::bit_shift(int lfsr, int shift)
{
    int lfsr1, lfsr2, shift_lfsr;
    lfsr = lfsr & mask;

    if (shift == 0) {
        shift_lfsr = lfsr;
    }
    else {
        lfsr1 = lfsr & shift1;          lfsr2 = lfsr & shift2;
        lfsr1 = lfsr1 << (B - shift);   lfsr2 = lfsr2 >> shift;
        lfsr1 = lfsr1 & shift3;         lfsr2 = lfsr2 & shift4;
        shift_lfsr = lfsr1 | lfsr2;
    }

    return shift_lfsr;
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