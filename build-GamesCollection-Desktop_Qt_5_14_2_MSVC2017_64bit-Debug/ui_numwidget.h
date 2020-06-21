/********************************************************************************
** Form generated from reading UI file 'numwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMWIDGET_H
#define UI_NUMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NumWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox;
    QSlider *horizontalSlider;

    void setupUi(QWidget *NumWidget)
    {
        if (NumWidget->objectName().isEmpty())
            NumWidget->setObjectName(QString::fromUtf8("NumWidget"));
        NumWidget->resize(159, 40);
        horizontalLayout_2 = new QHBoxLayout(NumWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        spinBox = new QSpinBox(NumWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_2->addWidget(spinBox);

        horizontalSlider = new QSlider(NumWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);


        retranslateUi(NumWidget);

        QMetaObject::connectSlotsByName(NumWidget);
    } // setupUi

    void retranslateUi(QWidget *NumWidget)
    {
        NumWidget->setWindowTitle(QCoreApplication::translate("NumWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NumWidget: public Ui_NumWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMWIDGET_H
