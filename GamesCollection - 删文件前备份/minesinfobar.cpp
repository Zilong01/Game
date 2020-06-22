#include "minesinfobar.h"
#include<QHBoxLayout>
#include<QDebug>
MinesInfoBar::MinesInfoBar(QWidget *parent) : QWidget(parent)
{

    /////////////初始化
    for(int i=0;i<2;i++){
        screen[i]=new QWidget(this);//新建两个控件
    }

    for(int i=0;i<3;i++){
        screen1[i]=new QLabel(screen[0]);//初始化左边数字 父对象为screen
        screen2[i]=new QLabel(screen[1]);
    }

    //设置背景色为灰色
    QPalette palette;
    palette.setColor(QPalette::Background,Qt::gray);
    this->setAutoFillBackground(true);
    this->setPalette(palette);


    //初始化笑脸
    QImage Image;
    Image.load(":/first/picture/mines/face_normal.png");
    QPixmap faceImg = QPixmap::fromImage(Image);
    faceWidget=new QWidget(this);
    faceWidget->resize(NUMHEIGHT,NUMHEIGHT);
    face=new MyPushButton(":/first/picture/mines/face_normal.png");
    face->reSizeBtn(NUMHEIGHT,NUMHEIGHT);//放大笑脸(btn)
    face->resize(NUMHEIGHT,NUMHEIGHT);//放大笑脸(标签)

    face->setParent(faceWidget);
    QPixmap facePix = faceImg.scaled(face->width(), face->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //face->setPix(facePix);
    resetFace(0);//放大笑脸的图片
    faceWidget->move((this->width()-face->width())*0.5,(this->height()-face->height())*0.5);

}

void MinesInfoBar::reset()
{

    //重置屏幕信息
    QImage Image;
    Image.load(":/first/picture/mines/scr0.png");
    QPixmap pixmap = QPixmap::fromImage(Image);


    for(int i=0;i<3;i++){
        //设置数字大小
        screen1[i]->resize(NUMWIDTH,NUMHEIGHT);
        screen2[i]->resize(NUMWIDTH,NUMHEIGHT);

         //按比例缩放图片
        QPixmap num0 = pixmap.scaled(screen1[i]->width(), screen1[i]->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        screen1[i]->setPixmap(num0);
        screen2[i]->setPixmap(num0);

        //水平布局
        screen1[i]->move(NUMWIDTH*i,0);
        screen2[i]->move(NUMWIDTH*i,0);
    }
    screen[0]->resize(NUMWIDTH*3,NUMHEIGHT);
    screen[1]->resize(NUMWIDTH*3,NUMHEIGHT);
    //两个数字显示器放到对称位置
    screen[0]->move(10,0);
    screen[1]->move(-10+this->width()-screen[1]->width(),0);


    faceWidget->move((this->width()-face->width())*0.5,(this->height()-face->height())*0.5);

}

void MinesInfoBar::changeScreen(QLabel **screen, int &num)
{
    if(num>999){
        num=0;//屏幕最大显示999
    }
    int copy=num;
    //读取传入的三个数字
    for(int i=2;i>=0;i--){
        QString digit= QString(":/first/picture/mines/scr%1.png").arg(copy%10);
        screen[i]->setPixmap(digit);
        copy/=10;
    }
}

void MinesInfoBar::changeScreen(int whichScreen, int num)
{
    if(whichScreen!=2&&whichScreen!=1){
        qDebug()<<"没有屏幕"<<whichScreen;
        return;
    }
    if(num>999){
        return;//屏幕最大显示999
    }
    int copy=num;
    //读取传入的三个数字
    for(int i=2;i>=0;i--){
        QString digit= QString(":/first/picture/mines/scr%1.png").arg(copy%10);
        if(whichScreen==1){
            QPixmap digitScl = QPixmap(digit).scaled(screen1[i]->width(), screen1[i]->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            screen1[i]->setPixmap(digitScl);
        }
        else if(whichScreen==2){
            QPixmap digitScl = QPixmap(digit).scaled(screen2[i]->width(), screen2[i]->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            screen2[i]->setPixmap(digitScl);
        }
        copy/=10;
    }
}

void MinesInfoBar::resetFace(int state){
    QPixmap pixmap;
    if(state==0){//默认微笑
        pixmap=QString(":/first/picture/mines/face_normal.png");
    }
    else if(state==1){//胜利
        pixmap=QString(":/first/picture/mines/face_success.png");
    }
    else if(state==2){//失败
        pixmap=QString(":/first/picture/mines/face_fail.png");
    }
    QPixmap facePix = pixmap.scaled(NUMHEIGHT,NUMHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    face->setIcon(facePix);
}

void MinesInfoBar::infoBarResize(int width, int height)
{
    this->resize(width,height);
}
