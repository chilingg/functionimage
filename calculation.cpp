#include "calculation.h"
#include <QDebug>

double Calculation::operator()(double in) const
{
    double out = b;

    if(!polynomials.empty())
    {
        for(auto pt : polynomials)
        {
            double polynomialsX = in;

            for(int i = 1; i < pt.first; ++i)
                polynomialsX *= in;

            polynomialsX *= pt.second;
            qDebug() << b << polynomialsX << pt.second << in;
            out += polynomialsX;
        }
    }

    return  out;
}

