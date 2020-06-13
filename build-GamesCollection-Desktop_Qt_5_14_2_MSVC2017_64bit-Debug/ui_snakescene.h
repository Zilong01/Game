/********************************************************************************
** Form generated from reading UI file 'snakescene.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAKESCENE_H
#define UI_SNAKESCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SnakeScene
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SnakeScene)
    {
        if (SnakeScene->objectName().isEmpty())
            SnakeScene->setObjectName(QString::fromUtf8("SnakeScene"));
        SnakeScene->resize(800, 600);
        menubar = new QMenuBar(SnakeScene);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        SnakeScene->setMenuBar(menubar);
        centralwidget = new QWidget(SnakeScene);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SnakeScene->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SnakeScene);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SnakeScene->setStatusBar(statusbar);

        retranslateUi(SnakeScene);

        QMetaObject::connectSlotsByName(SnakeScene);
    } // setupUi

    void retranslateUi(QMainWindow *SnakeScene)
    {
        SnakeScene->setWindowTitle(QCoreApplication::translate("SnakeScene", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SnakeScene: public Ui_SnakeScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAKESCENE_H
