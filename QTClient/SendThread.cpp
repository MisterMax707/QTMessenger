#include "SendThread.h"

SendThread::SendThread(QTcpSocket* socket, const QString& str, QObject *parent)
	: QThread(parent), socket(socket), str(str)
{}

SendThread::~SendThread()
{}

void SendThread::run()
{
	QByteArray Data;
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << quint16(0) << str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));

	//QThread::msleep(15000);
	emit sendData(socket, Data);
}
