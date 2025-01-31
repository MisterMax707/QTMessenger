#pragma once
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qmap.h>
#include <optional>
#include "../include/GlobalFile/CodeWord.h"
#include "../include/GlobalFile/InformationWord.h"
#include "../include/GlobalFile/InformationNumber.h"

class SocketManager :public QObject
{
	Q_OBJECT

private:
	const QString host = "127.0.0.1";
	const quint16 port = 2323;
	QTcpSocket* socket;
	QByteArray Data;
	quint16 nextBlockSize;
	QMap<cod::CodeWord, void (SocketManager::*)(const QVector<QString>&, const QVector<QString>&)> actionKey;

	void performAction_LoginAnswer(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_RegistrationAnswer(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_ListOfChatAnswer(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_ListOfMessagesAnswer(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_ListOfContactsAnswer(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_AddChatAnswer(const QVector<QString>& word, const QVector<QString>& number);
	void performAction_AddMessageAnswer(const QVector<QString>& word, const QVector<QString>& number);

public:
	SocketManager();
	void connectToServer();
	void sendToServer(const cod::CodeWord& cd, const OptInfoWord& word, const OptInfoNum& number);

signals:
	void signalCreateMainWindow(QString idOfUser, SocketManager* socket);
	void signalErrorNoSuchUser();
	void signalCloseInterfaceLogin();

	void signalTransmitChatsToForm(const QVector<QString>& word, const QVector<QString>& number);

	void signalTransmitContactsToForm(const QVector<QString>& word, const QVector<QString>& number);

	void signalAddChatToForm(const QVector<QString>& word, const QVector<QString>& number);

	void signalAddMessageToForm(QString str);
	void signalTransmitMessangesToForm(QString str);
	void signalRegistrationSuccess();
	//void signalCreateChatWindow(QString idOfChat,QString name, SocketManager* socket);

private slots:
	void readyRead();
	void startRead(QDataStream& in);
};

