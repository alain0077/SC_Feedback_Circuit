#include "Random.h"
#include "AbsError.h"
#include "Analysis.h"
#include "FeedbackCircuit.h"

#include "MyDiv.h"
#include "Calculation.h"

#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace SC;
using namespace Feedback;

int main()
{
    clock_t start = clock();    // スタート時間

    // // 乱数生成器  
    auto randN = Random();

    // 演算誤差などを記録するクラス
    Analysis ERR_FBDIV;
    Analysis ERR_CORDIV;
    
    for(int t = 0; t < 100; t++) {
        randN.seed((unsigned int)time(NULL));

        int rn1 = randN();
        int rn2 = randN();

        cout << rn1 << "=" << rn2 << endl;

        for (int i = 2; i < Define::N; i++) {
            SN sn1 = SN(i, rn1, 2);

            for (int j = 1; j < i; j++) {
                SN sn2 = SN(j, rn2, 0);
                SN sn3 = SN(j, rn1, 2);

                SN div1 = MyDiv(sn1, sn2);
                SN div2 = CORDIV(sn1, sn3);

                ERR_FBDIV.Update(div1.get_ans(), div1.get_val(), SCC(sn1, sn2));
                ERR_CORDIV.Update(div2.get_ans(), div2.get_val(),SCC(sn1, sn3));
            }
        }

        //cout << ERR_FBDIV.get_MAPE() << endl;
        //cout << ERR_CORDIV.get_MAPE() << endl;
    }

    cout << "Feedback" << endl;
    ERR_FBDIV.print_Summary();
    cout << endl;
    cout << "CORDIV" << endl;
    ERR_CORDIV.print_Summary();
    cout << endl;

    clock_t end = clock();     // 終了時間
    cout << (double)(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}