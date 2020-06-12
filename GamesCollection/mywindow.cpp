#include "mywindow.h"
#include<QMenu>
#include<QAction>
#include<QMenuBar>
#include<QPainter>
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent)
{

    setFixedSize(450,700);//设置窗口固定大小
    //设置应用图片
    setWindowIcon(QPixmap(":/first/picture/appPix.png"));
    //设置窗口标题
    setWindowTitle(QString("小游戏集合"));

    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu  * startMenu=bar->addMenu("开始");

    //创建菜单中菜单项
    QAction * openAction = startMenu->addAction("打开");
    QAction * saveAction = startMenu->addAction("保存");
    startMenu->addSeparator();
    QAction * quitAction = startMenu->addAction("关闭游戏");

    connect(quitAction,&QAction::triggered,[=](){close();});
    //创建帮助菜单
    QMenu  * helpMenu=bar->addMenu("帮助");

    //创建菜单中菜单项
    QAction * gameHelpAction = helpMenu->addAction("查看本游戏帮助");

}

MyWindow::~MyWindow()
{

}

//似乎已经没用了 可以删去
void MyWindow::setWindow(QMainWindow *window){
//    window->setFixedSize(450,700);//设置窗口固定大小
//    //设置应用图片
//    window->setWindowIcon(QPixmap(":/first/picture/appPix.jpg"));
//    //设置窗口标题
//    window->setWindowTitle(QString("小游戏集合"));

//    //创建菜单栏
//    QMenuBar *bar=window->menuBar();
//    window->setMenuBar(bar);

//    //创建开始菜单
//    QMenu  * startMenu=bar->addMenu("开始");

//    //创建菜单中菜单项
//    QAction * openAction = startMenu->addAction("打开");
//    QAction * saveAction = startMenu->addAction("保存");
//    startMenu->addSeparator();
//    QAction * quitAction = startMenu->addAction("关闭游戏");

//    connect(quitAction,&QAction::triggered,[=](){window->close();});
//    //创建帮助菜单
//    QMenu  * helpMenu=bar->addMenu("帮助");

//    //创建菜单中菜单项
//    QAction * gameHelpAction = helpMenu->addAction("查看本游戏帮助");

}

void MyWindow::setBackGroundPic(QString backpic)
{
    this->backGroundPic=backpic;
}

void MyWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(this->getBackGroundPic());//加载背景图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
