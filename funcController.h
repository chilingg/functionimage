#ifndef FUNCCONTROLLER_H
#define FUNCCONTROLLER_H

#include <QWidget>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include "funcview.h"

class ImageLabel;

class FuncController : public QWidget
{
    Q_OBJECT

public:
    FuncController(QWidget *parent = nullptr);
    ~FuncController() override;

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void addImageLabel();
    void clearImageLabel();

    FuncView *view;
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QVBoxLayout *imgLabelLayout;
    QWidget *console;
    QComboBox *imageType;
    QPushButton *addImageBtn;
    QPushButton *clearImageBtn;
    std::vector<ImageLabel*> imgLabels;
    QPoint &offset;
    QPoint &mousePos;
    QPoint movePos;

public slots:
    void deleteImgLab(unsigned index);
};

class ImageLabel : public QWidget
{
    Q_OBJECT
public:
    ImageLabel(unsigned index, FuncView *v, QString titleLabel, QWidget *parent = nullptr);
    ~ImageLabel();
    void setImgIndex(unsigned value) { imgIndex = value; }
    unsigned getImgIndex() const { return imgIndex; }

private:
    unsigned imgIndex;
    FuncView *view;
    QColor imgColor;
    std::string funcStr;
    QGridLayout *layout;
    QPushButton *getColorBtn;
    QPushButton *closeBtn;
    QLabel *titleLabel;
    QLineEdit *funcEdit;

signals:
    void deleteSelf(unsigned index);

public slots:
    void setImgColor();
    void removeImage();
};

#endif // FUNCCONTROLLER_H
