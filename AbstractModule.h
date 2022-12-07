#pragma once

#include "SN.h"
#include <vector>

class AbstractModule
{
public:
    AbstractModule(std::vector<SN*> SNs);
    ~AbstractModule();
    void update();
};