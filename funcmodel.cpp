#include "funcmodel.h"

FuncModel::FuncModel(const Calculation func, const int begin, const int end):
    xBegin(begin),
    xEnd(end),
    funcImages(std::make_pair(func, Coordinates()))
{
    for(int i = xBegin; i < xEnd; ++ i)
        funcImages.second[i] = funcImages.first(i);
}
