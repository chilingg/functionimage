#include "funcview.h"
#include <QPainter>
#include <cmath>
#include <QDebug>

FuncView::FuncView(const Calculation func, QWidget *parent) :
    QWidget(parent),
    beginPoint(0),
    endPoint(0),
    offset(0, 0),
    inModel(func),
    scales{4, 8, 16, 32, 64},
    level(2)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, {255, 255, 255});
    setAutoFillBackground((true));
    setPalette(pal);
}

void FuncView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setWindow(-width()/2 + offset.x()*scales[level],
                      height()/2 + offset.y()*scales[level],
                      width(), -height());
    int displayMinX = -width()/2/scales[level]*scales[level] + offset.x()*scales[level];
    int displayMaxX = displayMinX + width();
    int displayMinY = -height()/2/scales[level]*scales[level] + offset.y()*scales[level];
    int displayMaxY = displayMinY + height();

    if(scales[level] > 4)
    {
        painter.setPen(QColor(245, 245, 245));
        for(int i = 0; i < width(); i += scales[level])
        {
            painter.drawLine(displayMinX+i, displayMinY, displayMinX+i, displayMaxY);
        }
        for(int i = 0; i < height(); i += scales[level])
        {
            painter.drawLine(displayMinX, displayMinY+i, displayMaxX, displayMinY+i);
        }
    }
/*
    int ruler = 3;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_68);
    for(int i = displayMinX/scales[level]/10*10*scales[level]; i < width()/2; i += 10*scales[level])
    {
        painter.drawLine(i, -ruler, i, ruler);
    }
    for(int i = displayMinY/scales[level]/10*10*scales[level]; i < height()/2; i += 10*scales[level])
    {
        painter.drawLine(-ruler, i, ruler, i);
    }*/

    int ruler = 1;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_102);
    for(int i = displayMinX; i < width()/2; i += scales[level])
    {
        painter.drawLine(i, -ruler, i, ruler);
    }
    for(int i = displayMinY; i < height()/2; i += scales[level])
    {
        painter.drawLine(-ruler, i, ruler, i);
    }

    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_68);
    painter.drawLine(0, displayMinY, 0, displayMaxY);
    painter.drawLine(displayMinX, 0, displayMaxX, 0);
    qDebug() << displayMinX << displayMaxX;

    painter.setPen(IMAGE_COLOR::IC_RED);
    for(int i = displayMinX; i < displayMaxX; ++i)
    {
        int coor = i + offset.x()*scales[level];
        double di = static_cast<double>(coor);
        double temp = inModel.yValue(di/scales[level]) * scales[level];
        if(std::isnan(temp))
        {
            qDebug() << "NaN in startY!";
            continue;
        }
        int startY = static_cast<int>(temp);
        static int ignore = 0;
        if(startY < -height()/2)
        {
            ignore = -height()/2;
            continue;
        }
        else if(startY > height()/2)
        {
            ignore = height()/2;
            continue;
        }

        int endY;
        temp = inModel.yValue((di+1.0)/scales[level]) * scales[level];
        if(std::isinf(temp))
            temp > 0.0 ? endY = height()/2 : endY = -height()/2;
        else if(std::isnan(temp))
        {
            qDebug() << "NaN in endY!";
            continue;
        }
        else
        {
            endY = static_cast<int>(temp);
            if(endY < -height()/2)
            {
                endY = -height()/2;
            }
            else if(endY > height()/2)
            {
                endY = height()/2;
            }
        }

        if(ignore != 0)
        {
            painter.drawLine(coor-1, ignore, coor, startY);
            ignore = 0;
        }
        painter.drawLine(coor, startY, coor+1, endY);
    }
}
