#include "minessweeperscene.h"
#include<QMenu>
#include<QMenuBar>
MinesSweeperScene::MinesSweeperScene(QWidget *parent) : MyWindow(parent)
{
    setBackGroundPic(QString(":/first/picture/beiJing3.jpg"));

    this->setFixedSize(705,450);

    //设置帮助信息 该函数继承自mywindow类
    setHelpContent("帮助","扫雷","YES","CANCEL");


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


    infoBar=new MinesInfoBar(this);
    //设置与当前窗口大小一致
    infoBar->resize(this->width(),infoBar->height());
    infoBar->move(0,23);//避过菜单栏
    infoBar->reset();
    infoBar->show();

}
