#include "tetrisscene.h"
#include<QPainter>
#include<QLabel>
#include<QDebug>
#include<QMenuBar>
#include<QMessageBox>
#include<QDateTime>
int TetrisScene::unit=35;
int TetrisScene::xNum=TetrisLogic1::xNum;
int TetrisScene::yNum=TetrisLogic1::yNum;
bool TetrisScene::closeMusic=false;
TetrisScene::TetrisScene(QWidget *parent) : MyWindow(parent)
{
    ////////////////////////界面初始化//////////////////////////////
    setBackGroundPic(QString(":/first/picture/beiJing3.jpg"));

    //在paintEvent中调整了页面的显示位置 故加上菜单栏的高度
    this->setFixedSize(unit*xNum,unit*yNum+23);

    //this->setStyleSheet("border-image:url(:/first/picture/beiJing3.jpg);");//样式表绘制背景图
    //用调色板绘制背景图
    QPalette pal=this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/first/picture/beiJing3.jpg")));
    setPalette(pal);

    this->setWindowTitle("小游戏集合：俄罗斯方块");
    //设置帮助信息 该函数继承自mywindow类
    setHelpContent("帮助", "使用按WASD或↑←↓→键控制方块的移动，按'空格'暂停游戏 \n 点击'难度'可以设置难度信息，"
                         "\n 标准模式下限制每个方块旋转15次，困难模式限制旋转5次 \n 史诗模式限制旋转4次\n"
                         "同时，不同的难度有着不同的下落速度""","YES","CANCEL");

    //初始化逻辑计算指针
    gameTetrisLogic=new TetrisLogic1;


    //选择难度界面
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu  * difficultMenu=bar->addMenu("难度");
    QAction * difficultAction = difficultMenu->addAction("设置难度");
    connect(difficultAction,&QAction::triggered,[=](){
        int difficultChoice=QMessageBox::information(this,"选择难度","请选择适合你的难度","标准","困难","史诗");
        if(difficultChoice==0){
            changeDifficulty(TetrisLogic1::NORMAL);
            //标题重设也在上述函数中
        }
        else if(difficultChoice==1){
            changeDifficulty(TetrisLogic1::DIFFICULT);
        }
        else if(difficultChoice==2){
            changeDifficulty(TetrisLogic1::EPIC);
        }
    });


    //提示信息
    QLabel *primaryHelp=new QLabel(this);
    primaryHelp->setText("第一次使用请按空格暂停游戏\n点击菜单栏中的帮助 即可查看帮助信息");
    primaryHelp->setFixedSize(200,90);
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
    //提示关闭
    tempTimerForHelp->start(delay*20);
    connect(tempTimerForHelp,&QTimer::timeout,[=](){
        primaryHelp-> QLabel::setVisible(false);
        tempTimerForHelp->stop();
    });

    //返回
    QMenu  * backMenu=bar->addMenu("返回");
    QAction * backAction = backMenu->addAction("返回选择关卡界面");
    connect(backAction,&QAction::triggered,[=](){
        emit backChooseScene();
    });


    //////////////////////////////背景音乐//////////////////////////////
    playSound=new QSound(QString(":/first/music/Tetris.wav"));
    playSound->setLoops(QSound::Infinite);
    playSound->setParent(this);
    if(!TetrisScene::closeMusic)
        playSound->play();

    dieSound=new QSound(QString(":/first/music/die.wav"));
    dieSound->setParent(this);

    clearSound=new QSound(QString(":/first/music/Ding.wav"));
    clearSound->setParent(this);

    connect(gameTetrisLogic,&TetrisLogic1::lineClear1,[=](){
        if(!TetrisScene::closeMusic)
            clearSound->play();
        //标题重设
        changeDifficulty(TetrisLogic1::difficulty);
    });

    //背景音乐设置
    QMenu  * musicMenu=bar->addMenu("音乐");
    QAction * stopMusicAction = musicMenu->addAction("关闭/打开背景音乐");
    connect(stopMusicAction,&QAction::triggered,[=](){
        if(playSound->isFinished())
            playSound->play();
        else playSound->stop();
    });
    QAction * closeMusicAction = musicMenu->addAction("关闭/打开所有音乐");
    connect(closeMusicAction,&QAction::triggered,[=](){
        TetrisScene::closeMusic=!TetrisScene::closeMusic;
        if(playSound->isFinished()||!TetrisScene::closeMusic){
            playSound->play();
        }
        else playSound->stop();
    });


    //////////////  ///////////初始化地图/////////////////////////
    for(int j=0;j<xNum;j++){//列初始化
        //由于坐标系以左上角为原点 二维数组map 第一维为列 第二维为行
        //每次push_back的单位为一列
        gameTetrisLogic->map.push_back(vector<bool>({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}));//每一列都添加20行个0
    }

    //初始化难度相关信息
    changeDifficulty(TetrisLogic1::difficulty);

    //TetrisLogic1::gameOver=false;

    ////////////////////////////////////游戏内容//////////////////////

    //初始化定时器
    tetrisTimer=new QTimer(this);
    tetrisTimer->start(delay);
    connect(tetrisTimer,&QTimer::timeout,[=](){
        if(gameRun){
            gameTetrisLogic->move(TetrisLogic1::DOWN);
            update();


            //死亡判断
            if(TetrisLogic1::gameOver){
                if(!TetrisScene::closeMusic)
                    dieSound->play();
                tetrisTimer->stop();
                playSound->stop();
                if(!TetrisScene::closeMusic)
                    dieSound->play();
                record();//记录游戏信息
                QString score=QString("您的最终得分为：%1 是否重新开始？").arg(TetrisLogic1::score);

                int choice;
                choice= QMessageBox::question(this,"游戏结束！",score,QString("重新开始"),QString("返回选择游戏界面"),QString("关闭游戏"),2);

                if(choice==2){
                    this->close();
                }
                else if(choice==0){
                    qDebug()<<"重新开始";
                    if(!TetrisScene::closeMusic)
                         playSound->play();
                    TetrisLogic1::gameOver=false;
                    //clear map信息
                    TetrisLogic1::map.clear();
                    //初始化地图
                    for(int j=0;j<xNum;j++){//列初始化
                        //由于坐标系以左上角为原点 二维数组map 第一维为列 第二维为行
                        //每次push_back的单位为一列
                        gameTetrisLogic->map.push_back(vector<bool>({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}));//每一列都添加20行个0
                    }
                    //初始化方块
                    gameTetrisLogic->newBlock();
                    //
                    TetrisLogic1::score=0;//重置积分
                    //重设标题信息（难度+积分）
                    changeDifficulty(TetrisLogic1::difficulty);
                    //重启计数器
                    tetrisTimer->start(delay);

                }

                else if(choice==1){//返回选择游戏界面
                    emit backChooseScene();
                }
                return;
            }


        }

    });


}

void TetrisScene::changeDifficulty(TetrisLogic1::Difficulty diff)
{
    if(diff==TetrisLogic1::EPIC){
        TetrisLogic1::difficulty=TetrisLogic1::EPIC;
        TetrisLogic1::changeTimes=4;//重置旋转次数 史诗级
        delay=150;
        this->setWindowTitle(QString("俄罗斯方块(史诗) 当前得分：%1").arg(TetrisLogic1::score));//重设标题

    }
    else if(diff==TetrisLogic1::DIFFICULT){
        TetrisLogic1::difficulty=TetrisLogic1::DIFFICULT;
        TetrisLogic1::changeTimes=5;//困难
        delay=200;
        this->setWindowTitle(QString("俄罗斯方块(困难) 当前得分：%1").arg(TetrisLogic1::score));//重设标题

    }
    else {
        TetrisLogic1::difficulty=TetrisLogic1::NORMAL;
        TetrisLogic1::changeTimes=15;
        delay=300;
        this->setWindowTitle(QString("俄罗斯方块(标准) 当前得分：%1").arg(TetrisLogic1::score));//重设标题

    }
}



void TetrisScene::paintEvent (QPaintEvent *e)
{


    QPainter p(this);
    //p.setViewport(this->rect());
    p.setViewport(0,23,this->width(),this->height());//菜单栏高度为23 避过它开始绘图


    for(int i=0;i<TetrisLogic1::map.size();i++){ //列数
        for(int j=0;j<TetrisLogic1::map[i].size();j++){ //行数
            if(TetrisLogic1::map[i][j]){
                p.fillRect(i*unit,j*unit,unit-1,unit-1,QColor("red"));//长宽均减1 强化边界感
            }
        }
    }

    //画边框线
    QPen pen;;
    pen.setWidth(0);
    pen.setColor("white");
    p.setPen(pen);

    for(int i=0;i<=yNum;i++){
        p.drawLine(0,i*unit,this->width(),i*unit);
    }
    for(int i=0;i<=xNum;i++){
        p.drawLine(i*unit,0,i*unit,this->height());
    }
}

void TetrisScene::keyPressEvent(QKeyEvent *e){

    if(e->key()==Qt::Key_Space){
        gameRun=!gameRun;//游戏运行状态取非->实现暂停
        if(playSound->isFinished())
            playSound->play();
        else playSound->stop();
        allowPress=!allowPress;
        return;
    }
    if(allowPress){//允许左右和向下移动
        if(e->key()==Qt::Key_Left||e->key()==Qt::Key_A){
            gameTetrisLogic->move(TetrisLogic1::LEFT);
            return;
        }
        else if(e->key()==Qt::Key_Right||e->key()==Qt::Key_D){
            gameTetrisLogic->move(TetrisLogic1::RIGHT);
            return;
        }
        else if(e->key()==Qt::Key_Down||e->key()==Qt::Key_S){
            gameTetrisLogic->move(TetrisLogic1::DOWN);
             update();
             return;
        }
    }
    qDebug()<<TetrisLogic1::changeTimes;
    if(TetrisLogic1::changeTimes--<=0||!allowPress){//旋转次数耗尽或不允许按键
        qDebug()<<"不允许按键";
        return;
    }
    if(e->key()==Qt::Key_Up||e->key()==Qt::Key_W){
         gameTetrisLogic->move(TetrisLogic1::CHANGE);
    }
    update();

     /////////////用switch(e->key())反而延迟大？

}

void TetrisScene::infoShow()
{
    infoWin=new InfoWindow(this);
    infoWin->changePage(1);
    infoWin->show();
}

void TetrisScene::record()
{
    ///////////////////////保存游戏记录//////////////////////////////////////
    QFile record1("D:\\2020_train\\Game\\GamesCollection\\tetrisInformation.txt");
    if(record1.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append)){
        QTextStream date(&record1);//数据流对象并与文件关联
        QDateTime tempTime=QDateTime::currentDateTime();
        QString currentTime=tempTime.toString("yyyy.MM.dd hh:mm ddd");
        date<<QString("游戏时间:")<<currentTime<<QString("   得分:")<<TetrisLogic1::score<<endl;
        record1.close();
    }
    else qDebug()<<"俄罗斯方块记录文件打开失败";
}



