#ifndef SNAKESCENE_H
#define SNAKESCENE_H
#pragma execution_character_set("utf-8")
#include "mywindow.h"
#include<vector>
#include<QPaintEvent>
#include<QKeyEvent>
#include<QSound>
#include<infowindow.h>
using namespace std;
//struct Point{int x,y;};

namespace Ui {
class SnakeScene;
}

class SnakeScene : public MyWindow
{
    Q_OBJECT

public:
    explicit SnakeScene(QWidget *parent = nullptr);
    ~SnakeScene();
    enum Direction{UP=1,DOWN,LEFT,RIGHT};
    enum Difficulty{EASY=0,NORMAL,IMMORTAL};

    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e)override;

    bool checkFood()const;//检查食物是否与蛇身重合
    void newFood();//新生成食物
    void move();
    void died(QString reason="");//死亡信息（弹出QMessageBox reason为死亡原因
    void addOne();//蛇长加1
    bool isEatFood();//是否吃到食物

    bool eatSelf();
    static bool closeMusic;
    //virtual void helpInfo(QString title , QString content , QString choose1 , QString choose2 ) override;
private:
 //   Ui::SnakeScene *ui;

    vector<Point>snake; //蛇身
    Point food;//食物

    int moveDirection=LEFT;//蛇移动方向
    QTimer *timerMove;

    InfoWindow *infoWin=nullptr;//游戏数据

    bool gameOver=false;
    bool gameRun=true;//游戏未暂停
    int difficulty=NORMAL;//难度
    int delay=100;//刷新延迟
    //int length;//蛇长度 直接用vector的size表示长度

    int unit=15;//蛇身一个方块的单位长与宽

    int numOfChange=0;

    bool allowPress=true;//是否允许按键

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void setTittle();

    QSound *playSound;
    QSound *dieSound;
    QSound *eatSound;

    void record();
    void infoShow() override;


signals:
    void backChooseScene();

};

#endif // SNAKESCENE_H
