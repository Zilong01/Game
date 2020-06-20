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
    int getNumOfMines()const{return numOfMines;}
    int getNumOfFlags()const{return numOfFlag;}
    void resetMapSize(int row_,int col_,int numOfMines_);
signals:
    void gameOver();
    void gameWin();
    void firstClickSignal();
    void flagChangeSignal();

private:
    int row;
    int col;
    int numOfMines;
    int numOfFlag=0;

    void changeFlag(int x,int y);
    void checkWin();


};

#endif // MINESSWEEPERLOGIC_H
