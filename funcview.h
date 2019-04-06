#ifndef FUNCVIEW_H
#define FUNCVIEW_H

#include <QWidget>
#include "funcmodel.h"

class FuncView : public QWidget
{
    Q_OBJECT
public:
    explicit FuncView(const Calculation func, const unsigned length, QWidget *parent = nullptr);

private:
    FuncModel inModel;

signals:

public slots:
};

#endif // FUNCVIEW_H
