#pragma once
#include "../include/GlobalFile/CodeWord.h"
#include <qtcpserver.h>
#include <qvector.h>
#include <QMap>
#include "Socket.h"
#include "variant"
#include "User.h"
using ReturnType = std::variant<Socket*, QString>;
/*
*Кодовые слова
* LOGIN - ПРИШЕЛ ЛОГИН И ПАРОЛЬ ЧЕРЕЗ ПРОБЕЛ. НАЙТИ ПОЛЬЗОВАТЕЛЯ С ТАКИМИ ДАННЫМИ И ВЫДАТЬ ID. ВЫБРАТЬ ФУНКЦИЮ checkUser()
* LOGIN_ANSWER - ОТВЕТ НА ЗАПРОС ID ПОЛЬЗОВАТЕЛЯ В БАЗЕ ЧЕРЕЗ ЛОГИН И ПАРОЛЬ.
*/
class Server:public QTcpServer
{
	Q_OBJECT

public:
	Server();
	Socket* socket;

private:
	QVector<Socket*> Sockets;
	QMap<cod::CodeWord, void (Server::*)()> actionKey;
	QByteArray Data;
	quint16 nextBlockSize;

	std::vector <User*> users;
	std::vector<GroupChat*> chats;
	std::vector<Message*> messages;
	void SendToClient(QString str);
	void SendToClient(QString str, QString id);
	void SendToClient(QString str, QStringList listOfId);
	QString checkUser(QString nick, QString pass);
	QString checkUser(QString tel);
	Socket* findSocketById(QString id);
	User* findUserById(QString id);
	GroupChat* findChatById(QString id);
	QString AddChatOnServer(QString str);
	void AddUserOnServer(QString str);
	void AddContactToUser(QString str);
	QStringList idOfUsersToIdOfSockets(QStringList idOfUsers);

	void performAction_Login();
	void performAction_Registration();
	void performAction_ListOfChat();
	void performAction_ListOfMessages();
	void performAction_ListOfContacts();
	void performAction_AddChat();
	void performAction_AddContact();
	void performAction_AddMessage();
	

public slots:
	void incomingConnection(qintptr socketDescriptor);
	void readyRead();
	void startRead(QDataStream& in);
	void deleteSocket(QString i);//удаляет сокет из вектора сокетов когда клиент отключается от сервера
};

