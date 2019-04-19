#ifndef FUNCVIEW_H
#define FUNCVIEW_H

#include <QWidget>
#include <QImage>
#include <list>
#include <utility>
#include "funcmodel.h"
#include <QDebug>

namespace IMAGE_COLOR {
    const QColor LUMINOSITY_0_0(0, 0, 0);	//Black

    //定义了一组五等三分的明度
    const QColor LUMINOSITY_1_17(17, 17, 17);
    const QColor LUMINOSITY_1_34(34, 34, 34);
    const QColor LUMINOSITY_1_51(51, 51, 51);

    const QColor LUMINOSITY_2_68(68, 68, 68);
    const QColor LUMINOSITY_2_85(85, 85, 85);
    const QColor LUMINOSITY_2_102(102, 102, 102);

    const QColor LUMINOSITY_3_119(119, 119, 119);
    const QColor LUMINOSITY_3_136(136, 136, 136);
    const QColor LUMINOSITY_3_153(153, 153, 153);

    const QColor LUMINOSITY_4_170(170, 170, 170);
    const QColor LUMINOSITY_4_187(187, 187, 187);
    const QColor LUMINOSITY_4_204(204, 204, 204);

    const QColor LUMINOSITY_5_221(221, 221, 221);
    const QColor LUMINOSITY_5_238(238, 238, 238);
    const QColor LUMINOSITY_5_255(255, 255, 255); //White

    const QColor IC_RED(255, 0, 0);
    const QColor IC_YELLOW(255, 255, 0);
    const QColor IC_GREEN(0, 255, 0);
    const QColor IC_CYAN(0, 255, 255);
    const QColor IC_BLUE(0, 0, 255);
    const QColor IC_MAGENTA(255, 0, 255);
    const QColor IC_LIGHTRED(255, 127, 127);
}

class FuncView : public QWidget
{
    Q_OBJECT
public:
    using FuncImage = std::pair<FuncModel, QColor>;
    explicit FuncView(QWidget *parent = nullptr);
    bool zoomin();
    bool zoomout();
    QPoint &getOffsetR();
    QPoint &getMousePosR();
    int getUnitSize() const;
    unsigned addModelImage(Calculation func = "", QColor color = IMAGE_COLOR::IC_RED);
    void removeModelImage(unsigned index);
    void clearModelImage();
    bool isInView(QPoint pos);
    void changeImageColor(unsigned index, QColor color);
    bool changeImageFunc(unsigned index, std::string str);
    FuncImage &getFuncImage(unsigned index);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void clearImageWipeCache();

    QPoint offset;
    std::vector<FuncImage> inModels;
    const int scales[5];
    unsigned level;
    QImage numbers[13];
    QPoint mousePos;

    bool gridOnOff;
    bool numberOnOff;

signals:

public slots:
};

inline bool FuncView::zoomin()
{
    if(level != sizeof(scales)/sizeof(unsigned)-1)
    {
        clearImageWipeCache();
        ++level;
        return  true;
    }
    return false;
}

inline bool FuncView::zoomout()
{
    if(level != 0)
    {
        clearImageWipeCache();
        --level;
        return  true;
    }
    return false;
}

inline QPoint &FuncView::getOffsetR()
{
    return offset;
}

inline QPoint &FuncView::getMousePosR()
{
    return mousePos;
}

inline int FuncView::getUnitSize() const
{
    return scales[level];
}

inline unsigned FuncView::addModelImage(Calculation func, QColor color)
{
    inModels.push_back({FuncModel(func), color});
    return inModels.size() - 1;
}

inline void FuncView::removeModelImage(unsigned index)
{
    auto it = inModels.begin();
    std::advance(it, index);
    inModels.erase(it);
}

inline void FuncView::clearModelImage()
{
    std::vector<FuncImage> temp;
    swap(inModels, temp);
}

inline bool FuncView::isInView(QPoint pos)
{
    pos = mapFromGlobal(pos);
    QRect imageViewRc(QPoint(0, 0), QPoint(width(), height()));
    //qDebug() << imageViewRc << pos << imageWidth << imageHeight;
    return imageViewRc.contains(pos);
}

inline void FuncView::changeImageColor(unsigned index, QColor color)
{
    inModels[index].second = color;
}

inline bool FuncView::changeImageFunc(unsigned index, std::string str)
{
    inModels[index].first.changeFunc(str);
    return inModels[index].first.valid();
}

#endif // FUNCVIEW_H
