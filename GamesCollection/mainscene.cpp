#include "mainscene.h"
#include "ui_mainscene.h"
#include<QAction>
#include"mywindow.h"
#include<QPainter>
MainScene::MainScene(QWidget *parent)
    : MyWindow(parent)
{


}

MainScene::~MainScene()
{

}

void MainScene::paintEvent(QPaintEvent *e){
    QPainter painter(this);
}
