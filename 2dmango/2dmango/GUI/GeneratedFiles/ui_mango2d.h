/********************************************************************************
** Form generated from reading UI file 'mango2d.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANGO2D_H
#define UI_MANGO2D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mango2dClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *Mango2dClass)
    {
        if (Mango2dClass->objectName().isEmpty())
            Mango2dClass->setObjectName(QStringLiteral("Mango2dClass"));
        Mango2dClass->resize(1280, 720);
        Mango2dClass->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(Mango2dClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Mango2dClass->setCentralWidget(centralWidget);

        retranslateUi(Mango2dClass);

        QMetaObject::connectSlotsByName(Mango2dClass);
    } // setupUi

    void retranslateUi(QMainWindow *Mango2dClass)
    {
        Mango2dClass->setWindowTitle(QApplication::translate("Mango2dClass", "Mango2d", 0));
    } // retranslateUi

};

namespace Ui {
    class Mango2dClass: public Ui_Mango2dClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANGO2D_H
