#include "snakescene.h"
#include "ui_snakescene.h"
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QMessageBox>
#include<QSound>
#include<QLabel>
SnakeScene::SnakeScene(QWidget *parent) :
    MyWindow(parent)//,
  //ui(new Ui::SnakeScene)
{
    //ui->setupUi(this);

    ////////////////////////界面初始化//////////////////////////////
    setBackGroundPic(QString(":/first/picture/beiJing3.jpg"));
    setTittle();

    this->setFixedSize(705,450);

    //选择难度界面
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu  * difficultMenu=bar->addMenu("难度");
    QAction * difficultAction = difficultMenu->addAction("设置难度");
    connect(difficultAction,&QAction::triggered,[=](){
        int difficultChoice=QMessageBox::information(this,"选择难度","请选择适合你的难度","标准","简单","金刚");
        if(difficultChoice==0){
            difficulty=NORMAL;
            delay=100;
            this->setWindowTitle(QString("小游戏集合：贪吃蛇(标准) 当前长度：%1").arg(snake.size()));//重设标题
        }
        else if(difficultChoice==1){
            difficulty=EASY;
            delay=200;
            this->setWindowTitle(QString("小游戏集合：贪吃蛇(简单) 当前长度：%1").arg(snake.size()));//重设标题
        }
        else if(difficultChoice==2){
            difficulty=IMMORTAL;
            delay=150;
            this->setWindowTitle(QString("小游戏集合：贪吃蛇(金刚) 当前长度：%1").arg(snake.size()));//重设标题
        }
    });

    //设置帮助信息 该函数继承自mywindow类
    setHelpContent("帮助","按WASD或↑←↓→键控制蛇的移动，按'空格'暂停游戏 \n 点击'难度'可以设置难度信息，"
                        "\n 简单模式下撞墙不会死亡，标准模式会死亡 \n 金刚模式下蛇不会因为吃到自己而死亡","YES","CANCEL");


    //提示信息
    QLabel *primaryHelp=new QLabel(this);
    primaryHelp->setText("第一次使用请按空格暂停游戏\n点击菜单栏中的帮助 即可查看帮助信息");
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
    tempTimerForHelp->start(delay*20);//提示关闭
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

    eatSound=new QSound(QString(":/first/music/Ding.wav"));
    eatSound->setParent(this);

    //////////////////////////初始化相关信息////////////////////
    //初始化蛇身
    snake.push_back({345,375});
    snake.push_back({snake[0].x,snake[0].y+unit});
    snake.push_back({snake[1].x,snake[1].y+unit});
    //初始化食物
    newFood();



    //////////////////////////蛇的移动/////////////////////////
    //计数器 实现延迟
    timerMove=new QTimer(this);
    connect(timerMove,&QTimer::timeout,[=](){
        if(gameRun&&!gameOver){
            move();
            isEatFood();
            allowPress=true;
        }

    });
    timerMove->start(delay);


}

SnakeScene::~SnakeScene()
{
    // delete ui;
}

void SnakeScene::paintEvent(QPaintEvent *e)
{
    MyWindow::paintEvent(e);//画背景
    QPainter painter(this);
    //画蛇头
    painter.fillRect(snake[0].x,snake[0].y,unit,unit,Qt::red);

    //画蛇身
    for(int i=1;i<snake.size();i++){
        painter.fillRect(snake[i].x,snake[i].y,unit,unit,Qt::darkYellow);
    }

    //画食物
    painter.fillRect(food.x,food.y,unit,unit,Qt::green);
}

void SnakeScene::keyPressEvent(QKeyEvent *e)
{


    switch (e->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:
        if(moveDirection==DOWN||allowPress == false)
            return;
        else {moveDirection=UP;
            allowPress=false;}
        break;

    case Qt::Key_A:
    case Qt::Key_Left:
        if(moveDirection==RIGHT||allowPress == false)
            return;
        else {moveDirection=LEFT;
            allowPress=false;}
        break;

    case Qt::Key_S:
    case Qt::Key_Down:
        if(moveDirection==UP||allowPress == false)
            return;
        else {moveDirection=DOWN;
            allowPress=false;}
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        if(moveDirection==LEFT||allowPress == false)
            return;
        else {moveDirection=RIGHT;
            allowPress=false;}
        break;

    case Qt::Key_Space:
        gameRun=!gameRun;//游戏运行状态取非->实现暂停
        if(playSound->isFinished())
            playSound->play();
        else playSound->stop();
        allowPress=false;
        break;
    default:
        break;
    }
}

bool SnakeScene::checkFood() const
{
    for(int i=0;i<snake.size();i++){
        if(snake[i].x==food.x&&snake[i].y==food.y){
            return false;
        }
    }
    return true;
}

void SnakeScene::newFood()
{
    srand(static_cast<int>(time(0)));
    food.x=rand()%(this->width()/unit)*unit;//以蛇身单位长为单位的屏幕长度*单位
    food.y=rand()%(this->height()/unit)*unit;//以蛇身单位长为单位的屏幕宽度*单位
    while(!checkFood()){//重合
        srand(static_cast<int>(time(0)));
        food.x=rand()%(this->width()/unit-1)*unit;//以蛇身单位长为单位的屏幕长度*单位
        food.y=rand()%(this->height()/unit-1)*unit;//以蛇身单位长为单位的屏幕宽度*单位
    }
}

void SnakeScene::move()
{
    if(moveDirection==UP)
        this->moveUp();
    else if(moveDirection==DOWN)
        this->moveDown();
    else if(moveDirection==LEFT)
        this->moveLeft();
    else if(moveDirection==RIGHT)
        this->moveRight();
    if(difficulty!=IMMORTAL)//非金刚模式下 吃到自己死亡
        if(eatSelf())
            died("吃到了自己");
}

void SnakeScene::died(QString reason)
{
    timerMove->stop();
    playSound->stop();
    dieSound->play();
    QString score=QString("您的最终长度为：%1 是否重新开始？").arg(snake.size());
    int choice;
    if(reason=="")
        choice= QMessageBox::question(this,"蛇已死亡！",score,QString("重新开始"),QString("返回选择游戏界面"),QString("关闭游戏"),2);//临时实现 待修改
    else
        choice= QMessageBox::question(this,QString("蛇由于%1已死亡！").arg(reason),score,QString("重新开始"),QString("返回选择游戏界面"),QString("关闭游戏"),2);//临时实现 待修改

    if(choice==2){
        this->close();
    }
    if(choice==0){
        qDebug()<<"重新开始";
        playSound->play();
        snake.clear();//清除蛇信息
        setTittle();//重设标题信息（难度+积分）
        moveDirection=UP;//重置移动方向
        //初始化蛇身
        snake.push_back({345,375});
        snake.push_back({snake[0].x,snake[0].y+unit});
        snake.push_back({snake[1].x,snake[1].y+unit});
        //初始化食物
        newFood();
        timerMove->start(delay);
    }

    if(choice==1){//返回选择游戏界面
        emit backChooseScene();
    }
    return;
}

void SnakeScene::addOne()
{
    Point newTail={snake[snake.size()-1].x,snake[snake.size()-1].y};//重复尾巴点坐标
    snake.push_back(newTail);
}

bool SnakeScene::isEatFood()
{
    if(snake[0].x==food.x&&snake[0].y==food.y){
        qDebug()<<"吃到食物";
        addOne();//增加长度
        newFood();
        eatSound->play();

        //更改标题 （增加长度信息）
        setTittle();
        return true;
    }
    return false;
}

bool SnakeScene::eatSelf()
{
    for(int i=1;i<snake.size();i++){
        if(snake[0].x==snake[i].x&&snake[0].y==snake[i].y){
            return true;
        }
    }
    return false;//没吃到自己
}



void SnakeScene::moveUp()
{

    if(snake[0].y-unit>0){
        Point newHead={snake[0].x,snake[0].y-unit};
        snake.insert(snake.begin(),newHead);
        snake.erase(snake.end()-1);//删除末尾
    }
    else{
        if(difficulty==EASY){
            Point newHead={snake[0].x,this->height()-unit};//从窗口底部重新穿出
            snake.insert(snake.begin(),newHead);
            snake.erase(snake.end()-1);//删除末尾
        }
        if(difficulty==NORMAL){
            died(QString("接触上边界"));
        }
    }
    update();
}

void SnakeScene::moveDown()
{
    if(snake[0].y+unit<this->height()){
        Point newHead={snake[0].x,snake[0].y+unit};
        snake.insert(snake.begin(),newHead);
        snake.erase(snake.end()-1);//删除末尾
    }
    else{
        if(difficulty==EASY){
            Point newHead={snake[0].x,0};//从窗口顶部重新穿出
            snake.insert(snake.begin(),newHead);
            snake.erase(snake.end()-1);//删除末尾
        }
        if(difficulty==NORMAL){
            died(QString("接触下边界"));
        }
    }
    update();
}

void SnakeScene::moveLeft()
{
    if(snake[0].x-unit>=0){
        Point newHead={snake[0].x-unit,snake[0].y};
        snake.insert(snake.begin(),newHead);
        snake.erase(snake.end()-1);//删除末尾
    }
    else{
        if(difficulty==EASY){
            Point newHead={this->width(),snake[0].y};//从窗口右侧重新穿出
            snake.insert(snake.begin(),newHead);
            snake.erase(snake.end()-1);//删除末尾
        }
        if(difficulty==NORMAL){
            died(QString("接触左边界"));
        }
    }
    update();
}
void SnakeScene::moveRight()
{
    if(snake[0].x+unit<this->width()){
        Point newHead={snake[0].x+unit,snake[0].y};
        snake.insert(snake.begin(),newHead);
        snake.erase(snake.end()-1);//删除末尾
    }
    else{
        if(difficulty==EASY){
            Point newHead={0,snake[0].y};//从窗口左部重新穿出
            snake.insert(snake.begin(),newHead);
            snake.erase(snake.end()-1);//删除末尾
        }
        if(difficulty==NORMAL){
            died(QString("接触右边界"));
        }
    }
    update();
}

void SnakeScene::setTittle()
{
    QString tempD;
    if(difficulty==EASY)
        tempD="简单";
    if(difficulty==NORMAL)
        tempD="标准";
    if(difficulty==IMMORTAL)
        tempD="金刚";
    setWindowTitle(QString("小游戏集合：贪吃蛇(%1) 当前长度：%2").arg(tempD).arg(snake.size()));
}
