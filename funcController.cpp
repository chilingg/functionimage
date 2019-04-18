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
      imageLabels(),
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
    //rightLayout->addWidget(new ImageLabel(0, imageType->currentText(), this));
    addImageLabel();
    rightLayout->addStretch();

    view->addModelImage("x / (1 - x)");
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
    imageLabels.push_back(new ImageLabel(view->addModelImage(), view, imageType->currentText()));
    rightLayout->addWidget(imageLabels.back());
}

void FuncController::clearImageLabel()
{
    imageLabels.clear();
    view->clearModelImage();
}

ImageLabel::ImageLabel(unsigned index, FuncView *v, QString title, QWidget *parent):
    QWidget(parent),
    imgIndex(index),
    view(v),
    imgColor(IMAGE_COLOR::IC_RED),
    funcStr(),
    layout(new QGridLayout(this)),
    getColorBtn(new QPushButton),
    closeBtn(new QPushButton),
    titleLabel(new QLabel(title)),
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
    }
}
