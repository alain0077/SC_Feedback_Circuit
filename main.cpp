#define _CRT_SECURE_NO_WARNINGS

#include "SN.h"
#include "Random.h"
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
    int N = 8;
    const int B = 3;

    random_device rnd;
    //mt19937 mt(rnd());
    mt19937 mt((unsigned int)time(NULL));
    uniform_int_distribution<> randN(1, N - 1);

    unsigned int sr = randN(mt);

    //cout << bitset<B>(lfsr) << endl;

    vector<int> list = { 1 };

    map<int, int> test;

    for(int i = 0; i < N; i++) {
        cout << bitset<B>(sr) << endl;

        // 最下位ビットを抽出
        int lsb = sr & 1;

        // 1ビット右シフト
        sr >>= 1;

        // 上位にビットに最下位ビットを挿入
        sr |= (lsb << (B - 1));

        // 配置したxorについて演算する
        for (auto l : list) sr ^= (lsb << l);
    }

    return 0;
}