#ifndef FUNCCONTROLLER_H
#define FUNCCONTROLLER_H

#include <QMainWindow>
#include "funcview.h"

class funcController : public QMainWindow
{
    Q_OBJECT

public:
    funcController(QWidget *parent = nullptr);
    ~funcController();

private:
    Calculation func;
    FuncView inView;
    const float maxX = 4000.0f;
    const unsigned maxImageNumber = 10;
};

#endif // FUNCCONTROLLER_H
