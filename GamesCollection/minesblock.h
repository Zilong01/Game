﻿#ifndef MINESBLOCK_H
#define MINESBLOCK_H

#include"mywindow.h"
#include <QLabel>
#define MINESUNIT 30

//本类继承QLabel 来构造地雷块
class MinesBlock : public QLabel
{
    Q_OBJECT
public:
    //explicit MinesBlock(QWidget *parent = nullptr);
    explicit MinesBlock(Point p,QWidget *parent = nullptr);
    bool isMine;//是否为地雷
    bool isShow;//是否被点开
    bool isFlag;//被插旗子

    int number;//存储的数字
    Point pos;

    void showBlock(Point p);//递归翻开周围


signals:

};

#endif // MINESBLOCK_H