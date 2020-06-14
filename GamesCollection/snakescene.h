#ifndef SNAKESCENE_H
#define SNAKESCENE_H
#pragma execution_character_set("utf-8")
#include "mywindow.h"
#include<vector>
#include<QPaintEvent>
using namespace std;
struct Point{int x,y;};

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
    enum Difficulty{EASY=1,NORMAL};

    void paintEvent(QPaintEvent *e) override;
    bool checkFood()const;//检查食物是否与蛇身重合

private:
 //   Ui::SnakeScene *ui;

    vector<Point>snake; //蛇身
    Point food;//食物

    int moveDirection=UP;//蛇移动方向

    bool gameOver=false;
    int difficulty=NORMAL;//难度
    //int length;//蛇长度 直接用vector的size表示长度

    int unit=15;//蛇身一个方块的单位长与宽

    bool allowPress=false;//是否允许按键

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

};

#endif // SNAKESCENE_H
