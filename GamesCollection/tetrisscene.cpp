#include "tetrisscene.h"
#include<QPainter>
#include<QLabel>
#include<QDebug>
#include<QMenuBar>
#include<QMessageBox>
int TetrisScene::unit=35;
int TetrisScene::xNum=TetrisLogic::xNum;
int TetrisScene::yNum=TetrisLogic::yNum;
TetrisScene::TetrisScene(QWidget *parent) : MyWindow(parent)
{
    ////////////////////////界面初始化//////////////////////////////
    setBackGroundPic(QString(":/first/picture/beiJing3.jpg"));

    //在paintEvent中调整了页面的显示位置 故加上菜单栏的高度
    this->setFixedSize(unit*xNum,unit*yNum+23);

    this->setWindowTitle("小游戏集合：俄罗斯方块");
    //设置帮助信息 该函数继承自mywindow类
    setHelpContent("帮助", "俄罗斯方块帮助","YES","CANCEL");

    //初始化逻辑计算指针
    gameTetrisLogic=new TetrisLogic;


    //选择难度界面
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu  * difficultMenu=bar->addMenu("难度");
    QAction * difficultAction = difficultMenu->addAction("设置难度");
    connect(difficultAction,&QAction::triggered,[=](){
        int difficultChoice=QMessageBox::information(this,"选择难度","请选择适合你的难度","标准","困难","史诗");
        if(difficultChoice==0){
            changeDifficulty(TetrisLogic::NORMAL);
            //标题重设也在上述函数中
        }
        else if(difficultChoice==1){
            changeDifficulty(TetrisLogic::DIFFICULT);
        }
        else if(difficultChoice==2){
            changeDifficulty(TetrisLogic::EPIC);
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
    playSound=new QSound(QString(":/first/music/snake.wav"));
    playSound->setLoops(QSound::Infinite);
    playSound->setParent(this);
    playSound->play();

    dieSound=new QSound(QString(":/first/music/die.wav"));
    dieSound->setParent(this);

    clearSound=new QSound(QString(":/first/music/Ding.wav"));
    clearSound->setParent(this);

//    connect(gameTetrisLogic,&TetrisLogic::lineClear,this,[=]{
//        clearSound->play();
//    });



  //////////////  ///////////初始化地图/////////////////////////
    for(int j=0;j<xNum;j++){//列初始化
        //由于坐标系以左上角为原点 二维数组map 第一维为列 第二维为行
        //每次push_back的单位为一列
        gameTetrisLogic->map.push_back(vector<bool>({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}));//每一列都添加20行个0
    }

    //初始化难度相关信息
   changeDifficulty(TetrisLogic::difficulty);

   //TetrisLogic::gameOver=false;

   ////////////////////////////////////游戏内容//////////////////////

    //初始化定时器
        tetrisTimer=new QTimer(this);
        tetrisTimer->start(delay);
        connect(tetrisTimer,&QTimer::timeout,[=](){
            if(gameRun){
            gameTetrisLogic->move(TetrisLogic::DOWN);
            update();
            //清行音效
            if(TetrisLogic::lineClear)
                clearSound->play();
            //死亡判断
            if(TetrisLogic::gameOver){
                dieSound->play();
                tetrisTimer->stop();
                playSound->stop();
                dieSound->play();
                QString score=QString("您的最终得分为：%1 是否重新开始？").arg(TetrisLogic::score);

                int choice;
                choice= QMessageBox::question(this,"游戏结束！",score,QString("重新开始"),QString("返回选择游戏界面"),QString("关闭游戏"),2);

                if(choice==2){
                    this->close();
                }
                else if(choice==0){
                    qDebug()<<"重新开始";
                    playSound->play();
                    TetrisLogic::gameOver=false;
                    //clear map信息
                    TetrisLogic::map.clear();
                    //初始化地图
                    for(int j=0;j<xNum;j++){//列初始化
                        //由于坐标系以左上角为原点 二维数组map 第一维为列 第二维为行
                        //每次push_back的单位为一列
                        gameTetrisLogic->map.push_back(vector<bool>({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}));//每一列都添加20行个0
                    }
                    //初始化方块
                    gameTetrisLogic->newBlock();
                    //重设标题信息（难度+积分）
                    changeDifficulty(TetrisLogic::difficulty);
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

void TetrisScene::changeDifficulty(TetrisLogic::Difficulty diff)
{
    if(diff==TetrisLogic::EPIC){
        TetrisLogic::difficulty=TetrisLogic::EPIC;
        TetrisLogic::changeTimes=4;//重置旋转次数 史诗级
        delay=150;
        this->setWindowTitle(QString("俄罗斯方块(史诗) 当前得分：%1").arg(TetrisLogic::score));//重设标题

    }
    else if(diff==TetrisLogic::DIFFICULT){
        TetrisLogic::difficulty=TetrisLogic::DIFFICULT;
        TetrisLogic::changeTimes=5;//困难
        delay=200;
        this->setWindowTitle(QString("俄罗斯方块(困难) 当前得分：%1").arg(TetrisLogic::score));//重设标题

    }
    else {
        TetrisLogic::difficulty=TetrisLogic::NORMAL;
        TetrisLogic::changeTimes=15;
        delay=300;
        this->setWindowTitle(QString("俄罗斯方块(标准) 当前得分：%1").arg(TetrisLogic::score));//重设标题

    }
}



void TetrisScene::paintEvent (QPaintEvent *e)
{
    //调用基类paintEvent画背景
    MyWindow::paintEvent(e);

    QPainter p(this);
    //p.setViewport(this->rect());
    p.setViewport(0,23,this->width(),this->height());//菜单栏高度为23 避过它开始绘图


    for(int i=0;i<TetrisLogic::map.size();i++){ //列数
        for(int j=0;j<TetrisLogic::map[i].size();j++){ //行数
            if(TetrisLogic::map[i][j]){
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
            gameTetrisLogic->move(TetrisLogic::LEFT);
            return;
        }
        else if(e->key()==Qt::Key_Right||e->key()==Qt::Key_D){
            gameTetrisLogic->move(TetrisLogic::RIGHT);
            return;
        }
        else if(e->key()==Qt::Key_Down||e->key()==Qt::Key_S){
            gameTetrisLogic->move(TetrisLogic::DOWN);
             update();
             return;
        }
    }
    qDebug()<<TetrisLogic::changeTimes;
    if(TetrisLogic::changeTimes--<=0||!allowPress){//旋转次数耗尽或不允许按键
        qDebug()<<"不允许按键";
        return;
    }
    if(e->key()==Qt::Key_Up||e->key()==Qt::Key_W){
         gameTetrisLogic->move(TetrisLogic::CHANGE);
    }
    update();

     /////////////用switch(e->key())反而延迟大？

}
