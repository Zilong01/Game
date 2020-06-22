#include "mywindow.h"
#include<QMenu>
#include<QAction>
#include<QMenuBar>
#include<QPainter>
#include<QLabel>
#include<QMessageBox>
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
    QAction * infoAction=startMenu->addAction("查看历史记录");
    QAction * quitAction = startMenu->addAction("关闭游戏");

    connect(infoAction,&QAction::triggered,[=](){
        //查看游戏信息
        infoShow();
    });

    connect(quitAction,&QAction::triggered,[=](){
        close();
    });

    //创建帮助菜单
    QMenu  * helpMenu=bar->addMenu("帮助");

    //创建菜单中菜单项
    QAction * gameHelpAction = helpMenu->addAction("查看本游戏帮助");

    connect(gameHelpAction,&QAction::triggered,[=](){
        helpInfo();
    });
}

MyWindow::~MyWindow()
{

}


void MyWindow::setWindow(QMainWindow *window){

    QLabel *appName=new QLabel;
    appName->setParent(window);
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
}

void MyWindow::setBackGroundPic(QString backpic)
{
    this->backGroundPic=backpic;
}

void MyWindow::resizeWindow(int width, int height)
{
    setFixedSize(width,height);
}

void MyWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(this->getBackGroundPic());//加载背景图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

void MyWindow::setHelpContent(QString title, QString content, QString choose1, QString choose2)
{
    helpTitle=title;
    helpContent=content;
    helpChoose1=choose1;
    helpChoose2=choose2;
}

void MyWindow::helpInfo()
{
    QMessageBox::information(this,helpTitle,helpContent,helpChoose1,helpChoose2);
}


