#ifndef FUNCMODEL_H
#define FUNCMODEL_H

#include <map>
#include <vector>
#include <QPointF>
#include <utility>

class funcModel
{
    using Calculation = float (*)(float);
    using Coordinates = std::map<int, float>;
    using FuncImage = std::pair<Calculation, Coordinates>;

public:
    funcModel(const Calculation func, const unsigned length);
    bool addImage(const Calculation func);
    bool removeImage(unsigned imageID);

private:
    void buildImage(FuncImage &image);
    static constexpr float maxX = 4000.0f;
    static constexpr unsigned maxImageNumber = 10;

    int xBegin;
    int xEnd;
    unsigned imageNumber;

    std::vector<FuncImage> funcImages;
};

inline bool funcModel::addImage(const Calculation func)
{
    if(imageNumber >= maxImageNumber)
        return false;

    funcImages.push_back(std::make_pair(func, Coordinates()));
    buildImage(funcImages.back());
    ++imageNumber;

    return true;
}

inline bool funcModel::removeImage(unsigned imageID)
{
    if(imageID >= imageNumber)
        return false;

    funcImages.erase(funcImages.begin()+imageID);
    return true;
}

#endif // FUNCMODEL_H
