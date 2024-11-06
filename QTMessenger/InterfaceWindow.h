#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_InterfaceWindow.h"
#include "User.h"
#include <qscrollarea.h>
#include "GroupChat.h"
#include "ContactChat.h"
#include "InterfaceChat.h"
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
    
signals:
    void signalpushCreateGroupChat(QString name);
    void signalOpenAddWidget();
    void signalBackToMainWindow();
    void signalAddChatToForm(QString name, GroupChat* chat);
    void signalInicializateChat(GroupChat* chat,QString name);
     
public slots:
    void initializationUser(User* newUser, QString name);
    void createGroupChat(QString name);
    void pushAdd();
    void openAddWidget();
    void openMainWindow();
    void openEnterName();
    void pushOkCreateGroupChat();
    void addChatToForm(QString name, GroupChat* chat);
    void openGroupChat(/*GroupChat* chat*/);
    void openChat(ContactChat& chat);

};
 