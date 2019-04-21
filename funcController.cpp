#include "funcController.h"
#include <QColorDialog>
#include <QDebug>

FuncController::FuncController(QWidget *parent)
    : QWidget(parent),
      view(new FuncView),
      mainLayout(new QHBoxLayout(this)),
      rightLayout(new QVBoxLayout),
      imgLabelLayout(new QVBoxLayout),
      console(new QWidget),
      imageType(new QComboBox),
      addImageBtn(new QPushButton("新增")),
      clearImageBtn(new QPushButton("清除")),
      imgLabels(),
      offset(view->getOffsetR()),
      mousePos(view->getMousePosR()),
      movePos()
{
    setWindowTitle(tr("Function Image"));
    resize(1024, 780);
    //setWindowState(Qt::WindowMaximized);

    mainLayout->addWidget(view);
    mainLayout->addWidget(console);

    console->setMaximumWidth(180);
    console->setLayout(rightLayout);
    imageType->addItem("普通函数");

    connect(addImageBtn, &QPushButton::clicked, this, &FuncController::addImageLabel);
    connect(clearImageBtn, &QPushButton::clicked, this, &FuncController::clearImageLabel);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(addImageBtn);
    btnLayout->addWidget(clearImageBtn);

    rightLayout->addWidget(imageType);
    rightLayout->addLayout(btnLayout);
    rightLayout->addSpacing(6);
    rightLayout->addLayout(imgLabelLayout);
    //rightLayout->addWidget(new ImageLabel(0, imageType->currentText(), this));
    //addImageLabel();
    rightLayout->addStretch();
}

FuncController::~FuncController()
{

}

void FuncController::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? view->zoomin() : view->zoomout();
    view->update();
}

void FuncController::mousePressEvent(QMouseEvent *event)
{
    //QColorDialog::getColor(Qt::red, this);
    if(event->button() == Qt::MidButton)
        movePos = event->pos();
    if(event->button() == Qt::LeftButton)
    {
        mousePos = event->globalPos();
        //qDebug() << "c" << mousePos << view->isInView(mousePos);
        if(view->isInView(mousePos))
            view->update();
        else
            mousePos = QPoint();
    }
}

void FuncController::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MidButton)
    {
        int moveLengthX = (event->pos().x() - movePos.x()) / view->getUnitSize();
        if(moveLengthX != 0)
        {
            offset.rx() -= moveLengthX;
            movePos.setX(event->pos().x());
        }
        int moveLengthY = (event->pos().y() - movePos.y()) / view->getUnitSize();
        if(moveLengthY != 0)
        {
            offset.ry() += moveLengthY;
            movePos.setY(event->pos().y());
        }
        view->update();
    }
    if(event->buttons() == Qt::LeftButton)
    {
        mousePos = event->globalPos();
        if(view->isInView(mousePos))
            view->update();
        else
            mousePos = QPoint();
    }
}

void FuncController::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mousePos = QPoint();
        view->update();
    }
}

void FuncController::addImageLabel()
{
    imgLabels.push_back(new ImageLabel(view->addModelImage(), view, imageType->currentText()));
    imgLabelLayout->addWidget(imgLabels.back());
    connect(imgLabels.back(), &ImageLabel::deleteSelf, this, &FuncController::deleteImgLab);
    view->update();
}

void FuncController::clearImageLabel()
{
    for(auto lab : imgLabels)
        delete lab;
    imgLabels.clear();
    view->clearModelImage();
    view->update();
}

void FuncController::deleteImgLab(unsigned index)
{
    auto it = imgLabels.begin();
    std::advance(it, index);
    delete *it;
    imgLabels.erase(it);

    //更新label对应的图像索引
    for(unsigned i = 0; i < imgLabels.size(); ++i)
        imgLabels[i]->setImgIndex(i);
    view->update();
}

ImageLabel::ImageLabel(unsigned index, FuncView *v, const QString &title, QWidget *parent):
    QWidget(parent),
    imgIndex(index),
    view(v),
    imgColor(IMAGE_COLOR::IC_RED),
    layout(new QGridLayout(this)),
    getColorBtn(new QPushButton),
    closeBtn(new QPushButton),
    imgTitle(title),
    titleLabel(new QLabel("请输入正确函数")),
    funcEdit(new QLineEdit)
{
    QPalette plt(palette());
    plt.setColor(QPalette::Background, IMAGE_COLOR::LUMINOSITY_5_221);
    setPalette(plt);
    setAutoFillBackground(true);

    getColorBtn->setFlat(true);
    getColorBtn->setMaximumSize(16, 16);
    plt = getColorBtn->palette();
    plt.setColor(QPalette::Button, imgColor);
    getColorBtn->setPalette(plt);
    getColorBtn->setAutoFillBackground(true);
    connect(getColorBtn, &QPushButton::clicked, this, &ImageLabel::setImgColor);

    closeBtn->setFlat(true);
    closeBtn->setIcon(QIcon(":/texts/close"));
    closeBtn->setMaximumSize(16, 16);
    connect(closeBtn, &QPushButton::clicked, this, &ImageLabel::removeImage);

    connect(funcEdit, &QLineEdit::editingFinished, this, &ImageLabel::setImageFunc);

    layout->addWidget(getColorBtn, 0, 0);
    layout->addWidget(titleLabel, 0, 1);
    layout->addWidget(closeBtn, 0, 2);
    layout->addWidget(funcEdit, 1, 0, 1, 3);
}

ImageLabel::~ImageLabel()
{

}

void ImageLabel::setImgColor()
{
    QColor color = QColorDialog::getColor(imgColor);
    if(color.isValid())
    {
        imgColor = color;
        QPalette plt = getColorBtn->palette();
        plt.setColor(QPalette::Button, imgColor);
        getColorBtn->setPalette(plt);

        view->getFuncImage(imgIndex).second = imgColor;
        view->update();
    }
}

void ImageLabel::removeImage()
{
    view->removeModelImage(imgIndex);
    view->update();
    emit deleteSelf(imgIndex);
}

void ImageLabel::setImageFunc()
{
    if(view->changeImageFunc(imgIndex, funcEdit->text()))
    {
        titleLabel->setText(imgTitle);
        view->update();
    }
    else
    {
        titleLabel->setText("无效或空函数");
    }
}
