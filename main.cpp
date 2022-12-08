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
    std::uniform_int_distribution<> randN(1, Define::N - 1);  //生成する乱数の値の範囲
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

int main()
{
    SN* sn1 = new SN(10,RAND(),3);

    sn1->print_bs();

    return 0;
}