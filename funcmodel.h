#ifndef FUNCMODEL_H
#define FUNCMODEL_H

#include <map>
#include <vector>
#include <QPointF>
#include <utility>

class funcModel
{
    using Coordinates = std::map<int, float>;
    using Calculation = float (*)(float);

public:
    funcModel(const Calculation func, unsigned length);
    bool addImage();
    bool removeImage(unsigned imageID);

private:
    void buildImage(Coordinates &image);
    static constexpr float maxX = 4000.0f;
    static constexpr unsigned maxImageNumber = 10;

    int xBegin;
    int xEnd;
    const Calculation calFunc;
    unsigned imageNumber;

    std::vector<Coordinates> funcImages;
};

inline bool funcModel::addImage()
{
    if(imageNumber >= maxImageNumber)
        return false;

    funcImages.push_back(Coordinates());
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
