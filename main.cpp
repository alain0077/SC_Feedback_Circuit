#define _CRT_SECURE_NO_WARNINGS

#include "SN.h"
#include "Define.h"
#include <random>
#include <time.h>
#include <vector>
#include <fstream>
#include <iostream>

#include <map>

using namespace std;

int main()
{
    int flag = 1;
    int X = 4;
    int N = 1;

    double sum = 0.0;
    double n_max = 0.0, n_min = 1.0;
    int tmp1, tmp2;

    random_device rnd;
    mt19937 mt(rnd());
    //mt19937 mt((unsigned int)time(NULL));
    uniform_int_distribution<> randN(1, Define::N - 1);

    for(int i = 0; i < N; i++) {
        int rn1 = randN(mt);
        int rn2 = randN(mt);

        //cout << rn1 << ":" << rn2 << endl;

        SN* sn1 = new SN(X,rn1,flag);
        SN* sn2 = new SN(X,rn2,flag);

        auto scc = sn1->SCC(*sn2);

        if(n_max < abs(scc)) tmp1 = rn1, tmp2 = rn2;

        sum += abs(scc);
        n_min = min(n_min, abs(scc));
        n_max = max(n_max, abs(scc));

        if(abs(scc) == double(1)) cout << rn1 << ":" << rn2 << endl;
    }

    cout << sum / (double)N << endl;
    cout << "min : " << n_min << endl;
    cout << "max : " << n_max << endl;
    cout << tmp1 << ":" << tmp2 << endl;

    return 0;
}