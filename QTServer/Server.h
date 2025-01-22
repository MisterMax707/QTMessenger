#pragma once
#include "User.h"
#include <qtcpserver.h>
#include <qvector.h>
#include <vector>
#include "Socket.h"
#include "variant"
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
	QByteArray Data;
	quint16 nextBlockSize;
	std::vector <User*> users;
	std::vector<GroupChat*> chats;
	std::vector<Message*> messages;
	void SendToClient(QString str);
	void SendToClient(QString str, QString id);
	void SendToClient(QString str, QStringList listOfId);
	QString checkUser(QString nick, QString pass);
	Socket* findSocketById(QString id);
	User* findUserById(QString id);
	GroupChat* findChatById(QString id);
	QString AddChatOnServer(QString str);
	QStringList idOfUsersToIdOfSockets(QStringList idOfUsers);
	
	

public slots:
	void incomingConnection(qintptr socketDescriptor);
	void readyRead();
	void deleteSocket(QString i);//удаляет сокет из вектора сокетов когда клиент отключается от сервера
};

