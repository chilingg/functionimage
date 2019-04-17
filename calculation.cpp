#include "calculation.h"
#include <QDebug>
#include <regex>

using std::regex;
using std::regex_match;

Calculation::Calculation(std::string str):
    status(false)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    regex reg("[\\d+-/*()^]*x[\\d+-/*()x^]*");
    if(!regex_match(str, reg))
    {
        qDebug() << "Calculation:: unexpected character!";
        status = false;
    }

    qDebug() << str.c_str();
}

Calculation::Calculation(const char *c):
    Calculation(std::string(c))
{
    
}

double Calculation::operator()(double input) const
{
    return function(input);
}

