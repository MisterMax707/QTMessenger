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
    InterfaceWindow(QWidget* parent = nullptr, User* newUser = nullptr, QString name = nullptr);
    ~InterfaceWindow();
    
private:
    Ui::InterfaceWindowClass ui;
    User* user;
    InterfaceChat* IC;
    
signals:
    void signalpushCreateGroupChat(QString name);
    void signalOpenAddWidget();
    void signalBackToMainWindow();
    void signalAddChatToForm(QString name, GroupChat* chat);
    void signalInicializateChat(GroupChat* chat, QString user, QString name);
    void signalInicializateContactChat(ContactChat* chat, QString name, User* user1, User* user2);
    void signalCreateContact();
    void signalAddContactToForm(QString nick, Contact* contact);
     
public slots:
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
    void AddContactToForm(QString nick, Contact* contact);
    void pushCreateContact();
    void openContactChat();
};
 