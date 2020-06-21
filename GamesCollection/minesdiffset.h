#ifndef MINESDIFFSET_H
#define MINESDIFFSET_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include"numwidget.h"
#include<QPushButton>
namespace Ui {
class MinesDiffSet;
}

class MinesDiffSet : public QMainWindow
{
    Q_OBJECT

public:
    explicit MinesDiffSet(QWidget *parent = nullptr);
    ~MinesDiffSet();

    NumWidget* colChooseWidget=nullptr;
    NumWidget* rowChooseWidget=nullptr;
    NumWidget* minesChooseWidget=nullptr;

    QPushButton *btn_q=nullptr;

private:
    Ui::MinesDiffSet *ui;

    int UCol=0;
    int URow=0;
    int UMines=0;

public slots:

signals:
    void setCol(int colNum);
    void setRow(int rowNum);
    void setMines(int minesNum);
    void test();

};

#endif // MINESDIFFSET_H
