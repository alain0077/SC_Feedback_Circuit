#include "SC.h"
#include "SN.h"
#include "Define.h"
#include "Random.h"
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace SC::Divison;

int main()
{
    clock_t start = clock();    // スタート時間

    //auto randN = Random();

    auto div1 = Feedback();
    auto div2 = CORDIV();

    for(int t = 0; t < 1; t++) {
        //randN.seed((unsigned int)time(NULL));

        int rn1 = Random()();
        int rn2 = Random()();

        for (int i = 2; i < Define::N; i++) {
            SN sn1 = SN(i, rn1, 2);

            for (int j = 1; j < i; j++) {
                SN sn2 = SN(j, rn2, 0);
                SN sn3 = SN(j, rn1, 2);

                div1(sn1, sn2);
                div2(sn1, sn3);
            }
        }

        //cout << div1.get_MAPE() << endl;
        //cout << div2.get_MAPE() << endl;
    }
    
    cout << "Feedback" << endl;
    div1.print_Summary();
    cout << "CORDIV" << endl;
    div2.print_Summary();

    clock_t end = clock();     // 終了時間
    cout << (double)(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}