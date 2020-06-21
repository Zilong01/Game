#ifndef MINESSWEEPERSCENE_H
#define MINESSWEEPERSCENE_H

#include <QMainWindow>
#include"mywindow.h"
#include"minesinfobar.h"
#include"minessweeperlogic.h"
#include"minesdiffset.h"
#include<QSound>
#include"infowindow.h"
#define PRIMARYROWANDCOL 9
#define MIDDLEROWANDCOL 16
#define SENIORROW 16
#define SENIORCOL 30
#define PRIMARYMINES 10
#define MIDDLEMINES 40
#define SENIORMINES 99

//扫雷游戏场景
class MinesSweeperScene : public MyWindow
{
    Q_OBJECT
public:
    explicit MinesSweeperScene(QWidget *parent = nullptr);

    enum Difficulty{PRIMARY,MIDDLE,SENIOR};
    MinesInfoBar* infoBar=nullptr;
    MinesSweeperLogic* minesLoigc=nullptr;

    MinesDiffSet* diffScene=nullptr;
    InfoWindow* infoWin=nullptr;

    QTimer *timer=nullptr;//计时器
    int time=0;//存储时间

    QSound *dieSound=nullptr;
    void record(bool isWin);

    virtual void infoShow() override;

private:
   int SCol=PRIMARYROWANDCOL;
   int SRow=PRIMARYROWANDCOL;
   int SMines=PRIMARYMINES;
signals:
    void backChooseScene();
};

#endif // MINESSWEEPERSCENE_H
