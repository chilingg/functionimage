#ifndef FUNCVIEW_H
#define FUNCVIEW_H

#include <QWidget>
#include "funcmodel.h"

class FuncView : public QWidget
{
    Q_OBJECT
public:
    explicit FuncView(const Calculation func, const int length = 4000, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

private:
    int beginPoint;
    int endPoint;
    FuncModel inModel;
    const double scaleLevels[5];
    unsigned scaleLevel;

signals:

public slots:
};

namespace IMAGE_COLOR {
    const QColor LUMINOSITY_0_0(0, 0, 0);	//Black

    //定义了一组五等三分的明度
    const QColor LUMINOSITY_1_17(17, 17, 17);
    const QColor LUMINOSITY_1_34(34, 34, 34);
    const QColor LUMINOSITY_1_51(51, 51, 51);

    const QColor LUMINOSITY_2_68(68, 68, 68);
    const QColor LUMINOSITY_2_85(85, 85, 85);
    const QColor LUMINOSITY_2_102(102, 102, 102);

    const QColor LUMINOSITY_3_119(119, 119, 119);
    const QColor LUMINOSITY_3_136(136, 136, 136);
    const QColor LUMINOSITY_3_153(153, 153, 153);

    const QColor LUMINOSITY_4_170(170, 170, 170);
    const QColor LUMINOSITY_4_187(187, 187, 187);
    const QColor LUMINOSITY_4_204(204, 204, 204);

    const QColor LUMINOSITY_5_221(221, 221, 221);
    const QColor LUMINOSITY_5_238(238, 238, 238);
    const QColor LUMINOSITY_5_255(255, 255, 255); //White

    const QColor IC_RED(255, 0, 0);
    const QColor IC_YELLOW(255, 255, 0);
    const QColor IC_GREEN(0, 255, 0);
    const QColor IC_CYAN(0, 255, 255);
    const QColor IC_BLUE(0, 0, 255);
    const QColor IC_MAGENTA(255, 0, 255);
}

#endif // FUNCVIEW_H
