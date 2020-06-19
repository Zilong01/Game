#ifndef MINESSWEEPERLOGIC_H
#define MINESSWEEPERLOGIC_H

#include <QObject>
#include <QWidget>
#include "minesblock.h"
#include<vector>
using namespace std;
class MinesSweeperLogic : public QWidget
{
    Q_OBJECT
public:
    explicit MinesSweeperLogic(int row,int col,int numOfMines,QWidget *parent = nullptr);
    vector<vector<MinesBlock*>> map;
    void newMap();//生成新地图

    void showBlock(Point p);
    bool firstClick=true;
signals:
    void gameOver();
    void gameWin();

private:
    int row;
    int col;
    int numOfMines;

};

#endif // MINESSWEEPERLOGIC_H
