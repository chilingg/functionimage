#ifndef FUNCMODEL_H
#define FUNCMODEL_H

#include <map>
#include <vector>
#include <QPointF>
#include <utility>
#include "calculation.h"

class FuncModel
{
    using Coordinates = std::map<double, double>;
    using FuncImage = std::pair<Calculation, Coordinates>;

public:
    explicit FuncModel(const Calculation func);
    double yValue(double x);
    void wipeCacheImage();
    bool valid() const { return status; }

private:
    FuncImage funcImages;
    bool status;
};

inline double FuncModel::yValue(double x)
{
    auto iter = funcImages.second.find(x);

    if(iter != funcImages.second.end())
        return iter->second;

    funcImages.second[x] = funcImages.first(x);
    return funcImages.second[x];
}

inline void FuncModel::wipeCacheImage()
{
    //Coordinates emptyCoors = Coordinates();
    //funcImages.second.swap(emptyCoors);
    funcImages.second.clear();
}

#endif // FUNCMODEL_H
