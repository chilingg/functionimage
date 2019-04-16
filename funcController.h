#ifndef FUNCCONTROLLER_H
#define FUNCCONTROLLER_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QMouseEvent>
#include "funcview.h"

class funcController : public QMainWindow
{
    Q_OBJECT

public:
    funcController(QWidget *parent = nullptr);
    ~funcController() override;

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Calculation func;
    FuncView view;
    QPoint &offset;
    QPoint &mousePos;
    QPoint movePos;
    const unsigned maxImageNumber = 10;
};

#endif // FUNCCONTROLLER_H
