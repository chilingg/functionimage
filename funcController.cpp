#include "funcController.h"
#include <QDebug>

funcController::funcController(QWidget *parent)
    : QWidget(parent),
      view(new FuncView),
      mainLayout(new QHBoxLayout(this)),
      rightLayout(new QVBoxLayout),
      console(new QWidget),
      offset(view->getOffsetR()),
      mousePos(view->getMousePosR()),
      movePos()
{
    setWindowTitle(tr("Function Image"));
    resize(840, 720);
    //setWindowState(Qt::WindowMaximized);

    mainLayout->addWidget(view);
    mainLayout->addWidget(console);

    console->setMaximumWidth(180);
    console->setLayout(rightLayout);

    addImageCombo = new QComboBox;
    rightLayout->addWidget(addImageCombo);

    view->addModelImage("x / (1 - x)");
}

funcController::~funcController()
{

}

void funcController::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? view->zoomin() : view->zoomout();
    view->update();
}

void funcController::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
        movePos = event->pos();
    if(event->button() == Qt::LeftButton)
    {
        mousePos = event->globalPos();
        //qDebug() << "c" << mousePos << view->isInView(mousePos);
        if(view->isInView(mousePos))
            view->update();
        else
            mousePos = QPoint();
    }
}

void funcController::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MidButton)
    {
        int moveLengthX = (event->pos().x() - movePos.x()) / view->getUnitSize();
        if(moveLengthX != 0)
        {
            offset.rx() -= moveLengthX;
            movePos.setX(event->pos().x());
        }
        int moveLengthY = (event->pos().y() - movePos.y()) / view->getUnitSize();
        if(moveLengthY != 0)
        {
            offset.ry() += moveLengthY;
            movePos.setY(event->pos().y());
        }
        view->update();
    }
    if(event->buttons() == Qt::LeftButton)
    {
        mousePos = event->globalPos();
        if(view->isInView(mousePos))
            view->update();
        else
            mousePos = QPoint();
    }
}

void funcController::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mousePos = QPoint();
        view->update();
    }
}
