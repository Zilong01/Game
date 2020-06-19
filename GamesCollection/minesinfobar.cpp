#include "minesinfobar.h"
#include<QHBoxLayout>
MinesInfoBar::MinesInfoBar(QWidget *parent) : QWidget(parent)
{

    /////////////初始化
    for(int i=0;i<2;i++){
        screen[i]=new QWidget(this);//新建两个控件
    }

    for(int i=0;i<3;i++){
        screen1[i]=new QLabel(screen[0]);//初始化左边数字
        screen2[i]=new QLabel(screen[1]);
    }

    //设置背景色为灰色
    QPalette palette;
    palette.setColor(QPalette::Background,Qt::gray);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

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

    //放置表情到中央
    face=new MyPushButton(":/first/picture/mines/face_normal.png");
    face->setParent(this);
    face->reSizeBtn(NUMHEIGHT,NUMHEIGHT);//放大笑脸(btn)
    resetFace(0);//放大笑脸的图片
    face->move((this->width()-face->width())*0.5,(this->height()-face->height())*0.5);


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
