#ifndef CHOOSEGAMESCENE_H
#define CHOOSEGAMESCENE_H
#include<QPaintEvent>
#include <QMainWindow>
#include"mywindow.h"
#include"mypushbutton.h"
#include"snakescene.h"
#include<QSound>
#include"tetrisscene.h"
#include"minessweeperscene.h"
namespace Ui {
class ChooseGameScene;
}

class ChooseGameScene : public MyWindow
{
    Q_OBJECT

public:
    explicit ChooseGameScene(QWidget *parent = nullptr);
    ~ChooseGameScene();

    void paintEvent(QPaintEvent* e)override;

private:
    //Ui::ChooseGameScene *ui;
    SnakeScene *gameSnake=nullptr;
    TetrisScene *gameTetris=nullptr;
    MinesSweeperScene *gameMines=nullptr;
    //QSound *playSound=nullptr;
};

#endif // CHOOSEGAMESCENE_H
