#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_InterfaceWindow.h"
#include "InterfaceChat.h"
#include "SocketManager.h"

class InterfaceWindow : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceWindow(QString id, SocketManager* socket, QWidget* parent = nullptr);
	~InterfaceWindow();

private:
	QString userId;
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
	void signalCreateChatWindow(QString idOfChat, QString name, QString idOfUser, SocketManager* socket);

public slots:
	// void initializationUser(User* newUser, QString name);
	 //void createGroupChat(QString name);

  /*   void openAddWidget();

	*/
	 //  void addChatToForm(QString name, GroupChat* chat);
	  // void openGroupChat(/*GroupChat* chat*/);
	 //  void openChat(ContactChat& chat);
	  /* void openInicializateContactPage();
	   
	   
	   void openContactChat();*/

	void downloadChats(QString str);
	void createListOfContacts(QString str);
	void pushAdd();
	void openMainWindow();
	void openEnterNameGroupChat();
	void pushOkCreateGroupChat();
	void addChat(QString str);
	void onGroupChatClicked(QListWidgetItem* item);
	void createChatWindow(QString id, QString name,QString userId,SocketManager* socket);
	void createContact();
	void pushCreateContact();
};
