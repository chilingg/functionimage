#ifndef FUNCMODEL_H
#define FUNCMODEL_H

#include <map>
#include <vector>
#include <QPointF>
#include <utility>
#include "calculation.h"

class FuncModel
{
    using Coordinates = std::map<int, double>;
    using FuncImage = std::pair<Calculation, Coordinates>;

public:
    explicit FuncModel(const Calculation func, const int begin = -2000, const int end = 2000);
    double yValue(int x) const;

private:
    const int xBegin;
    const int xEnd;

    FuncImage funcImages;
};

inline double FuncModel::yValue(int x) const
{
    auto iter = funcImages.second.find(x);

    if(iter != funcImages.second.end())
        return iter->second;

    return 0.0;
}

#endif // FUNCMODEL_H
