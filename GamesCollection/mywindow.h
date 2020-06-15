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
    void resizeWindow(int,int);
    QString getBackGroundPic()const{return backGroundPic;}

    void paintEvent(QPaintEvent *e)override;//我的窗口类 重写 用于绘制背景图片
    void setHelpContent(QString title, QString content, QString choose1, QString choose2);

    virtual void helpInfo();//帮助信息 虚函数 用于点击菜单栏帮助按钮的弹出信息
    QMenuBar* getMenuBar(){return bar;}
private:

    QMenuBar *bar;//菜单栏
    QString backGroundPic;
    //帮助信息
    QString helpTitle="帮助",helpContent="暂无帮助",helpChoose1="Yes",helpChoose2="Cancel";

};

#endif // MYWINDOW_H
