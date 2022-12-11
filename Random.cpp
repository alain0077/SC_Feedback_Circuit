#include "Random.h"
#include "Define.h"
#include <time.h>

using namespace std;

Random::Random()
{
    mt = mt19937((unsigned int)time(NULL));
    randN = uniform_int_distribution<>(1, Define::N - 1);
    rand01 = uniform_int_distribution<>(0, 1);
}

int Random::RAND()
{
    return randN(mt);
}

int Random:: RAND01()
{
    return rand01(mt);
}