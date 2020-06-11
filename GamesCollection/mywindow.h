#ifndef MYWINDOW_H
#define MYWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>

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

private:

};

#endif // MYWINDOW_H
