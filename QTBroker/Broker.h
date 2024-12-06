#pragma once
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <QVector.h>
#include <QMap.h>
#include <functional>

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
	QMap<Key, void (Broker::*)(QByteArray)> actionMap;

signals:
	void signalCallingAnAccessKeyAction(Key key, QByteArray data);
	void signalSendDataOnLoginServer(QTcpSocket* serverSocket, QByteArray data);

private slots:
	void onNewConnection();
	void onReadyRead();
	void callingAnAccessKeyAction(Key key, QByteArray data);
	void connectToLoginServer(QByteArray data);
	void sendDataOnLoginServer(QTcpSocket* serverSocket, QByteArray data);
};
