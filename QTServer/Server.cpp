#include "Server.h"


Server::Server() {
	if (this->listen(QHostAddress::Any, 2323))
	{
		qDebug() << "server is running...";
	}
	else
	{
		qDebug() << "error";

	}
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	socket = new QTcpSocket();
	socket->setSocketDescriptor(socketDescriptor);
	connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
	Sockets.push_back(socket);
	qDebug() << "client " << socketDescriptor<<" connected...";

}

void Server::readyRead()
{
	socket = ( QTcpSocket*)sender();
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_6_2);
	if (in.status() == QDataStream::Ok)
	{
		qDebug() << "read....";
		QString str;
		in >> str;
		qDebug() << str;
		SendToClient(str);

	}
	else
	{
		qDebug() << "DataStream Error";

	}

}


void Server::SendToClient(QString str)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << str;
	//socket->write(Data);
	for (int i = 0; i < Sockets.size(); i++) {
		Sockets[i]->write(Data);
	}
}