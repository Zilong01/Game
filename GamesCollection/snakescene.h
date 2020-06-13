#ifndef SNAKESCENE_H
#define SNAKESCENE_H

#include "mywindow.h"

namespace Ui {
class SnakeScene;
}

class SnakeScene : public MyWindow
{
    Q_OBJECT

public:
    explicit SnakeScene(QWidget *parent = nullptr);
    ~SnakeScene();

private:
 //   Ui::SnakeScene *ui;
};

#endif // SNAKESCENE_H
