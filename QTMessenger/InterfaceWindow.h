#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InterfaceWindow.h"

class InterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    InterfaceWindow(QWidget* parent = nullptr);
    ~InterfaceWindow();

private:
    Ui::InterfaceWindowClass ui;
};
