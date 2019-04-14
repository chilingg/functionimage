#include "funcview.h"
#include <QPainter>
#include <cmath>
#include <QDebug>

FuncView::FuncView(QWidget *parent) :
    QWidget(parent),
    beginPoint(0),
    endPoint(0),
    offset(0, 0),
    inModels(),
    scales{4, 8, 16, 32, 64},
    level(2),
    gridOnOff(true),
    rulerOnOff(true),
    numberOnOff(true)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, IMAGE_COLOR::LUMINOSITY_5_255);
    setAutoFillBackground((true));
    setPalette(pal);
}

void FuncView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int rulerSpace = 0;
    if(rulerOnOff)
        rulerSpace = 18;

    painter.setWindow(-width()/2 + offset.x()*scales[level] - rulerSpace,
                      height()/2 + offset.y()*scales[level] + rulerSpace,
                      width(), -height());
    int imageWidth = width() - rulerSpace;
    int imageHeight = height() - rulerSpace;
    int leftX = -imageWidth/2/scales[level]*scales[level] - scales[level] + offset.x()*scales[level];
    int rightX = leftX + imageWidth + scales[level];
    int bottomY = -imageHeight/2/scales[level]*scales[level] - scales[level] + offset.y()*scales[level];
    int topY = bottomY + imageHeight + scales[level];

    //qDebug() << bottomY << topY << leftX << rightX;
    if(scales[level] > 4 && rulerOnOff)
    {
        painter.setPen(IMAGE_COLOR::LUMINOSITY_5_238);
        for(int i = 0; i < imageWidth+scales[level]; i += scales[level])
        {
            painter.drawLine(leftX+i, bottomY, leftX+i, topY);
        }
        for(int i = 0; i < imageHeight+scales[level]; i += scales[level])
        {
            painter.drawLine(leftX, bottomY+i, rightX, bottomY+i);
        }
    }

    if(rulerOnOff)
    {
        int viewLX = leftX - rulerSpace;
        int viewLT = topY + rulerSpace;
        painter.setPen(IMAGE_COLOR::LUMINOSITY_2_102);
        painter.drawRect(leftX, topY, scales[level], scales[level]);
        //painter.drawRect(viewLX, topY, width(), rulerSpace);
    }

    int ruler = 1;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_102);
    for(int i = 0; i < imageWidth/scales[level]+2; ++i)
    {
        painter.drawLine(i*scales[level]+leftX, -ruler, i*scales[level]+leftX, ruler);
    }
    for(int i = 0; i < imageHeight/scales[level]+2; ++i)
    {
        painter.drawLine(-ruler, i*scales[level]+bottomY, ruler, i*scales[level]+bottomY);
    }

    ruler = 3;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_68);
    int displayMin10X = leftX/scales[level]/10*10*scales[level];
    for(int i = 0; i < imageWidth/scales[level]+2; i += 10)
    {
        painter.drawLine(i*scales[level]+displayMin10X, -ruler, i*scales[level]+displayMin10X, ruler);
    }
    int displayMin10Y = bottomY/scales[level]/10*10*scales[level];
    int displayMax10Y = topY/scales[level]/10*10*scales[level];
    qDebug() << displayMax10Y/scales[level] << displayMin10Y/scales[level];
    for(int i = 0; i < displayMax10Y/scales[level]; i += 10)
    {
        painter.drawLine(-ruler, i*scales[level]+displayMin10Y, ruler, i*scales[level]+displayMin10Y);
    }

    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_68);
    painter.drawLine(0, bottomY, 0, topY);
    painter.drawLine(leftX, 0, rightX, 0);
    //qDebug() << offset << displayMinX << displayMaxX;

    for(auto model : inModels)
    {
        painter.setPen(model.second);
        for(int i = leftX; i < rightX; ++i)
        {
            double di = static_cast<double>(i);
            double temp = model.first.yValue(di/scales[level]) * scales[level];
            if(std::isnan(temp))
            {
                qDebug() << "NaN in startY!";
                continue;
            }
            int startY = static_cast<int>(temp);
            static int ignore = 0;
            if(startY < bottomY)
            {
                ignore = bottomY;
                continue;
            }
            else if(startY > topY)
            {
                ignore = topY;
                continue;
            }

            int endY;
            temp = model.first.yValue((di+1.0)/scales[level]) * scales[level];
            if(std::isinf(temp))
                temp > 0.0 ? endY = topY : endY = bottomY;
            else if(std::isnan(temp))
            {
                qDebug() << "NaN in endY!";
                continue;
            }
            else
            {
                endY = static_cast<int>(temp);
                if(endY < bottomY)
                {
                    endY = bottomY;
                }
                else if(endY > topY)
                {
                    endY = topY;
                }
            }

            if(ignore != 0)
            {
                painter.drawLine(i-1, ignore, i, startY);
                ignore = 0;
            }
            painter.drawLine(i, startY, i+1, endY);
        }
    }
}
