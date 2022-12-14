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

    int rn1 = randN(mt);

    SN sn1 = SN(X, rn1, flag);
    SN sn2 = SN(X, rn1, flag);

    cout << sn1.SCC(sn2) << endl;

    int rn2 = randN(mt);

    SN sn3 = sn1.Regeneration(rn2, flag);

    cout << sn1.SCC(sn3) << endl;

    return 0;
}