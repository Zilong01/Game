#include "mypushbutton.h"
#include"QDebug"
#include<QString>
#include<QPropertyAnimation>
MyPushButton::MyPushButton(QString firstImg,QString secondImg){
    Img1=firstImg,Img2=secondImg;
    QPixmap pix1,pix2;
    if(!pix1.load(firstImg)){
        //加载失败
        qDebug()<<QString("按钮中图片1(%1)加载失败！").arg(firstImg);
        return;
    }
    this->setStyleSheet("QPushButton{border:0px;}");//去除透明部分
    this->setFixedSize(pix1.width(),pix1.height());
    this->setIcon(pix1);
    this->setIconSize(QSize(pix1.width()*0.75,pix1.height()*0.75));
}

void MyPushButton::btnShow()
{
    //创建动态对象
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //设置动态时间间隔100ms
    animation->setDuration(50);

    //起止位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();


    QPropertyAnimation *animation2=new QPropertyAnimation(this,"geometry");
    animation2->setDuration(50);
    animation2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation2->start();
}
