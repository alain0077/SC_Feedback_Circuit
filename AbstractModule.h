#include "SN.h"
#include <vector>

class AbstractModule
{
public:
    AbstractModule() {};
    ~AbstractModule() {};
    virtual void update();
};