#include "snakescene.h"
#include "ui_snakescene.h"
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QMessageBox>
SnakeScene::SnakeScene(QWidget *parent) :
    MyWindow(parent)//,
    //ui(new Ui::SnakeScene)
{
    //ui->setupUi(this);
    setBackGroundPic(QString(":/first/picture/beiJing3.jpg"));

    this->setWindowTitle(QString("小游戏集合：贪吃蛇"));
    this->setFixedSize(705,450);

  //初始化蛇身
    snake.push_back({345,375});
    snake.push_back({snake[0].x,snake[0].y+unit});
    snake.push_back({snake[1].x,snake[1].y+unit});
  //初始化食物  ->是否可以封装？
    srand(static_cast<int>(time(0)));
    food.x=rand()%(this->width()/unit)*unit;//以蛇身单位长为单位的屏幕长度*单位
    food.y=rand()%(this->height()/unit)*unit;//以蛇身单位长为单位的屏幕宽度*单位
    while(!checkFood()){
        srand(static_cast<int>(time(0)));
        food.x=rand()%(this->width()/unit-1)*unit;//以蛇身单位长为单位的屏幕长度*单位
        food.y=rand()%(this->height()/unit-1)*unit;//以蛇身单位长为单位的屏幕宽度*单位
    }

   QTimer *timerMove=new QTimer(this);
   connect(timerMove,&QTimer::timeout,[=](){
       moveUp();
   });
   timerMove->start(300);









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

    //花蛇身
    for(int i=1;i<snake.size();i++){
        painter.fillRect(snake[i].x,snake[i].y,unit,unit,Qt::darkYellow);
    }

    //画食物
    painter.fillRect(food.x,food.y,unit,unit,Qt::green);
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
            ////////////////////////////////////////修改我///////////////////////
            qDebug()<<"游戏结束 分数";
            QString score=QString("您的最终长度为：%1 是否重新开始？").arg(snake.size());

            int choice= QMessageBox::question(this,"蛇已死亡！",score,QString("重新开始"),QString("返回选择游戏界面"),QString("关闭游戏"),2);//临时实现 待修改
            if(choice==2){
                this->close();
            }
        }
    }
    update();
}

void SnakeScene::moveDown()
{
    Point newHead={snake[0].x,snake[0].y+unit};
    snake.insert(snake.begin(),newHead);
    snake.erase(snake.end()-1);
}

void SnakeScene::moveLeft()
{
    Point newHead={snake[0].x-unit,snake[0].y};
    snake.insert(snake.begin(),newHead);
    snake.erase(snake.end()-1);
}
