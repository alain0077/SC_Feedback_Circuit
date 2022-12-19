#include "Random.h"

using namespace std;
using dist_type = std::uniform_int_distribution<>;

Random::Random()
{
    // Initialize the generator with Hardware Random Seed
    random_device rnd;
    _mt.seed(rnd());

    // Reset the state of normal_distribution.
    _dist.reset();
    
    // Initialize the range from 1 to N - 1.
    dist_type::param_type param(1, Define::N - 1);
    _dist.param(param);
}

void Random::range(int min, int max)
{
    // Set the range from min to max.
    _dist.param(dist_type::param_type(min, max));
}

void Random::seed(unsigned int seed)
{
    // Set the seed
    _mt.seed(seed);
}