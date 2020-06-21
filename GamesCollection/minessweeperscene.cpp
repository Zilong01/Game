#include "minessweeperscene.h"
#include<QMenu>
#include<QMenuBar>
#include<QTimer>
#include<QMessageBox>
#include<QDebug>
MinesSweeperScene::MinesSweeperScene(QWidget *parent) : MyWindow(parent)
{

   this->setFixedSize(MINESUNIT*9,23+NUMHEIGHT+MINESUNIT*9);

    //设置帮助信息 该函数继承自mywindow类
    setHelpContent("帮助","左键单击：在判断出不是雷的方块上按下左键，可以打开该方块。\n"
                        "如果方块上出现数字，则该数字表示其周围3×3区域中的地雷数；\n"
                        "如果方块上为空（相当于0），则可以递归地打开与空相邻的方块；\n"
                        "如果不幸触雷，则游戏结束。\n"
                        "右键单击：在判断为地雷的方块上按下右键，可以标记地雷（显示为小红旗）。\n"
                        "重复两次操作可取消标记。","YES","CANCEL");

    this->setWindowTitle("扫雷");

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


    /////////////////////////////菜单栏/////////////////////
    QMenuBar *bar=menuBar();
    //    enum Difficulty{PRIMARY,MIDDLE,SENIOR};
    QMenu *difficultyMenu=bar->addMenu("难度");
    QAction *primaryAction=difficultyMenu->addAction("初级");
    QAction *middleAction=difficultyMenu->addAction("中级");
    QAction *seniorAction=difficultyMenu->addAction("高级");
    QAction *customizeAction=difficultyMenu->addAction("自定义");



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

    dieSound=new QSound(QString(":/first/music/boom.wav"));
    dieSound->setParent(this);

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
    minesLoigc=new MinesSweeperLogic(SRow,SCol,PRIMARYMINES,this);
    minesLoigc->setParent(this);//让控件在本窗口内显示->不加这个就无延迟
    minesLoigc->resize(this->width(),this->height()-23-infoBar->height());
    minesLoigc->move(0,23+infoBar->height());

    //生成新地图
    minesLoigc->newMap();
    minesLoigc->show();

    timer=new QTimer(this);


    //第一次点击打开计时器
    connect(minesLoigc,&MinesSweeperLogic::firstClickSignal,[=](){
        timer->start(1000);//1秒响应一次
    });
    //修改时间屏幕
    connect(timer,&QTimer::timeout,[=](){
        time++;
        infoBar->changeScreen(2,time);
    });
    //修改雷数屏幕
    infoBar->changeScreen(1,minesLoigc->getNumOfMines());//初始雷数
    connect(minesLoigc,&MinesSweeperLogic::flagChangeSignal,[=](){
        infoBar->changeScreen(1,minesLoigc->getNumOfMines()-minesLoigc->getNumOfFlags());
    });


    //监听logic中的死亡信号
    connect(minesLoigc,&MinesSweeperLogic::gameOver,[=](){
        dieSound->play();
        //保存游戏记录
        record(false);

        timer->stop();//计时器停止
        //延迟弹出
        infoBar->resetFace(2);
        QTimer *tempTimer=new QTimer(this);
        tempTimer->start(800);
        connect(tempTimer,&QTimer::timeout,[=]{
            tempTimer->stop();
            int choice;


            choice=QMessageBox::information(this,"游戏结束","请选择你要进行的操作","再战一局","返回选择游戏界面","我还要看本局");
            if(choice==0){
                time=0;//重置时间
                infoBar->resetFace(0);//必须先于reset
                infoBar->reset();
                //////////////////////bug第二局不改笑脸了
                infoBar->changeScreen(1,minesLoigc->getNumOfMines());//初始雷数
                connect(minesLoigc,&MinesSweeperLogic::flagChangeSignal,[=](){
                    infoBar->changeScreen(1,minesLoigc->getNumOfMines()-minesLoigc->getNumOfFlags());
                });

                minesLoigc->newMap();
                minesLoigc->show();
            }

            if(choice==1){
                emit backChooseScene();
            }

//            if(choice==2){
//                this->close();
//            }
        });
    });

    connect(minesLoigc,&MinesSweeperLogic::gameWin,[=](){

        infoBar->resetFace(1);

        //保存游戏记录
        record(true);

        QTimer *tempTimer=new QTimer(this);
        tempTimer->start(100);
        connect(tempTimer,&QTimer::timeout,[=]{
            tempTimer->stop();
            int choice;
            choice=QMessageBox::information(this,"游戏胜利","请选择你要进行的操作","再战一局","返回选择游戏界面");
            if(choice==0){
                infoBar->resetFace(0);//必须先于reset
                infoBar->reset();
                minesLoigc->newMap();
                minesLoigc->show();
            }
            if(choice==1){
                emit backChooseScene();
            }

        });
    });



    connect(primaryAction,&QAction::triggered,[=](){
         SRow=SCol=PRIMARYROWANDCOL;
         SMines=PRIMARYMINES;
         minesLoigc->resetMapSize(SRow,SCol,SMines);
         minesLoigc->newMap();
         this->setFixedSize(MINESUNIT*9,23+NUMHEIGHT+MINESUNIT*9);
         minesLoigc->resize(this->width(),this->height()-23-infoBar->height());
         infoBar->resize(this->width(),infoBar->height());
         infoBar->reset();


    });
    connect(middleAction,&QAction::triggered,[=](){
         SRow=SCol=MIDDLEROWANDCOL;
         SMines=MIDDLEMINES;
         minesLoigc->resetMapSize(SRow,SCol,SMines);
         minesLoigc->newMap();
         this->setFixedSize(MINESUNIT*MIDDLEROWANDCOL,23+NUMHEIGHT+MINESUNIT*MIDDLEROWANDCOL);
         qDebug()<<"中级";
         minesLoigc->resize(this->width(),this->height()-23-infoBar->height());
         infoBar->resize(this->width(),infoBar->height());
         infoBar->reset();
         infoBar->changeScreen(1,SMines);
         infoBar->face->move((this->width()-infoBar->face->width())*0.5,0);
    });

    connect(seniorAction,&QAction::triggered,[=](){
         SRow=SENIORROW;
         SCol=SENIORCOL;
         SMines=SENIORMINES;
         minesLoigc->resetMapSize(SRow,SCol,SMines);
         minesLoigc->newMap();
         this->setFixedSize(MINESUNIT*SENIORCOL,23+NUMHEIGHT+MINESUNIT*SENIORROW);
         minesLoigc->resize(this->width(),this->height()-23-infoBar->height());
         infoBar->resize(this->width(),infoBar->height());
         infoBar->reset();
         infoBar->changeScreen(1,SMines);
         infoBar->face->move((this->width()-infoBar->face->width())*0.5,0);
    });

    //////////////////////////用户自定义难度
    connect(customizeAction,&QAction::triggered,[=](){
        qDebug()<<"检测到";
        diffScene=new MinesDiffSet(this);
        diffScene->show();

        connect(diffScene,&MinesDiffSet::setCol,this,[=](int col__){
            SCol=col__;
            //qDebug()<<"连接成功"<<SCol;
        });

        connect(diffScene,&MinesDiffSet::setRow,this,[=](int row__){
            SRow=row__;
            //qDebug()<<"连接成功"<<SRow;
        });

        connect(diffScene,&MinesDiffSet::setMines,this,[=](int mines__){
            SMines=mines__;
            //qDebug()<<"连接成功"<<SCol;
        });

        connect(diffScene->btn_q,&QPushButton::clicked,[=](){
            qDebug()<<"设置成功"<<SRow<<SCol<<SMines;
            diffScene->deleteLater();
            minesLoigc->resetMapSize(SRow,SCol,SMines);
            minesLoigc->newMap();
            this->setFixedSize(MINESUNIT*SCol,23+NUMHEIGHT+MINESUNIT*SRow);
            minesLoigc->resize(this->width(),this->height()-23-infoBar->height());
            infoBar->resize(this->width(),infoBar->height());
            infoBar->reset();
            infoBar->changeScreen(1,SMines);
        });


    });



}

void MinesSweeperScene::record(bool isWin)
{
    ///////////////////////保存游戏记录//////////////////////////////////////
    QFile record1("D:\\2020_train\\Game\\GamesCollection\\minesInformation.txt");
    if(record1.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append)){
        QTextStream date(&record1);//数据流对象并与文件关联
        QDateTime tempTime=QDateTime::currentDateTime();
        QString currentTime=tempTime.toString("yyyy.MM.dd hh:mm ddd");
        if(isWin)
            date<<QString("游戏时间:")<<currentTime<<QString("   行数:")<<SRow<<QString("   列数:")<<SCol<<QString("   雷数:")<<SMines<<"  "<<QString("胜利")<<QString(" 耗时:%1 秒").arg(time)<<endl;
        else
            date<<QString("游戏时间:")<<currentTime<<QString("   行数:")<<SRow<<QString("   列数:")<<SCol<<QString("   雷数:")<<SMines<<"  "<<QString("失败")<<QString(" 耗时:%1 秒").arg(time)<<endl;
            //date<<currentTime<<SRow<<" "<<SCol<<" "<<SMines<<" "<<QString("失败")<<" "<<time<<endl;
        record1.close();
    }
    else qDebug()<<"扫雷记录文件打开失败";
}

void MinesSweeperScene::infoShow()
{
    infoWin=new InfoWindow(this);
    infoWin->changePage(2);
    infoWin->show();
    //qDebug()<<"游戏信息展示";
}
