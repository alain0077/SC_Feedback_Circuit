#define _CRT_SECURE_NO_WARNINGS

#include "SN.h"
#include "Define.h"
#include <random>
#include <math.h>
#include <fstream>

using namespace std;

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