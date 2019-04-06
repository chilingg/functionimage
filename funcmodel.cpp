#include "funcmodel.h"

funcModel::funcModel(funcModel::Calculation func, const unsigned length):
    xBegin(-length/2),
    xEnd(length/2),
    imageNumber(1),
    funcImages()
{
    addImage(func);
}

void funcModel::buildImage(FuncImage &image)
{
    for(int i = xBegin; i <= xEnd; ++i)
    {
        image.second[i] = image.first(i);
    }
}

constexpr float funcModel::maxX;
constexpr unsigned funcModel::maxImageNumber;
