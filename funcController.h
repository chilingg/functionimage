#ifndef FUNCCONTROLLER_H
#define FUNCCONTROLLER_H

#include <QWidget>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include "funcview.h"

class funcController : public QWidget
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
    FuncView *view;
    QHBoxLayout *mainLayout;
    //QLabel *console;
    QPoint &offset;
    QPoint &mousePos;
    QPoint movePos;
};

#endif // FUNCCONTROLLER_H
