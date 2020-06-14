#include "mainscene.h"
#include<QAction>
#include"mywindow.h"
#include<QPainter>
#include<QLabel>
#include"mypushbutton.h"
#include<QDebug>
#include<QSound>
#include"choosegamescene.h"
#include<QTimer>
MainScene::MainScene(QWidget *parent)
    : MyWindow(parent)
{
    setBackGroundPic(":/first/picture/beiJing3.jpg");
    //显示应用名称在程序中
    QLabel *appName=new QLabel;
    appName->setParent(this);

          //1.设置字体
    QFont font;
    font.setPointSize(40);
    //font.setFamily("华文行楷");
    font.setWeight(QFont::Black);
    appName->setFont(font);
           //2.设置字体颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    appName->setPalette(pa);
            //3.在屏幕上显示
    appName->setText(QString("小游戏集合"));
    //appName->setGeometry(150,this->height()*0.10,appName->width(),appName->height());
    appName->move(150,0);


    ChooseGameScene *gameScene=new ChooseGameScene;
    //进入选择游戏场景的按钮
    MyPushButton *btn_start=new MyPushButton(":/first/picture/start.png");
    btn_start->setParent(this);
    btn_start->move((this->width()-btn_start->width())*0.5,400);


    //QSound *startSound=new QSound(":/first/music/Click.wav");
    connect(btn_start,&QPushButton::clicked,[=](){
        btn_start->btnShow();//动画
        btn_start->btnMusic(":/first/music/Click.wav");
        //startSound->play();
        //设置选择游戏场景的初始位置
        gameScene->setGeometry(this->geometry());
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit this->enterChooseScene();
            gameScene->show();
            //delete this;
        });

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
