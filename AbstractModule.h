#include "SN.h"
#include <vector>

class AbstractModule
{
private:
    // 入力の1の数
    unsigned int _input1;
    unsigned int _input2;

    // 出力の1の数
    unsigned int _output;

    // nextが呼ばれた回数
    unsigned int _time;

    // 誤差
    double _err;

public:
    AbstractModule();
    virtual ~AbstractModule() = default;

    // 逐次実行
    virtual bool next(bool input1, bool input2);
};

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

void Div()
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