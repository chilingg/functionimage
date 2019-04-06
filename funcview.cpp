#include "funcview.h"

FuncView::FuncView(const Calculation func, const unsigned length, QWidget *parent) :
    QWidget(parent),
    inModel(func, length)
{

}
