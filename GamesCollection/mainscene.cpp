#include "mainscene.h"
#include<QAction>
#include"mywindow.h"
#include<QPainter>
#include<QLabel>
#include"mypushbutton.h"
#include<QDebug>
#include<QSound>
MainScene::MainScene(QWidget *parent)
    : MyWindow(parent)
{
    setBackGroundPic(":/first/picture/beiJing3.jpg");
    //显示应用名称
    QLabel *appName=new QLabel;
    appName->setParent(this);

    QFont font;
    font.setPointSize(40);
    //font.setFamily("华文行楷");
    font.setWeight(QFont::Black);
    appName->setFont(font);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    appName->setPalette(pa);

    appName->setText(QString("小游戏集合"));
    //appName->setGeometry(150,this->height()*0.10,appName->width(),appName->height());
    appName->move(150,0);

    MyPushButton *btn_start=new MyPushButton(":/first/picture/start.png");
    btn_start->setParent(this);

    QSound *startSound=new QSound(":/first/music/Click.wav");
    connect(btn_start,&QPushButton::clicked,[=](){
        btn_start->btnShow();//动画
        //this->hide();
        startSound->play();
    });

}

MainScene::~MainScene()
{
    qDebug()<<"主场景析构";
}

void MainScene::paintEvent(QPaintEvent *e){
    MyWindow::paintEvent(e);//调用mywindow类中的绘图事件 用于绘制背景图片
    QPainter painter(this);

    //绘制应用图标于窗口内
    QPixmap pix2;
    pix2.load(":/first/picture/appPix.png");
    painter.drawPixmap(0,this->height()*0.20,pix2.width()*0.3,pix2.height()*0.3,pix2);

}
