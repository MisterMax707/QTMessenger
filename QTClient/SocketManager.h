#pragma once
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <optional>
#include "../include/GlobalFile/CodeWord.h"
#include "../include/GlobalFile/InformationWord.h"
#include "../include/GlobalFile/InformationNumber.h"

using OptInfoWord = std::optional<InformationWord>;
using OptInfoNum = std::optional<InformationNumber>;

class SocketManager :public QObject
{
	Q_OBJECT

private:
	const QString host = "127.0.0.1";
	const quint16 port = 2323;
	QTcpSocket* socket;
	QByteArray Data;
	quint16 nextBlockSize;

public:
	SocketManager();
	void connectToServer();
	void sendToServer(const cod::CodeWord& cd, const OptInfoWord& word, const OptInfoNum& number);

signals:
	void signalCreateMainWindow(QString idOfUser, SocketManager* socket);
	void signalErrorNoSuchUser();
	void signalCloseInterfaceLogin();
	void signalTransmitChatsToForm(QString str);
	void signalTransmitContactsToForm(QString str);
	void signalAddChatToForm(QString str);
	void signalAddMessageToForm(QString str);
	void signalTransmitMessangesToForm(QString str);
	void signalRegistrationSuccess();
	//void signalCreateChatWindow(QString idOfChat,QString name, SocketManager* socket);

private slots:
	void readyRead();
};

