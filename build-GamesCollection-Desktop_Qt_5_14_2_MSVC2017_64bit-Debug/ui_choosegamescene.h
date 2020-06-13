/********************************************************************************
** Form generated from reading UI file 'choosegamescene.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEGAMESCENE_H
#define UI_CHOOSEGAMESCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseGameScene
{
public:
    QAction *quitAction;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChooseGameScene)
    {
        if (ChooseGameScene->objectName().isEmpty())
            ChooseGameScene->setObjectName(QString::fromUtf8("ChooseGameScene"));
        ChooseGameScene->resize(450, 700);
        quitAction = new QAction(ChooseGameScene);
        quitAction->setObjectName(QString::fromUtf8("quitAction"));
        centralwidget = new QWidget(ChooseGameScene);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ChooseGameScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChooseGameScene);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 450, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        ChooseGameScene->setMenuBar(menubar);
        statusbar = new QStatusBar(ChooseGameScene);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ChooseGameScene->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(quitAction);

        retranslateUi(ChooseGameScene);

        QMetaObject::connectSlotsByName(ChooseGameScene);
    } // setupUi

    void retranslateUi(QMainWindow *ChooseGameScene)
    {
        ChooseGameScene->setWindowTitle(QCoreApplication::translate("ChooseGameScene", "MainWindow", nullptr));
        quitAction->setText(QCoreApplication::translate("ChooseGameScene", "\345\205\263\351\227\255", nullptr));
        menu->setTitle(QCoreApplication::translate("ChooseGameScene", "\345\274\200\345\247\213", nullptr));
        menu_2->setTitle(QCoreApplication::translate("ChooseGameScene", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseGameScene: public Ui_ChooseGameScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEGAMESCENE_H
