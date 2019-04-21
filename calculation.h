#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>
#include <QString>

class Calculation
{
public:
    explicit Calculation(QString str);
    explicit Calculation(const char *c);
    double operator()(double input);
    bool valid() const { return status; }
    double calculating(QString &str);
    double popFristTermValue(QString &str);

private:
    QString funcStr;
    bool status;
    double x;
};

#endif // CALCULATION_H
