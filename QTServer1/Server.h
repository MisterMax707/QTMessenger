#pragma once
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qvector.h>
#include "MessageSender.h"


class Server :public QTcpServer
{
	Q_OBJECT

public:
	Server();
	QTcpSocket* socket;

private:
	QVector<QTcpSocket*> Sockets;
	QByteArray Data;
	MessageSender* messageSender;
	void SendToClient(QString str, QString nick, int id);

public slots:
	void incomingConnection(qintptr socketDescriptor);
	void readyRead();
};

