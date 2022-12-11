#include <random>

class Random
{
private:
    std::mt19937 mt;
    std::uniform_int_distribution<> randN;
    std::uniform_int_distribution<> rand01;

public:
    Random();
    int RAND();
    int RAND01();
};