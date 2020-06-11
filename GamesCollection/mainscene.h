#ifndef MAINSCENE_H
#define MAINSCENE_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include<mywindow.h>
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class MainScene : public MyWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
private:
};
#endif // MAINSCENE_H
