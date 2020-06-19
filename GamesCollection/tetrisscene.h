
#ifndef TETRIS_H
#define TETRIS_H
#include<vector>
using namespace std;
#include "mywindow.h"
#include<QPaintEvent>
#include<QTimer>
#include<QKeyEvent>
#include<QSound>
#include"tetrislogic.h"
//struct Point{int x,y;};




class TetrisScene : public QMainWindow
{
    Q_OBJECT
public:

    explicit TetrisScene(QWidget *parent = nullptr);


    void changeDifficulty(TetrisLogic::Difficulty);
    QTimer *tetrisTimer=nullptr;
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e)override;

private:
    static int unit;//单位长宽
    static int xNum,yNum;//界面上的方格数


    int delay=300;//刷新延迟


    bool gameRun=true;
    bool allowPress=true;//是否允许按键

    QSound *playSound=nullptr;
    QSound *dieSound=nullptr;
    QSound *clearSound=nullptr;

    TetrisLogic *gameTetrisLogic=nullptr;
signals:
    void backChooseScene();

};

#endif // TETRIS_H
