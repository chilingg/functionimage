#include "funcController.h"
#include <QApplication>
#include <QColorDialog>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    FuncController w;
    w.show();

    return a.exec();
}
