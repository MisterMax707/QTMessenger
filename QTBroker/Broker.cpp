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

	actionMap[Registration] = &Broker::connectToLoginServer;

	connect(this, &QTcpServer::newConnection, this, &Broker::onNewConnection);
}

Broker::~Broker()
{}

void Broker::onNewConnection()
{
	QTcpSocket* clientSocket = nextPendingConnection();
	clients.push_back(clientSocket);

	connect(this, &Broker::signalCallingAnAccessKeyAction, this, &Broker::callingAnAccessKeyAction);
	connect(this, &Broker::signalSendDataOnLoginServer, this, &Broker::sendDataOnLoginServer);
	//connect(clientSocket, &QTcpSocket::connected, this, &Broker::sendDataOnLoginServer);
	connect(clientSocket, &QTcpSocket::readyRead, this, &Broker::onReadyRead);
	connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void Broker::onReadyRead()
{
	QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
	QByteArray data = clientSocket->readAll();
	QDataStream in(clientSocket);
	in.setVersion(QDataStream::Qt_6_2);
	if (in.status() == QDataStream::Ok)
	{
		Key key;
		in >> key;
		emit signalCallingAnAccessKeyAction(key, data);
	}
}

void Broker::callingAnAccessKeyAction(Key key, QByteArray data)
{
	if (actionMap.contains(key)) {
		(this->*actionMap[key])(data);
	}
	else {
		qDebug() << "Key does not exist";
	}
}

void Broker::connectToLoginServer(QByteArray data)
{
	QTcpSocket* serverSocket = new QTcpSocket(this);
	serverSocket->connectToHost("127.0.0.1", 1000);
	emit signalSendDataOnLoginServer(serverSocket, data);
}

void Broker::sendDataOnLoginServer(QTcpSocket* serverSocket, QByteArray data)
{
	if (!data.isEmpty()) {
		serverSocket->write(data);
		qDebug() << "data to send to server";
	}
	else {
		qDebug() << "No data to send to server";
	}
}


