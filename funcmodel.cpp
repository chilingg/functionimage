#include "funcmodel.h"

FuncModel::FuncModel(const Calculation func):
    funcImages(std::make_pair(func, Coordinates())),
    status(func.valid())
{
}
