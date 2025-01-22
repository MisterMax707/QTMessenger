#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_InterfaceWindow.h"
#include "InterfaceChat.h"
#include "SocketManager.h"



class InterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    InterfaceWindow(QWidget* parent = nullptr);
    ~InterfaceWindow();
    
private:
    Ui::InterfaceWindowClass ui;
    SocketManager* socket;
    InterfaceChat* IC;
    QByteArray Data;
    
signals:
   /* void signalpushCreateGroupChat(QString name);
    void signalOpenAddWidget();
    void signalBackToMainWindow();*/
  //  void signalAddChatToForm(QString name, GroupChat* chat);
 //   void signalInicializateChat(GroupChat* chat, QString user, QString name);
    //void signalInicializateContactChat(ContactChat* chat, QString name, User* user1, User* user2);
   // void signalCreateContact();
     
public slots:
   // void initializationUser(User* newUser, QString name);
    //void createGroupChat(QString name);
   /* void pushAdd();
    void openAddWidget();
    void openMainWindow();
    void openEnterNameGroupChat();
    void pushOkCreateGroupChat();*/
  //  void addChatToForm(QString name, GroupChat* chat);
   // void openGroupChat(/*GroupChat* chat*/);
  //  void openChat(ContactChat& chat);
   /* void openInicializateContactPage();
    void createContact();
    void pushCreateContact();
    void openContactChat();*/
    void setUserId(QString idOfUser);
    void setSocket(SocketManager* socket);
    //для теста потом удалить
    

};
 