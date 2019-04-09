#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>

using Polynomial = std::vector<std::pair<int, double>>;
class Calculation
{
public:
    explicit Calculation(double constant = 0, Polynomial pt = Polynomial()):
        b(constant),
        polynomials(pt)
    {}
    double operator()(double in) const;

private:
    double b;
    Polynomial polynomials;
};

#endif // CALCULATION_H
