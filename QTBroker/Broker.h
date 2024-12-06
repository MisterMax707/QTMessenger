#pragma once
#include <QObject>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <QVector.h>
#include <QMap.h>

enum Key {
	Registration, 
	Confirm
};

class Broker  : public QTcpServer
{
	Q_OBJECT

public:
	Broker();
	~Broker();

private:
	QVector<QTcpSocket*> clients;
	QMap<Key, std::function<void()>> actionMap;

signals:
	void signalCallingAnAccessKeyAction(Key key);

private slots:
	void onNewConnection();
	void onReadyRead();
	void callingAnAccessKeyAction(Key key);
};
