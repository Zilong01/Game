#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#pragma execution_character_set("utf-8")
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
   MyPushButton(QString firstImg,QString secondImg="");
    void btnShow();//点击按钮的动画
    void reSizeBtn(int,int);//重新设置按钮的大小
    void btnMusic(QString);
private:
   QString Img1;
   QString Img2;
signals:

};

#endif // MYPUSHBUTTON_H
