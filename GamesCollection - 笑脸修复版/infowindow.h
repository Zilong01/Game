#ifndef INFOWINDOW_H
#define INFOWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();

    void changePage(int page);

private:
    Ui::InfoWindow *ui;
};

#endif // INFOWINDOW_H
