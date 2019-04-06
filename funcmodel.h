#ifndef FUNCMODEL_H
#define FUNCMODEL_H

#include <map>
#include <vector>
#include <QPointF>
#include <utility>

using Calculation = float (*)(float);

class FuncModel
{
    using Coordinates = std::map<int, float>;
    using FuncImage = std::pair<Calculation, Coordinates>;

public:
    explicit FuncModel(const Calculation func, const unsigned length);
    void addImage(const Calculation func);
    bool removeImage(const unsigned imageID);

private:
    void buildImage(FuncImage &image);

    int xBegin;
    int xEnd;
    unsigned imageNumber;

    std::vector<FuncImage> funcImages;
};

inline void FuncModel::addImage(const Calculation func)
{
    funcImages.push_back(std::make_pair(func, Coordinates()));
    buildImage(funcImages.back());
    ++imageNumber;
}

inline bool FuncModel::removeImage(const unsigned imageID)
{
    if(imageID >= imageNumber)
        return false;

    funcImages.erase(funcImages.begin()+imageID);
    return true;
}

#endif // FUNCMODEL_H
