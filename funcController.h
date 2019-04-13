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

private:
    Calculation func;
    FuncView inView;
    QPoint &offset;
    QPoint movePos;
    const unsigned maxImageNumber = 10;
};

#endif // FUNCCONTROLLER_H
