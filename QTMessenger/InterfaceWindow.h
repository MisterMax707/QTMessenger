#pragma once
#include <QtWidgets/QMainWindow>
#include <qscrollarea.h>
#include "ui_InterfaceWindow.h"
#include "InterfaceChat.h"
#include "User.h"
#include <qtcpserver.h>
#include <qtcpsocket.h>


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
    QWidget* widgetPage2;
    QVBoxLayout* verticalLayoutPage2;
    QScrollArea* scrollAreaPage2;
    QTcpSocket* socket;
    QByteArray Data;
    
signals:
    void signalpushCreateGroupChat(QString name);
    void signalOpenAddWidget();
    void signalBackToMainWindow();
    void signalAddChatToForm(QString name, GroupChat* chat);
    void signalInicializateChat(GroupChat* chat, QString user, QString name);
    void signalInicializateContactChat(ContactChat* chat, QString name, User* user1, User* user2);
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
    void openContactChat();
    //для теста потом удалить
    void connectToServer();
    void readyRead();
    void sendToServer(QString str);

};
 