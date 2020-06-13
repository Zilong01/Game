#include "snakescene.h"
#include "ui_snakescene.h"

SnakeScene::SnakeScene(QWidget *parent) :
    MyWindow(parent)//,
    //ui(new Ui::SnakeScene)
{
    //ui->setupUi(this);
    setBackGroundPic(QString(":/first/picture/beiJing3.jpg"));
    MyWindow(this);
    resizeWindow(700,450);
}

SnakeScene::~SnakeScene()
{
   // delete ui;
}
