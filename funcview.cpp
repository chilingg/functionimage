#include "funcview.h"
#include <QPainter>
#include <cmath>
#include <stack>

FuncView::FuncView(QWidget *parent) :
    QWidget(parent),
    offset(0, 0),
    inModels(),
    scales{4, 8, 16, 32, 64},
    level(2),
    numbers{
        QImage(":/texts/0"),
        QImage(":/texts/1"),
        QImage(":/texts/2"),
        QImage(":/texts/3"),
        QImage(":/texts/4"),
        QImage(":/texts/5"),
        QImage(":/texts/6"),
        QImage(":/texts/7"),
        QImage(":/texts/8"),
        QImage(":/texts/9"),
        QImage(":/texts/-"),
        QImage(":/texts/point")
        },
    mousePos(0, 0),
    rulerSpace(0),
    imageWidth(0),
    imageHeight(0),
    gridOnOff(true),
    accuretaOnOff(true),
    numberOnOff(true)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, IMAGE_COLOR::LUMINOSITY_5_255);
    setAutoFillBackground((true));
    setPalette(pal);

    for(int i = 0; i < 10; ++i)
    {
        numbers[i] = numbers[i].mirrored();
    }
}

void FuncView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(accuretaOnOff)
        rulerSpace = 18;
    else
        rulerSpace = 0;

    int unitSize = scales[level];
    QPoint viewLTP((-width() - rulerSpace)/2 + offset.x()*unitSize,
                    (height() + rulerSpace)/2 + offset.y()*unitSize);
    imageWidth = width() - rulerSpace;
    imageHeight = height() - rulerSpace;
    int column = imageWidth/2/unitSize*2 + 2;
    int row = imageHeight/2/unitSize*2 + 2;
    int leftX = -column/2*unitSize + offset.x()*unitSize;
    int rightX = leftX + column*unitSize;
    int bottomY = -row/2*unitSize + offset.y()*unitSize;
    int topY = bottomY + row*unitSize;
    
    std::stack<int, std::vector<int>> reverse;//数字倒转用

    painter.setWindow(viewLTP.x(), viewLTP.y(), width(), -height());

    //qDebug() << bottomY << topY << leftX << rightX;
    if(unitSize > 4 && gridOnOff)
    {
        painter.setPen(IMAGE_COLOR::LUMINOSITY_5_238);
        for(int i = 0; i < column; ++i)
        {
            painter.drawLine(leftX+i*unitSize, bottomY, leftX+i*unitSize, topY);
        }
        for(int i = 0; i < row; ++i)
        {
            painter.drawLine(leftX, bottomY+i*unitSize, rightX, bottomY+i*unitSize);
        }
    }

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
    }

    int ruler = 1;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_0_0);
    for(int i = 0; i < column; ++i)
    {
        painter.drawLine(i*unitSize+leftX, -ruler, i*unitSize+leftX, ruler);
    }
    for(int i = 0; i < row; ++i)
    {
        painter.drawLine(-ruler, i*unitSize+bottomY, ruler, i*unitSize+bottomY);
    }

    ruler = 4;
    painter.setPen(IMAGE_COLOR::LUMINOSITY_0_0);
    for(int i = -leftX/unitSize%10; i < column; i += 10)
    {
        painter.drawLine(i*unitSize+leftX, -ruler, i*unitSize+leftX, ruler);
        if(numberOnOff)
        {
            int num = i + leftX/unitSize;
            int pp = i*unitSize+leftX;
            int pW = numbers[0].width();
            if(num < 0)
            {
                painter.drawImage(pp, -18, numbers[10]);
                pp += pW;
                num = -num;
            }
            for(int j = num; j != 0; j /= 10)
            {
                reverse.push(j % 10);
            }
            while(!reverse.empty())
            {
                painter.drawImage(pp, -18, numbers[reverse.top()]);
                reverse.pop();
                pp += pW;
            }
        }
    }
    for(int i = -bottomY/unitSize%10; i < row; i += 10)
    {
        painter.drawLine(-ruler, i*unitSize+bottomY, ruler, i*unitSize+bottomY);
        if(numberOnOff)
        {
            int num = i + bottomY/unitSize;
            int pY = i*unitSize+bottomY;
            int PX = 11;
            int pW = numbers[0].width();
            if(num < 0)
            {
                painter.drawImage(PX, pY, numbers[10]);
                PX += pW;
                num = -num;
            }
            for(int j = num; j != 0; j /= 10)
            {
                reverse.push(j % 10);
            }
            while(!reverse.empty())
            {
                painter.drawImage(PX, pY, numbers[reverse.top()]);
                reverse.pop();
                PX += pW;
            }
        }
    }

    painter.setPen(IMAGE_COLOR::LUMINOSITY_2_102);
    painter.drawLine(0, bottomY, 0, topY);
    painter.drawLine(leftX, 0, rightX, 0);

    if(accuretaOnOff)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(IMAGE_COLOR::LUMINOSITY_5_238);
        painter.drawRect(viewLTP.x(), viewLTP.y(), rulerSpace, -height());
        painter.drawRect(viewLTP.x(), viewLTP.y(), width()-1, -rulerSpace);
        painter.setBrush(QBrush());

        //qDebug() << mousePos;
        if(!mousePos.isNull())
        {
            int imgMouseX = viewLTP.x() + mousePos.x();
            int imgMouseY = viewLTP.y() - mousePos.y();
            painter.setPen(QPen(IMAGE_COLOR::IC_LIGHTRED, 1, Qt::DashLine));
            painter.drawLine(imgMouseX, viewLTP.y(), imgMouseX, imgMouseY);
            painter.drawLine(viewLTP.x(), imgMouseY, imgMouseX, imgMouseY);

            double xValue = imgMouseX * 1.0 / unitSize;
            double yValue = imgMouseY * 1.0 / unitSize;
            qDebug() << xValue << yValue;
            int numToStr = static_cast<int>(xValue);

            int pp = imgMouseX + 4;
            int pW = numbers[0].width();
            if(numToStr < 0)
            {
                painter.drawImage(pp, viewLTP.y()-12, numbers[10]);
                pp += pW;
                numToStr = -numToStr;
            }
            for(int j = numToStr; j != 0; j /= 10)
            {
                reverse.push(j % 10);
            }
            if(reverse.empty())
                reverse.push(0);
            while(!reverse.empty())
            {
                painter.drawImage(pp, viewLTP.y()-12, numbers[reverse.top()]);
                reverse.pop();
                pp += pW;
            }
        }
    }

    /*
    painter.setPen(IMAGE_COLOR::LUMINOSITY_0_0);
    painter.drawRect(leftX, bottomY, unitSize, unitSize);
    painter.drawRect(rightX, bottomY, -unitSize, unitSize);
    painter.drawRect(0, bottomY, unitSize, unitSize);
    painter.drawRect(0, topY, unitSize, -unitSize);
    painter.drawRect(-10, 10, 10, 10);
*/
}

void FuncView::clearImage()
{
    for(auto img : inModels)
    {
        img.first.wipeCacheImage();
    }
}
