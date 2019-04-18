#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>
#include <string>

class Calculation
{
public:
    Calculation(std::string str);
    Calculation(const char *c);
    double operator()(double input) const;
    bool valid() const { return status; }

private:
    bool status;
    int addition[4];
};

#endif // CALCULATION_H
