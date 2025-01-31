#pragma once
#include <qtcpserver.h>
#include <qvector.h>
#include <QMap>
#include "Socket.h"
#include "variant"
#include "User.h"
#include "../include/GlobalFile/CodeWord.h"
#include "../include/GlobalFile/InformationWord.h"
#include "../include/GlobalFile/InformationNumber.h"

using ReturnType = std::variant<Socket*, QString>;
//using ServerMethodPtr = void (Server::*)(const QVector<QString>&, const QVector<QString>&);
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
	QByteArray Data;
	quint16 nextBlockSize;

	std::vector <User*> users;
	QVector<GroupChat*> chats;
	std::vector<Message*> messages;
	QMap<cod::CodeWord, void (Server::*)(const QVector<QString>&, const QVector<QString>&)> actionKey;

	//void SendToClient(QString str);
	//void SendToClient(QString str, QString id);
	//void SendToClient(QString str, QStringList listOfId);

	void SendToClient(const cod::CodeWord& cod, OptInfoWord word, OptInfoNum number, OptInfoNum idSocket);


	//QString checkUser(QString tel);
	Socket* findSocketById(QString id);
	User* findUserById(QString id);
	GroupChat* findChatById(QString id);

	void AddContactToUser(QString str);
	QStringList idOfUsersToIdOfSockets(QStringList idOfUsers);


	void performAction_Login(const QVector<QString>& word, const QVector<QString>& number);
	QString getIdOfLoggedUser(QString nick, QString pass);

	void performAction_Registration(const QVector<QString>& word, const QVector<QString>& number);
	void AddUserOnServer(const QVector<QString>& word);

	void performAction_ListOfChat(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_ListOfMessages(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_ListOfContacts(const QVector<QString>& word, const QVector<QString>& number);

	void performAction_AddChat(const QVector<QString>& word, const QVector<QString>& number);
	void AddChatOnServer(const QVector<QString>& word, const QVector<QString>& number);
	void addChatForSelectedUsers(const QVector<QString>& number);
	inline QString getIdOfNewGroupChat();

	void performAction_AddContact(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_AddMessage(const QVector<QString>& word, const QVector<QString>& number);
	

public slots:
	void incomingConnection(qintptr socketDescriptor);
	void readyRead();
	void startRead(QDataStream& in);
	void deleteSocket(QString i);//удаляет сокет из вектора сокетов когда клиент отключается от сервера
};

