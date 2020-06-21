
#ifndef TETRIS_H
#define TETRIS_H
#include<vector>
using namespace std;
#include "mywindow.h"
#include<QPaintEvent>
#include<QTimer>
#include<QKeyEvent>
#include<QSound>
#include"tetrislogic1.h"
#include"infowindow.h"
//struct Point{int x,y;};




class TetrisScene : public MyWindow
{
    Q_OBJECT
public:

    explicit TetrisScene(QWidget *parent = nullptr);


    void changeDifficulty(TetrisLogic1::Difficulty);
    QTimer *tetrisTimer=nullptr;
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e)override;

private:
    static int unit;//单位长宽
    static int xNum,yNum;//界面上的方格数
    static bool closeMusic;

    int delay=300;//刷新延迟


    bool gameRun=true;
    bool allowPress=true;//是否允许按键

    QSound *playSound=nullptr;
    QSound *dieSound=nullptr;
    QSound *clearSound=nullptr;

    TetrisLogic1 *gameTetrisLogic=nullptr;
    InfoWindow *infoWin=nullptr;

    virtual void infoShow() override;
    void record();

signals:
    void backChooseScene();

};

#endif // TETRIS_H
