#ifndef MYWINDOW_H
#define MYWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include<QPaintEvent>
namespace Ui {
class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

    static void setWindow(QMainWindow*);

    //背景图片
    void setBackGroundPic(QString);
    QString getBackGroundPic()const{return backGroundPic;}

    void paintEvent(QPaintEvent *e)override;//我的窗口类 重写 用于绘制背景图片
private:

    QString backGroundPic;

};

#endif // MYWINDOW_H
