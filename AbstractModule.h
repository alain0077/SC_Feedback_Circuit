#include "SN.h"
#include <vector>

class AbstractModule
{
public:
    AbstractModule() {};
    ~AbstractModule() {};
    virtual bool next(std::vector<bool> inputs);
};