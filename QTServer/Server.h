#pragma once
#include "User.h"
#include <qtcpserver.h>
#include <qvector.h>
#include <vector>
#include "Socket.h"
#include "variant"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QDateTime>
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
	QSqlDatabase db;
	QByteArray Data;
	quint16 nextBlockSize;
	std::vector <User*> users;
	std::vector<GroupChat*> chats;
	std::vector<Message*> messages;
	void SendToClient(QString str);
	void SendToClient(QString str, QString id);
	void SendToClient(QString str, QStringList listOfId);
	void SendToClient(QString str1, QString str2, QString id1,QString id2);
	QString checkUser(QString nick, QString pass);
	bool checkUser(QString tel);
	QString checkContact(QString tel);
	Socket* findSocketById(QString id);
	//User* findUserById(QString id);
	//GroupChat* findChatById(QString id);
	QString AddChatOnServer(QString str);
	void AddUserOnServer(QString str);
	QString AddContactToUser(QString str);
	QStringList idOfUsersToIdOfSockets(QStringList idOfUsers);
	void deleteUser(QString id);
	void createNewUserOnServer(QString tel,QString nick, QString pass);
	void findAndUpdateUser(QString tel, QString nick, QString pass);
	void recordUserIsOnline(QString userId,QString socketId);
	QString getListOfChatsByIdUser(QString userId);
	QString getListOfMessagesByIdChat(QString chatId);
	QString addMessageOnServer(QString str);
	QStringList getListOfParticipatorsByIdChat(QString chatId);
	QString getContactsByIdUser(QString userId);
	QString forwardMessageOnServer(QString str);

public slots:
	void incomingConnection(qintptr socketDescriptor);
	void readyRead();
	void deleteSocket(QString i);//удаляет сокет из вектора сокетов когда клиент отключается от сервера
};

