#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>

class Calculation
{
public:
    explicit Calculation(double (*func)(double)):function(func) {}
    double operator()(double input) const;

private:
    double (*function)(double);
};

#endif // CALCULATION_H
