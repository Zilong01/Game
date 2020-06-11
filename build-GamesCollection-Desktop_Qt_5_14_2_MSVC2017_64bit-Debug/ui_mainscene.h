/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScene
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionPause;
    QAction *actionquit;
    QAction *actionHelpThis;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_help;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainScene)
    {
        if (MainScene->objectName().isEmpty())
            MainScene->setObjectName(QString::fromUtf8("MainScene"));
        MainScene->resize(800, 600);
        MainScene->setLayoutDirection(Qt::LeftToRight);
        actionOpen = new QAction(MainScene);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainScene);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionPause = new QAction(MainScene);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionquit = new QAction(MainScene);
        actionquit->setObjectName(QString::fromUtf8("actionquit"));
        actionHelpThis = new QAction(MainScene);
        actionHelpThis->setObjectName(QString::fromUtf8("actionHelpThis"));
        centralwidget = new QWidget(MainScene);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainScene);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_help = new QMenu(menubar);
        menu_help->setObjectName(QString::fromUtf8("menu_help"));
        menu_help->setLayoutDirection(Qt::LeftToRight);
        MainScene->setMenuBar(menubar);
        statusbar = new QStatusBar(MainScene);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainScene->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_help->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionPause);
        menu->addSeparator();
        menu->addAction(actionquit);
        menu_help->addAction(actionHelpThis);

        retranslateUi(MainScene);

        QMetaObject::connectSlotsByName(MainScene);
    } // setupUi

    void retranslateUi(QMainWindow *MainScene)
    {
        MainScene->setWindowTitle(QCoreApplication::translate("MainScene", "MainScene", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainScene", "\346\211\223\345\274\200", nullptr));
        actionSave->setText(QCoreApplication::translate("MainScene", "\344\277\235\345\255\230", nullptr));
        actionPause->setText(QCoreApplication::translate("MainScene", "\346\232\202\345\201\234", nullptr));
        actionquit->setText(QCoreApplication::translate("MainScene", "\351\200\200\345\207\272", nullptr));
        actionHelpThis->setText(QCoreApplication::translate("MainScene", "\345\275\223\345\211\215\346\270\270\346\210\217\345\270\256\345\212\251", nullptr));
        menu->setTitle(QCoreApplication::translate("MainScene", "\350\217\234\345\215\225", nullptr));
        menu_help->setTitle(QCoreApplication::translate("MainScene", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainScene: public Ui_MainScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H
