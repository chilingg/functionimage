#include "calculation.h"

double Calculation::operator()(double input) const
{
    return function(input);
}

