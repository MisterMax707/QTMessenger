/********************************************************************************
** Form generated from reading UI file 'InterfaceWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEWINDOW_H
#define UI_INTERFACEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceWindowClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InterfaceWindowClass)
    {
        if (InterfaceWindowClass->objectName().isEmpty())
            InterfaceWindowClass->setObjectName("InterfaceWindowClass");
        InterfaceWindowClass->resize(563, 563);
        InterfaceWindowClass->setMinimumSize(QSize(563, 563));
        InterfaceWindowClass->setMaximumSize(QSize(563, 563));
        centralWidget = new QWidget(InterfaceWindowClass);
        centralWidget->setObjectName("centralWidget");
        InterfaceWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InterfaceWindowClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 563, 21));
        InterfaceWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InterfaceWindowClass);
        mainToolBar->setObjectName("mainToolBar");
        InterfaceWindowClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(InterfaceWindowClass);
        statusBar->setObjectName("statusBar");
        InterfaceWindowClass->setStatusBar(statusBar);

        retranslateUi(InterfaceWindowClass);

        QMetaObject::connectSlotsByName(InterfaceWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *InterfaceWindowClass)
    {
        InterfaceWindowClass->setWindowTitle(QCoreApplication::translate("InterfaceWindowClass", "InterfaceWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceWindowClass: public Ui_InterfaceWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEWINDOW_H
