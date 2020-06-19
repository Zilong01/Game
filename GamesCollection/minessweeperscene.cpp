#include "minessweeperscene.h"
#include<QMenu>
#include<QMenuBar>
#include<QTimer>
MinesSweeperScene::MinesSweeperScene(QWidget *parent) : QMainWindow(parent)
{

   this->setFixedSize(MINESUNIT*9,23+NUMHEIGHT+MINESUNIT*9);

    //设置帮助信息 该函数继承自mywindow类
    //setHelpContent("帮助","扫雷","YES","CANCEL");


    //提示信息
    QLabel *primaryHelp=new QLabel(this);
    primaryHelp->setText("第一次使用请点击菜单栏中的帮助\n即可查看帮助信息");
    primaryHelp->setFixedSize(250,100);
    primaryHelp->move((this->width()-primaryHelp->width())*0.5,20);
    primaryHelp->show();
    primaryHelp->setParent(this);

    QFont ft;
    ft.setPointSize(10);
    ft.setWeight(QFont::Black);
    primaryHelp->setFont(ft);

    //设置提示信息字体颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    primaryHelp->setPalette(pa);
    QTimer *tempTimerForHelp=new QTimer;
    tempTimerForHelp->start(2000);//提示关闭
    connect(tempTimerForHelp,&QTimer::timeout,[=](){
        primaryHelp-> QLabel::setVisible(false);
        tempTimerForHelp->stop();
    });

    QMenuBar *bar=menuBar();
    //返回
    QMenu  * backMenu=bar->addMenu("返回");
    QAction * backAction = backMenu->addAction("返回选择关卡界面");
    connect(backAction,&QAction::triggered,[=](){
        emit backChooseScene();
    });


    //////////////////////////////背景音乐//////////////////////////////
//    playSound=new QSound(QString(":/first/music/snake.wav"));
//    playSound->setLoops(QSound::Infinite);
//    playSound->setParent(this);
//    playSound->play();

//    dieSound=new QSound(QString(":/first/music/die.wav"));
//    dieSound->setParent(this);

//    eatSound=new QSound(QString(":/first/music/Ding.wav"));
//    eatSound->setParent(this);



    /////////////////////////初始化两个模块指针
    infoBar=new MinesInfoBar(this);
    //设置与当前窗口大小一致
    infoBar->resize(this->width(),infoBar->height());
    infoBar->move(0,23);//避过菜单栏
    infoBar->reset();
    infoBar->show();



    ////逻辑处理
    /// 此处先选择默认难度
    minesLoigc=new MinesSweeperLogic(PRIMARYROWANDCOL,PRIMARYROWANDCOL,PRIMARYMINES,this);
    minesLoigc->setParent(this);//让控件在本窗口内显示->不加这个就无延迟
    minesLoigc->resize(this->width(),this->height()-23-infoBar->height());
    minesLoigc->move(0,23+infoBar->height());

    //生成新地图
    minesLoigc->newMap();
    minesLoigc->show();


    //监听logic中的信号
    //connect(minesLoigc,&MinesSweeperLogic::)
}
