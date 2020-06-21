/********************************************************************************
** Form generated from reading UI file 'infowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOWINDOW_H
#define UI_INFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *SnakePage;
    QVBoxLayout *verticalLayout;
    QPushButton *snakeBtn;
    QScrollArea *scrollAreaSnake;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *TetrisPage;
    QVBoxLayout *verticalLayout_2;
    QPushButton *tetrisBtn;
    QScrollArea *scrollAreaTetris;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *MinesPage;
    QVBoxLayout *verticalLayout_3;
    QPushButton *minesBtn;
    QScrollArea *scrollAreaMines;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *meneFile;

    void setupUi(QMainWindow *InfoWindow)
    {
        if (InfoWindow->objectName().isEmpty())
            InfoWindow->setObjectName(QString::fromUtf8("InfoWindow"));
        InfoWindow->resize(537, 287);
        centralwidget = new QWidget(InfoWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 541, 271));
        SnakePage = new QWidget();
        SnakePage->setObjectName(QString::fromUtf8("SnakePage"));
        verticalLayout = new QVBoxLayout(SnakePage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        snakeBtn = new QPushButton(SnakePage);
        snakeBtn->setObjectName(QString::fromUtf8("snakeBtn"));

        verticalLayout->addWidget(snakeBtn);

        scrollAreaSnake = new QScrollArea(SnakePage);
        scrollAreaSnake->setObjectName(QString::fromUtf8("scrollAreaSnake"));
        scrollAreaSnake->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 521, 222));
        scrollAreaSnake->setWidget(scrollAreaWidgetContents_3);

        verticalLayout->addWidget(scrollAreaSnake);

        stackedWidget->addWidget(SnakePage);
        TetrisPage = new QWidget();
        TetrisPage->setObjectName(QString::fromUtf8("TetrisPage"));
        verticalLayout_2 = new QVBoxLayout(TetrisPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tetrisBtn = new QPushButton(TetrisPage);
        tetrisBtn->setObjectName(QString::fromUtf8("tetrisBtn"));

        verticalLayout_2->addWidget(tetrisBtn);

        scrollAreaTetris = new QScrollArea(TetrisPage);
        scrollAreaTetris->setObjectName(QString::fromUtf8("scrollAreaTetris"));
        scrollAreaTetris->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 521, 222));
        scrollAreaTetris->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollAreaTetris);

        stackedWidget->addWidget(TetrisPage);
        MinesPage = new QWidget();
        MinesPage->setObjectName(QString::fromUtf8("MinesPage"));
        verticalLayout_3 = new QVBoxLayout(MinesPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        minesBtn = new QPushButton(MinesPage);
        minesBtn->setObjectName(QString::fromUtf8("minesBtn"));

        verticalLayout_3->addWidget(minesBtn);

        scrollAreaMines = new QScrollArea(MinesPage);
        scrollAreaMines->setObjectName(QString::fromUtf8("scrollAreaMines"));
        scrollAreaMines->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 521, 222));
        scrollAreaMines->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollAreaMines);

        stackedWidget->addWidget(MinesPage);
        InfoWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(InfoWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 537, 23));
        meneFile = new QMenu(menuBar);
        meneFile->setObjectName(QString::fromUtf8("meneFile"));
        InfoWindow->setMenuBar(menuBar);

        menuBar->addAction(meneFile->menuAction());

        retranslateUi(InfoWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(InfoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *InfoWindow)
    {
        InfoWindow->setWindowTitle(QCoreApplication::translate("InfoWindow", "MainWindow", nullptr));
        snakeBtn->setText(QCoreApplication::translate("InfoWindow", "\350\264\252\345\220\203\350\233\207\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        tetrisBtn->setText(QCoreApplication::translate("InfoWindow", "\344\277\204\347\275\227\346\226\257\346\226\271\345\235\227\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        minesBtn->setText(QCoreApplication::translate("InfoWindow", "\346\211\253\351\233\267\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        meneFile->setTitle(QCoreApplication::translate("InfoWindow", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoWindow: public Ui_InfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOWINDOW_H
