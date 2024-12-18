#pragma once
#include <QtWidgets/QMainWindow>
#include <qscrollarea.h>
#include "ui_InterfaceWindow.h"
#include "InterfaceChat.h"
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
    QWidget* widget;
    QVBoxLayout* verticalLayout;
    QScrollArea* scrollArea;
    InterfaceChat* IC=new InterfaceChat();
    int chatHeight = 40;
    QWidget* widgetPage5;
    QVBoxLayout* verticalLayoutPage5;
    QScrollArea* scrollAreaPage5;
    
signals:
    void signalpushCreateGroupChat(QString name);
    void signalOpenAddWidget();
    void signalBackToMainWindow();
    void signalAddChatToForm(QString name, GroupChat* chat);
    void signalInicializateChat(GroupChat* chat, QString user, QString name);
    void signalCreateContact();
     
public slots:
    void initializationUser(User* newUser, QString name);
    void createGroupChat(QString name);
    void pushAdd();
    void openAddWidget();
    void openMainWindow();
    void openEnterNameGroupChat();
    void pushOkCreateGroupChat();
    void addChatToForm(QString name, GroupChat* chat);
    void openGroupChat(/*GroupChat* chat*/);
    void openChat(ContactChat& chat);
    void openInicializateContactPage();
    void createContact();
    void pushCreateContact();
    void openContactsList();
};
 