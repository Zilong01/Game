/********************************************************************************
** Form generated from reading UI file 'minesdiffset.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINESDIFFSET_H
#define UI_MINESDIFFSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MinesDiffSet
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MinesDiffSet)
    {
        if (MinesDiffSet->objectName().isEmpty())
            MinesDiffSet->setObjectName(QString::fromUtf8("MinesDiffSet"));
        MinesDiffSet->resize(800, 600);
        menubar = new QMenuBar(MinesDiffSet);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        MinesDiffSet->setMenuBar(menubar);
        centralwidget = new QWidget(MinesDiffSet);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MinesDiffSet->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MinesDiffSet);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MinesDiffSet->setStatusBar(statusbar);

        retranslateUi(MinesDiffSet);

        QMetaObject::connectSlotsByName(MinesDiffSet);
    } // setupUi

    void retranslateUi(QMainWindow *MinesDiffSet)
    {
        MinesDiffSet->setWindowTitle(QCoreApplication::translate("MinesDiffSet", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MinesDiffSet: public Ui_MinesDiffSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINESDIFFSET_H
