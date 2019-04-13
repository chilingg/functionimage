#include "funcController.h"
#include <QDebug>

double function(double input);

funcController::funcController(QWidget *parent)
    : QMainWindow(parent),
      func(function),
      inView(func),
      offset(inView.getOffsetR()),
      movePos()
{
    setWindowTitle(tr("Function Image"));
    resize(840, 720);
    setWindowState(Qt::WindowMaximized);
    setCentralWidget(&inView);
}

funcController::~funcController()
{

}

void funcController::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? inView.zoomin() : inView.zoomout();
    inView.update();
}

void funcController::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
        movePos = event->pos();
}

void funcController::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MidButton)
    {
        int moveLengthX = (event->pos().x() - movePos.x()) / inView.getUnitSize();
        if(moveLengthX != 0)
        {
            offset.rx() -= moveLengthX;
            movePos.setX(event->pos().x());
        }
        int moveLengthY = (event->pos().y() - movePos.y() / inView.getUnitSize());
        if(moveLengthY != 0)
        {
            offset.ry() += moveLengthY;
            movePos.setY(event->pos().y());
        }
        inView.update();
    }
}

double function(double input)
{
    //qDebug() << input << 500-input;
    return input / (1 - input);
}
