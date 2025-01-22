#pragma once
#include "qtcpsocket.h"
/*
* Данный класс реализован для того, чтобы присвоить каждому сокету уникальный номер, 
что требуется для ответов на запросы конкретным клиентам и для удаления конкретных сокетов из списка на сервере
*/
class Socket :public QTcpSocket
{
	Q_OBJECT
public:
	QString id;
	QString userId;
	Socket(QObject* parent = nullptr) :QTcpSocket(parent)
	{
		id = QString::number(count++);
		connect(this, &Socket::disconnected, this, &Socket::returnIdToServer);
	};

private:
	static inline unsigned count{};
signals:
	void signalDeleteSocket(QString id);
public slots:
	void returnIdToServer() {//слот запускается при отключении сокета от сервера и возвращает на сервер id отключенного сокета
		emit signalDeleteSocket(id);
	};
};

