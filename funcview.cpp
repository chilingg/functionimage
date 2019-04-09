#include "funcview.h"
#include <QPainter>

FuncView::FuncView(const Calculation func, const int length, QWidget *parent) :
    QWidget(parent),
    beginPoint(-length/2),
    endPoint(length/2),
    inModel(func, beginPoint, endPoint),
    scaleLevels{0.1, 1, 4, 8, 16},
    scaleLevel(1)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, {255, 255, 255});
    setAutoFillBackground((true));
    setPalette(pal);
}

void FuncView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setWindow(-width()/2, -height()/2, width(), height());
    int displayMinX = beginPoint < width()/2 ? beginPoint : -width()/2;
    int displayMaxX = endPoint < width()/2 ? endPoint : width()/2;

    painter.setPen(IMAGE_COLOR::LUMINOSITY_5_238);
    for(int i = -width()/2/10*10; i < width()/2; i += 10)
    {
        painter.drawLine(i, -height()/2, i, height()/2);
    }
    for(int i = -height()/2/10*10; i < height()/2; i += 10)
    {
        painter.drawLine(-width()/2, i, width()/2, i);
    }

    painter.setPen(IMAGE_COLOR::LUMINOSITY_4_204);
    painter.drawLine(0, -height()/2, 0, height()/2);
    painter.drawLine(-width()/2, 0, width()/2, 0);

    painter.setPen(IMAGE_COLOR::IC_RED);
    for(int i = displayMinX; i < displayMaxX; ++i)
    {
        painter.drawLine(i, static_cast<int>(inModel.yValue(i) * scaleLevels[scaleLevel]),
                         i+1, static_cast<int>(inModel.yValue(i+1) * scaleLevels[scaleLevel]));
    }
}
