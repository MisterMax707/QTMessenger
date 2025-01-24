#pragma once
#include <QObject>
#include <QString>
#include <QThread>
#include <qtcpserver.h>
#include <qtcpsocket.h>

class SendThread  : public QThread
{
	Q_OBJECT

public:
	SendThread(QTcpSocket* socket, const QString& str, QObject *parent);
	~SendThread();

protected:
	void run() override;

private:
	QString str;
	QTcpSocket* socket;

signals:
	void sendData(QTcpSocket* socket, const QByteArray& data);
};
