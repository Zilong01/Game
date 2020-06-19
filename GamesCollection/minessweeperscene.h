#ifndef MINESSWEEPERSCENE_H
#define MINESSWEEPERSCENE_H

#include <QMainWindow>
#include"mywindow.h"
#include"minesinfobar.h"
#include"minessweeperlogic.h"


#define PRIMARYROWANDCOL 9
#define MIDDLEROWANDCOL 16
#define SENIORROW 16
#define SENIOCOL 30
#define PRIMARYMINES 10
#define MIDDLEMINES 40
#define SENIORMINES 99

//扫雷游戏场景
class MinesSweeperScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit MinesSweeperScene(QWidget *parent = nullptr);

    enum Difficulty{PRIMARY,MIDDLE,SENIOR};
    MinesInfoBar* infoBar=nullptr;
    MinesSweeperLogic* minesLoigc=nullptr;

signals:
    void backChooseScene();
};

#endif // MINESSWEEPERSCENE_H
