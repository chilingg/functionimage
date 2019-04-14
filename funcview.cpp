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

    int unitSize = scales[level];
    QPoint viewLTP(-width()/2 + offset.x()*unitSize - rulerSpace,
                    height()/2 + offset.y()*unitSize + rulerSpace);
    int imageWidth = width() - rulerSpace;
    int imageHeight = height() - rulerSpace;
    int column = imageWidth/2/unitSize*2;
    int row = imageHeight/2/unitSize*2;
    int leftX = -column/2*unitSize - unitSize + offset.x()*unitSize;
    int rightX = -(leftX - offset.x()*unitSize);
    int bottomY = -row/2*unitSize - unitSize + offset.y()*unitSize;
    int topY = -(bottomY - offset.y()*unitSize);

    painter.setWindow(viewLTP.x(), viewLTP.y(), width(), -height());

    painter.setPen(IMAGE_COLOR::LUMINOSITY_0_0);
    painter.drawRect(viewLTP.x(), viewLTP.y()-unitSize, rulerSpace, rulerSpace);
    painter.drawLine(leftX, bottomY, leftX, topY);
    /*
    //qDebug() << bottomY << topY << leftX << rightX;
    if(unitSize > 4 && rulerOnOff)
    {
        painter.setPen(IMAGE_COLOR::LUMINOSITY_5_238);
        for(int i = 0; i < imageWidth+unitSize; i += unitSize)
        {
            painter.drawLine(leftX+i, bottomY, leftX+i, topY);
        }
        for(int i = 0; i < imageHeight+unitSize; i += unitSize)
        {
            painter.drawLine(leftX, bottomY+i, rightX, bottomY+i);
        }
    }
    if(rulerOnOff)
    {
        int viewLX = leftX - rulerSpace;
        int viewLT = topY + rulerSpace;
        painter.setPen(IMAGE_COLOR::LUMINOSITY_2_102);
        painter.drawRect(leftX, topY, unitSize, unitSize);
        //painter.drawRect(viewLX, topY, width(), rulerSpace);
    }

    int ruler = 1;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_102);
    for(int i = 0; i < imageWidth/unitSize+2; ++i)
    {
        painter.drawLine(i*unitSize+leftX, -ruler, i*unitSize+leftX, ruler);
    }
    for(int i = 0; i < imageHeight/unitSize+2; ++i)
    {
        painter.drawLine(-ruler, i*unitSize+bottomY, ruler, i*unitSize+bottomY);
    }

    ruler = 3;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_68);
    int displayMin10X = leftX/unitSize/10*10*unitSize;
    for(int i = 0; i < imageWidth/unitSize+2; i += 10)
    {
        painter.drawLine(i*unitSize+displayMin10X, -ruler, i*unitSize+displayMin10X, ruler);
    }
    int displayMin10Y = bottomY/unitSize/10*10*unitSize;
    int displayMax10Y = topY/unitSize/10*10*unitSize;
    qDebug() << displayMax10Y/unitSize << displayMin10Y/unitSize;
    for(int i = 0; i < displayMax10Y/unitSize; i += 10)
    {
        painter.drawLine(-ruler, i*unitSize+displayMin10Y, ruler, i*unitSize+displayMin10Y);
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
            double temp = model.first.yValue(di/unitSize) * unitSize;
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
            temp = model.first.yValue((di+1.0)/unitSize) * unitSize;
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
    }*/
}
