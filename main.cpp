#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <random>
#include <math.h>
#include <fstream>
//#include <algorithm>

using namespace std;

/*
  SNを2の乗数とするかどうかを決定
  例えば、0なら1023、1なら1024ビットの精度
*/
#define ins0 1

// LFSRのビット数:B、SNのビット長:N を決定
#define N 1024
#define B 10

// 最長LFSRの構成において、XORの入力へ繋がるビットの設定
#if N == 4 || N == 3
int seq[] = { 1 << 1, 1 };
#endif
#if N == 8 || N == 7
int seq[] = { 1 << 2, 1 << 1 };
#endif
#if N == 16 || N == 15
int seq[] = { 1 << 3, 1 << 2 };
#endif
#if N == 32 || N == 31
int seq[] = { 1 << 4, 1 << 2 };
#endif
#if N == 64 || N == 63
int seq[] = { 1 << 5, 1 << 4 };
#endif
#if N == 128 || N == 127
int seq[] = { 1 << 6, 1 << 5 };
#endif
#if N == 256 || N == 255
int seq[] = { 1 << 7, 1 << 5, 1 << 4, 1 << 3 };
#endif
#if N == 512 || N == 511
int seq[] = { 1 << 8, 1 << 4 };
#endif
#if N == 1024 || N == 1023
int seq[] = { 1 << 9, 1 << 6 };
#endif
#if N == 2048 || N == 2047
int seq[] = { 1 << 10, 1 << 8 };
#endif
#if N == 4096 || N == 4095
int seq[] = { 1 << 11, 1 << 10, 1 << 9, 1 << 3 };
#endif
#if N == 8192 || N == 8191
int seq[] = { 1 << 12, 1 << 11, 1 << 10, 1 << 7 };
#endif

#if ins0 == 0
int mask = N;
#endif
#if ins0 == 1
int mask = N - 1;
#endif

// 乱数を生成
int RAND()
{
    int rand;

    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randN(1, N - 1);  //生成する乱数の値の範囲
    rand = randN(mt);

    return rand;
}

// 乱数を生成
double RAND3()
{
    double rand;

    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_real_distribution<double> randN(0.4, 0.6);  //生成する乱数の値の範囲
    rand = randN(mt);

    return rand;
}

// 0 or 1をランダムに生成
int RAND01()
{
    int rand;

    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randN(0, 1);  // 乱数を生成 
    rand = randN(mt);

    return rand;
}

// 0-3をランダムに生成
int RAND03()
{
    int rand;

    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randN(0, 3);  // 乱数を生成 
    rand = randN(mt);

    return rand;
}

/*
  Stochastic Numberのクラス
*/
class SN {
    bitset<N> sn;  // SNのビット列
    double val;    // SNの値
    double nume;   // 本来の分子の値
    int deno;      // 分母の値

    // ビットシフト用の値
    int shift1;  int shift2;  int shift3;  int shift4;

public:

    /*
      デフォルトコンストラクタ
      行いたい処理はないが、書かないとコンパイルできない
    */
    SN() {}

    /*
      コンストラクタ
      数値xを初期値seedのLFSRでSNに変換し、値などを変数に登録
      複数のSNGでLFSRを共有する時のビットシフトに対応
    */
    SN(int x, int seed, int shift)
    {
        bitset<N> input = this->SNG(x, seed, shift);
        this->sn = input;
        this->nume = (double)x;
        this->deno = N;
        this->val = (double)input.count() / (double)N;
    }

    /*
      数値xを初期値seedのLFSRでSNに変換
      上記の初期化の際に用いる
      複数のSNGでLFSRを共有する時のビットシフトに対応
    */
    bitset<N> SNG(int x, int seed, int shift)
    {
        bitset<N> sn;
        int lfsr = seed;
        int set0 = 1;
        int shift_lfsr; // ビットシフト後の値

        set_shift(shift); // ビットシフト用の値の設定

        for (int i = 0; i < N; i++) {
            shift_lfsr = bit_shift(lfsr, shift);

#if ins0 == 0
            if (x >= shift_lfsr) {
                sn.set(i);          // iビット目を0(or1)にする                                        
            }
#endif
#if ins0 == 1
            if (x > shift_lfsr) {
                sn.set(i);
            }
#endif

            bool t_bit = (lfsr & seq[0]) != 0;
            for (int j = 1; j < sizeof(seq) / sizeof(int); j++) {
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
      ビットシフト用の値の設定
    */
    void set_shift(int shift)
    {
        shift1 = pow(2.0, shift) - 1;     shift2 = mask - shift1;
        shift3 = shift1 << (B - shift);  shift4 = mask - shift3;
    }

    /*
      LFSRから出力された乱数をビットシフトする
    */
    int bit_shift(int lfsr, int shift)
    {
        int lfsr1, lfsr2, shift_lfsr;
        lfsr = lfsr & mask;

        if (shift == 0) {
            shift_lfsr = lfsr;
        }
        else {
            lfsr1 = lfsr & shift1;         lfsr2 = lfsr & shift2;
            lfsr1 = lfsr1 << (B - shift);  lfsr2 = lfsr2 >> shift;
            lfsr1 = lfsr1 & shift3;        lfsr2 = lfsr2 & shift4;
            shift_lfsr = lfsr1 | lfsr2;
        }

        return shift_lfsr;
    }

    /*
      乗算を行う
      乗算した結果（ビット列SN、SNの値、正しい値を計算するための分子・分母）をメンバ変数に代入
    */
    SN operator&(SN sn2)
    {
        SN output;

        bitset<N> input1 = this->sn;
        bitset<N> input2 = sn2.sn;
        output.sn = input1 & input2;
        output.val = (double)output.sn.count() / (double)N;
        output.nume = (this->nume * sn2.nume) / (double)N;
        output.deno = N;

        return output;
    }

    /*
      ORゲートによる加算を行う
      加算した結果（ビット列SN、SNの値、正しい値を計算するための分子・分母）をメンバ変数に代入
    */
    SN operator|(SN sn2)
    {
        SN output;

        bitset<N> input1 = this->sn;
        bitset<N> input2 = sn2.sn;
        output.sn = input1 | input2;
        output.val = (double)output.sn.count() / (double)N;
        output.nume = (this->nume + sn2.nume);
        output.deno = N;

        return output;
    }

    /*
    * NSAddによる飽和加算を行う
    * 加算した結果（ビット列SN、SNの値、正しい値を計算するための分子・分母）をメンバ変数に代入
    */
    SN operator+(SN sn2)
    {
        SN output;

        bitset<N> input1 = this->sn;
        bitset<N> input2 = sn2.sn;

        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < N; i++) {
            sum1 += input1[i] + input2[i];

            if (sum1 > sum2) {
                output.sn[i] = 1;
                sum2++;
            }
            else output.sn[i] = 0;
        }

        output.val = (double)output.sn.count() / (double)N;
        output.nume = (this->nume + sn2.nume);
        output.deno = N;

        return output;
    }

    /*
      指定したSNの否定形(1-x)を生成
      結果（ビット列SN、SNの値、正しい値を計算するための分子・分母）をメンバ変数に代入
    */
    SN not_SN()
    {
        SN output;

        bitset<N> input1 = this->sn;
        bitset<N> input2 = ~input1;
        output.sn = input2;
        output.nume = (double)N - this->nume;
        output.deno = N;
        output.val = (double)input2.count() / (double)N;

        return output;
    }

    /*
      SNの複製を行う
    */
    SN dup_RRR(int seed, int shift)
    {
        bitset<1> FF1, FF2;
        FF1 = RAND01();
        FF2 = RAND01();
        bitset<N> ctrl = SNG(N / 2, seed, shift);  //制御入力は値が1/2のSN

        bitset<N> input = this->sn;
        bitset<N> output1, output2;

        // FF1の方の処理
        for (int i = 0; i < N; i++) {
            // ctrl = 1ならFF1を出力
            output1[i] = ctrl[i] ? FF1[0] : input[i];
            if (ctrl[i] == 1) {
                FF1[0] = input[i];
            }
        }

        // FF2の方の処理
        for (int i = 0; i < N; i++) {
            // ctrl = 0ならFF2を出力
            output2[i] = ctrl[i] ? input[i] : FF2[0];
            if (ctrl[i] == 0) {
                FF2[0] = input[i];
            }
        }

        SN output;
        for (int i = 0; i < N; i++) {
            // ctrl = 1ならoutput1を出力
            output.sn[i] = ctrl[i] ? output1[i] : output2[i];
        }
        output.val = (double)output.sn.count() / (double)N;
        output.nume = this->nume;
        output.deno = N;

        return output;
    }

    /*
      加算を行う
      gが加算したいSN
      また、自動的に初期値seedのLFSRで1/2の値のSNを生成し、制御入力とする
      加算した結果（ビット列SN、SNの値、正しい値を計算するための分子・分母）をメンバ変数に代入
      複数のSNGでLFSRを共有する時のビットシフトに対応
    */
    SN mux(SN sn2, int seed, int shift)
    {
        SN output;
        bitset<N> ctrl = SNG(N / 2, seed, shift);  //制御入力は値が1/2のSN  

        //cout << ctrl << endl;

        bitset<N> input1 = this->sn;
        bitset<N> input2 = sn2.sn;
        for (int i = 0; i < N; i++) {
            output.sn[i] = ctrl[i] ? input2[i] : input1[i];
        }

        output.val = (double)output.sn.count() / (double)N;
        output.nume = (this->nume + sn2.nume) / (double)2;
        output.deno = N;

        return output;
    }

    // 保持しているSNとその値を表示 
    void print_bs()
    {
        cout << this->sn << " = " << this->sn.count() << "/" << N << " = " << this->val << endl;
    }

    /*
      ・これまで行った演算の正確な値
      ・実際に演算された値
      ・誤差
      上記三つを表示
    */
    void print_ans()
    {
        double ans = this->nume / (double)this->deno;
        cout << "ans: " << ans << endl;
        cout << "val: " << val << endl;
        cout << "err: " << this->val - ans << endl;
    }

    /*
      ・print_bs();
      ・print_ans();
      上記二つを実行
    */
    void print()
    {
        this->print_bs();
        this->print_ans();
        cout << endl;
    }

    // SNを取得
    bitset<N> get_out()
    {
        return this->sn;
    }

    // SNの値を取得
    double get_val()
    {
        return this->val;
    }

    // 2つのSNの相関の強さを取得
    double SCC(SN sn2)
    {
        bitset<N> input1 = this->sn;
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
};

/*
* Div
*/
void div()
{
    //演算結果を書き込むファイル
    FILE* fp = fopen("Method_Div.csv", "w");
    if (fp == NULL) {
        cout << "miss" << endl;
    }

    for (int t = 0; t < 1; ++t) {
        cout << t << endl;             // 回数
        int ran1 = RAND();         // LFSRの初期値
        int ran2 = RAND();         // LFSRの初期値

        double times = 0;
        double sum_ans = 0;  // 正確な演算結果の合計
        double sum_err_m1 = 0, sum_err_m2 = 0, sum_err_m3 = 0, sum_err_m4 = 0;  // 演算誤差の合計
        double percent_m1 = 0, percent_m2 = 0, percent_m3 = 0, percent_m4 = 0;  // エラー率の合計

        double err_max1 = 0, err_max2 = 0, err_max3 = 0;

        /*
        * 演算を行う
        * iが演算式におけるxの値の分子 (x = i/N)
        * N=1024の場合、x = 1/1024,2/1024,...,1023/1024の場合を全て演算する
        */
        for (int i = 2; i < N; i++) {
            for (int j = 1; j < i; j++) {
                /*
                * 実際の演算結果を求める
                */
                double x = (double)i / (double)N;  // xの値
                double y = (double)j / (double)N;  // yの値
                double ans = y / x;  // 除算
                //sum_ans += ans;

                //入力
                SN p1(i, ran1, 2);
                SN p2(j, ran1, 2);
                SN p3(j, ran2, 0);

                /*
                double r = ((double)j / (double)N) / ((double)i / (double)N);
                int tmp = r * (double)N;

                //SNへの変換
                SN p_div(tmp, RAND(), 1);
                */

                double err = 0;  double per = 0;

                /*
                * 提案手法 ( NSAdd )
                */
                //emitの出力
                bitset<N + 1> emit;
                emit[0] = 0;
                
                //NS Addの出力
                bitset<N> nsadd;
                
                //Accumlaterの初期化
                int sum1 = 0, sum2 = 0;

                for (int k = 0; k < N; k++) {
                    sum1 += p3.get_out()[k] + emit[k];

                    if (sum1 > sum2) {
                        nsadd[k] = 1;
                        sum2++;
                    }
                    else nsadd[k] = 0;
                    
                    emit[k + 1] = nsadd[k] && (!p1.get_out()[k]);
                }

                err = (double)nsadd.count() / (double)N;
                err -= ans;   // 誤差
                err_max1 = max(err_max1, abs(err));
                sum_err_m1 += abs(err);         // 絶対誤差
                //fprintf(fp, "%f\n", (double)nsadd.count() / (double)N);
                per = err / ans;              // エラー率
                percent_m1 += abs(per);         // 絶対二乗エラー率

                /*
                * 提案手法 ( JK-FF )
                */
                //calculateの出力
                bool cal = false;

                /*
                * JK-FF
                * 真理値表
                * J=0,K=0でQを保持
                * J=0,K=1でQを0
                * J=1,K=0でQを1
                * J=1,K=1でQを反転
                */
                bitset<N> JK;
                bool Q = false;

                for (int k = 0; k < N; k++) {
                    if (!cal && !p3.get_out()[k]) JK[k] = Q;
                    if (!cal && p3.get_out()[k]) JK[k] = 0;
                    if (cal && !p3.get_out()[k]) JK[k] = 1;
                    if (cal && p3.get_out()[k]) JK[k] = !Q;

                    Q = JK[k];

                    cal = !JK[k] && p1.get_out()[k];
                }
                err = 1.0 - ((double)JK.count() / (double)N);
                err -= (ans / 2.0);   // 誤差
                err_max2 = max(err_max2, abs(err));
                sum_err_m2 += abs(err);        // 二乗誤差
                //fprintf(fp, "%f\n", (double)nsadd.count() / (double)N);
                per = err / ans;              // エラー率
                percent_m2 += abs(per);        // 二乗エラー率
                
                /*
                * CORDIV
                */
                //MUX
                bitset<N> mux;

                //D-FF
                int d = 0;

                for (int k = 0; k < N; k++) {
                    
                    mux[k] = p1.get_out()[k]? p2.get_out()[k] : d;

                    d = mux[k];
                }

                err = (double)mux.count() / (double)N;
                err -= ans;   // 誤差
                err_max3 = max(err_max3, abs(err));
                sum_err_m3 += abs(err);        // 絶対誤差
                //fprintf(fp, "%f\n", (double)z.count() / (double)N);
                per = err / ans;              // エラー率
                percent_m3 += abs(per);        // 絶対エラー率

                times++;
            }
            /*/*
            sum_err_m1 = sum_err_m1 / times;    //sum_err_m1 = sqrt(sum_err_m1);  // 平均誤差
            percent_m1 = percent_m1 / times;  //percent_m1 = sqrt(percent_m1);  // 平均エラー率
            sum_err_m2 = sum_err_m2 / times;  //sum_err_m2 = sqrt(sum_err_m2);  // 平均誤差
            percent_m2 = percent_m2 / times;  //percent_m2 = sqrt(percent_m2);  // 平均エラー率
            sum_err_m3 = sum_err_m3 / times;  //sum_err_m3 = sqrt(sum_err_m3);  // 平均誤差
            percent_m3 = percent_m3 / times;  //percent_m3 = sqrt(percent_m3);  // 平均エラー率

            fprintf(fp, "%d,", i);
            fprintf(fp, "%f,", sum_err_m1);
            fprintf(fp, "%f,", sum_err_m2);
            fprintf(fp, "%f,", sum_err_m3);
            fprintf(fp, "%f,", percent_m1);
            fprintf(fp, "%f,", percent_m2);
            fprintf(fp, "%f,", percent_m3);
            fprintf(fp, "%f,", err_max1);
            fprintf(fp, "%f,", err_max2);
            fprintf(fp, "%f\n", err_max3);

            err_max1 = 0;
            err_max2 = 0;
            err_max3 = 0;
            times = 0;
            sum_err_m1 = 0, sum_err_m2 = 0, sum_err_m3 = 0, sum_err_m4 = 0;  // 演算誤差の合計
            percent_m1 = 0, percent_m2 = 0, percent_m3 = 0, percent_m4 = 0;  // エラー率の合計
        }
        /*/
        }
        //Method1の結果
        sum_err_m1 = sum_err_m1 / times;  //sum_err_m1 = sqrt(sum_err_m1);  // 平均誤差
        percent_m1 = percent_m1 / times;  //percent_m1 = sqrt(percent_m1);  // 平均エラー率
        fprintf(fp, "\n");
        fprintf(fp, " Method1,");
        fprintf(fp, "%f,", sum_err_m1);
        fprintf(fp, "%f,", percent_m1);
        fprintf(fp, "%f\n", err_max1);

        //Method2の結果
        sum_err_m2 = sum_err_m2 / times;  //sum_err_m2 = sqrt(sum_err_m2);  // 平均誤差
        percent_m2 = percent_m2 / times;  //percent_m2 = sqrt(percent_m2);  // 平均エラー率
        fprintf(fp, "\n");
        fprintf(fp, " Method2,");
        fprintf(fp, "%f,", sum_err_m2);
        fprintf(fp, "%f,", percent_m2);
        fprintf(fp, "%f\n", err_max2);

        //CORDIVの結果
        sum_err_m3 = sum_err_m3 / times;  //sum_err_m3 = sqrt(sum_err_m3);  // 平均誤差
        percent_m3 = percent_m3 / times;  //percent_m3 = sqrt(percent_m3);  // 平均エラー率
        fprintf(fp, "\n");
        fprintf(fp, " Method3,");
        fprintf(fp, "%f,", sum_err_m3);
        fprintf(fp, "%f,", percent_m3);
        fprintf(fp, "%f\n", err_max3);
        /**/

        fclose(fp);
    }
}


/*
  MUX 
*/
void mux(int mode)
{
    //演算結果を書き込むファイル
    FILE* fp = fopen("Method_MUX.csv", "w");
    if (fp == NULL) {
        cout << "miss" << endl;
    }

    for (int t = 0; t < 1; ++t) {
        cout << t << endl;             // 回数
        int ran1 = RAND();         // LFSRの初期値
        int ran2 = RAND();

        int times = 0;
        double sum_ans = 0;  // 正確な演算結果の合計
        double sum_err_m1 = 0, sum_err_m2 = 0, sum_err_m3 = 0, sum_err_m4 = 0;  // 演算誤差の合計
        double percent_m1 = 0, percent_m2 = 0, percent_m3 = 0, percent_m4 = 0;  // エラー率の合計
        /*
        * 演算を行う
        * iが演算式におけるxの値の分子 (x = i/N)
        * N=1024の場合、x = 1/1024,2/1024,...,1023/1024の場合を全て演算する
        */
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < N; j++) {
                /*
                * 実際の演算結果を求める
                */
                double x_ans = (double)i / (double)N;  // xの値
                double y_ans = (double)j / (double)N;  // yの値
                double ans = x_ans + y_ans;  // xの平方根の値
                sum_ans += ans;

                //入力
                SN p1(i, ran1, 2);
                SN p2(j, ran2, 5);

                double err = 0;  double per = 0;
                //fprintf(fp, "%f,", p_root.get_val());

                SN output = p1.mux(p2, RAND(), 0);

                err = output.get_val() * 2 - ans;   // 誤差
                sum_err_m1 += err * err;        // 二乗誤差
                //fprintf(fp, "%f,", output.get_val());
                per = err / ans;              // エラー率
                percent_m1 += per * per;        // 二乗エラー率

                times++;
            }
        }

        sum_err_m1 = sqrt(sum_err_m1);  sum_err_m1 = sum_err_m1 / times;  // 平均誤差
        percent_m1 = percent_m1 / times;  percent_m1 = sqrt(percent_m1);  // 平均エラー率
        fprintf(fp, "\n");
        fprintf(fp, " Method1,");
        fprintf(fp, "%f,", sum_err_m1);
        fprintf(fp, "%f,", percent_m1);
        fprintf(fp, "%f\n", sum_ans);
    }
}

void test()
{
    int i = 1023;
    //int j = 0;

    double times = 0;
    double sum_err_m = 0;  // 演算誤差の合計
    double percent_m = 0;  // エラー率の合計
    double err_max = 0;
    double err = 0;  double per = 0;

    FILE* fp = fopen("test.csv", "w");
    if (fp == NULL) {
        cout << "miss" << endl;
    }

    for (int j = 1; j < i; j++) {

        /*
        * 実際の演算結果を求める
        */
        double x = (double)i / (double)N;  // xの値
        double y = (double)j / (double)N;  // yの値
        double ans = y / x;  // 除算
        //sum_ans += ans;

        //入力
        SN p1(i, RAND(), 2);
        SN p3(j, RAND(), 0);

        /*
        * JK-FF
        * 真理値表
        * J=0,K=0でQを保持
        * J=0,K=1でQを0
        * J=1,K=0でQを1
        * J=1,K=1でQを反転
        */
        bitset<N> JK;
        bool Q = false;

        //calculateの出力
        bool cal = false;

        for (int k = 0; k < N; k++) {
            if (!cal && !p3.get_out()[k]) JK[k] = Q;
            if (!cal && p3.get_out()[k]) JK[k] = 0;
            if (cal && !p3.get_out()[k]) JK[k] = 1;
            if (cal && p3.get_out()[k]) JK[k] = !Q;

            Q = JK[k];

            cal = !JK[k] && p1.get_out()[k];
        }
        err = (1.0 - (double)JK.count() / (double)N);
        err *= 2.0;
        err -= ans;
        fprintf(fp, "%d,", j);
        fprintf(fp, "%f,", ans);
        fprintf(fp, "%f,", abs(err)/1.0);
        fprintf(fp, "%f,", ((double)JK.count() / (double)N));
        fprintf(fp, "%f,", ((double)1.0 - (double)JK.count() / (double)N));
        fprintf(fp, "%f\n", ((double)1.0 - (double)JK.count() / (double)N) * 2.0);
    }

    //err = ((double)1.0 - (double)JK.count() / (double)N) - ans;   // 誤差
    //err_max = max(err_max, abs(err));
    //sum_err_m += abs(err);        // 二乗誤差
    //per = err / ans;              // エラー率
    //percent_m += abs(per);        // 二乗エラー率
}

int main()
{
    /*/*/
    test();
    /*/
    div();
    /**/
    
    //mux(mode);

    return 0;
}