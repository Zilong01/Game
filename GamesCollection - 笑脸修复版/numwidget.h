#ifndef NUMWIDGET_H
#define NUMWIDGET_H

#include <QWidget>
#pragma execution_character_set("utf-8")
namespace Ui {
class NumWidget;
}

class NumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NumWidget(QWidget *parent = nullptr);
    ~NumWidget();

    void setMinNum(int num);
    void setMaxNum(int num);
   // int getNum();

signals:
    void getNumChange(int);

private:
    Ui::NumWidget *ui;
};

#endif // NUMWIDGET_H
