#include "Broker.h"

Broker::Broker()
{
	if (this->listen(QHostAddress::Any, 2323))
	{
		qDebug() << "server is running...";
	}
	else
	{
		qDebug() << "error";
	}

	actionMap[Registration] = ;

	connect(this, &QTcpServer::newConnection, this, &Broker::onNewConnection);
	listen(QHostAddress::Any, 2323);
}

Broker::~Broker()
{}

void Broker::onNewConnection()
{
	QTcpSocket* clientSocket = nextPendingConnection();
	clients.push_back(clientSocket);

	connect(this, &Broker::signalCallingAnAccessKeyAction, this, &callingAnAccessKeyAction);
	connect(clientSocket, &QTcpSocket::readyRead, this, &Broker::onReadyRead);
	connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void Broker::onReadyRead()
{
	QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
	QDataStream in(clientSocket);
	in.setVersion(QDataStream::Qt_6_2);
	if (in.status() == QDataStream::Ok)
	{
		Key key;
		in >> key;
		emit signalCallingAnAccessKeyAction(key);
	}
}

void Broker::callingAnAccessKeyAction(Key key)
{
	if (actionMap.contains(key)) {
		actionMap[key]();
	}
	else {
		qDebug() << "Key does not exist";
	}
}


