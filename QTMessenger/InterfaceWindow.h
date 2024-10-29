#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_InterfaceWindow.h"
#include "User.h"

class InterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    InterfaceWindow(QWidget* parent = nullptr);
    ~InterfaceWindow();
    
private:
    Ui::InterfaceWindowClass ui;
    User* user;
signals:
    void signalpushCreateGroup(QString name);
    void signalOpenAddWidget();
    void signalBackToMainWindow();
     
public slots:
    void inicialisationUser(QString name, QString password);
    void createGroup(QString name);
    void pushAdd();
    void openAddWidget();
    void openMainWindow();
    void openEnterName();
    void pushOkCreateGroup();
};
 