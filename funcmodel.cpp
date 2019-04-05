#include "funcmodel.h"

funcModel::funcModel(funcModel::Calculation func, unsigned length):
    xBegin(-length/2),
    xEnd(length/2),
    calFunc(func),
    imageNumber(1),
    funcImages()
{
    addImage();
}

void funcModel::buildImage(funcModel::Coordinates &image)
{
    for(int i = xBegin; i <= xEnd; ++i)
    {
        image[i] = calFunc(i);
    }
}

constexpr float funcModel::maxX;
constexpr unsigned funcModel::maxImageNumber;
