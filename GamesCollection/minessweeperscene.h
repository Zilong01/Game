#ifndef MINESSWEEPERSCENE_H
#define MINESSWEEPERSCENE_H

#include <QMainWindow>
#include"mywindow.h"
#include"minesinfobar.h"

//扫雷游戏场景
class MinesSweeperScene : public MyWindow
{
    Q_OBJECT
public:
    explicit MinesSweeperScene(QWidget *parent = nullptr);


    MinesInfoBar* infoBar=nullptr;
signals:
    void backChooseScene();
};

#endif // MINESSWEEPERSCENE_H
