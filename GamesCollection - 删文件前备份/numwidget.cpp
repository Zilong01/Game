#include "numwidget.h"
#include "ui_numwidget.h"

NumWidget::NumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumWidget)
{
    ui->setupUi(this);    

    //连接这两个部件
    connect(ui->spinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->horizontalSlider,&QSlider::setValue);

    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,[=]{
        emit getNumChange(ui->spinBox->value());
         });





}

NumWidget::~NumWidget()
{
    delete ui;
}

void NumWidget::setMinNum(int num)
{
    ui->spinBox->setMinimum(num);
    ui->horizontalSlider->setMinimum(num);
}

void NumWidget::setMaxNum(int num)
{
    ui->spinBox->setMaximum(num);
    ui->horizontalSlider->setMaximum(num);
}

//int NumWidget::getNum()
//{
//    return ui->spinBox->value();
//}

