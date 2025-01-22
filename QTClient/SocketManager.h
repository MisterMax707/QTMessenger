#pragma once

#include <qtcpserver.h>
#include <qtcpsocket.h>



class SocketManager :public QObject
{
	Q_OBJECT
private:
	
	QTcpSocket* socket;
	QByteArray Data;
	quint16 nextBlockSize;
public:
	SocketManager();
	void connectToServer(const QString& host, quint16 port);
	void sendToServer(QString str);
signals:
	void signalCreateMainWindow(QString idOfUser, SocketManager* socket);
	void signalErrorNoSuchUser();
	void signalCloseInterfaceLogin();
	void signalTransmitChatsToForm(QString str);
	void signalTransmitContactsToForm(QString str);
	void signalAddChatToForm(QString str);
	void signalAddMessageToForm(QString str);
	void signalTransmitMessangesToForm(QString str);
	//void signalCreateChatWindow(QString idOfChat,QString name, SocketManager* socket);
private slots:
	void readyRead();
};

