#pragma once
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qvector.h>
class Server:public QTcpServer
{
	Q_OBJECT
public:
	Server();
	QTcpSocket* socket;
private:
	QVector<QTcpSocket*> Sockets;
	QByteArray Data;
	void SendToClient(QString str);
public slots:
	void incomingConnection(qintptr socketDescriptor);
	void readyRead();
};

