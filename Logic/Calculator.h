#pragma once

#include "DataModel/Factory.h"

class Calculator
{
public:
    Calculator(Factory& factory);

    void calculate();

public:
    Factory& factory;
};
