#include "funcController.h"
#include <QDebug>

funcController::funcController(QWidget *parent)
    : QMainWindow(parent),
      func(10.0, {std::make_pair(1, -1.0)}),
      inView(func)
{
    qDebug() << func(15);
    setWindowTitle(tr("Function Image"));
    resize(840, 720);
    setWindowState(Qt::WindowMaximized);
    setCentralWidget(&inView);
}

funcController::~funcController()
{

}
