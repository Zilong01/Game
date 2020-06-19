#ifndef MINESINFOBAR_H
#define MINESINFOBAR_H

#define NUMWIDTH 20
#define NUMHEIGHT 30

#include <QWidget>
#include<QLabel>
#include<QPushButton>

#include<QTime>
#include"mypushbutton.h"



//本类用于显示游戏场景中的时间等信息

class MinesInfoBar : public QWidget
{
    Q_OBJECT
public:
    explicit MinesInfoBar(QWidget *parent = nullptr);

    QWidget* screen[2];//用于展示三个数字的控件

    QLabel* screen1[3]={nullptr};//显示左边信息的屏幕中的信息
    QLabel* screen2[3]={nullptr};//右
    MyPushButton * face=nullptr;//中央的表情

    QTimer *timer=nullptr;//计时器
    QTime time;//时间
    int runningTime;//保存游戏运行是时间

    void reset();
    void changeScreen(QLabel** screen, int &num);
    void resetFace(int state);

    void infoBarResize(int width,int height);

signals:

};

#endif // MINESINFOBAR_H
