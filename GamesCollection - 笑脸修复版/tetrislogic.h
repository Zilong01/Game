#ifndef TETRISLOGIC_H
#define TETRISLOGIC_H
#include"mywindow.h"
#include<vector>
#include<QDebug>
using namespace std;
class TetrisLogic
{

public:

    TetrisLogic();

    static Point shape[7][4][4];//7种图形 至多4种形态 4个点坐标
    static int xNum,yNum;//界面上的方格数
    static vector<vector<bool>>map;//地图 true表示该位置有方块

    enum form{formO=0,formI,formS,formZ,formL,formJ,formT};
    enum moveDirection{CHANGE=0,LEFT,RIGHT,DOWN};
    enum Difficulty{NORMAL,DIFFICULT,EPIC};


    void newBlock();//生成新方块
    void updateMap();//更新地图信息 同时检测是否游戏结束

    void clearPrevious();//清除移动前的方块
    bool checkChange(int moveX=0,int moveY=1,bool isChangeState=false);//移动前、变化形态前的检查/触底检查
    void clearLine();

    void move(moveDirection direction);

    static int changeTimes;
    static int score;
    static Difficulty difficulty;
    static bool gameOver;
    //static bool lineClear;

private:
//    int unit=30;//单位长宽 改到界面中
    int x;//当前x坐标
    int y;//当前y坐标

    int currentShape;//当前方块的形状
    int currentState;//当前方块的状态

//signals:

//    void lineClear1();
};

#endif // TETRISLOGIC_H
