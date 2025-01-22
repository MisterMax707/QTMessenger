#include "SocketManager.h"
#include "InterfaceLogin.h"
void SocketManager::connectToServer(const QString& host, quint16 port)
{
	socket->connectToHost(host, port);

}
void SocketManager::sendToServer(QString str)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << quint16(0) << str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));
	socket->write(Data);

}
void SocketManager::readyRead()
{
	socket = (QTcpSocket*)sender();
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_6_2);
	if (in.status() == QDataStream::Ok)
	{
		for (;;)
		{
			if (nextBlockSize == 0)
			{
				if (socket->bytesAvailable() < 2)
					break;
				in >> nextBlockSize;

			}
			if (socket->bytesAvailable() > nextBlockSize)
				break;

			QString str;
			in >> str;
			QString codeWord = str.left(str.indexOf(' '));
			str = str.mid(str.indexOf(' ') + 1);
			if (codeWord == "LOGIN_ANSWER")
			{
				if (str == "Error")
				{
					
					emit signalErrorNoSuchUser();
					socket->disconnect()	;
				}
				else
				{
					emit signalCreateMainWindow(str, this);//передаем InterfaceWindow id пользователя(в данном случае str это id пользователя) и указатель на SocketManager(он один у всего приложения
					sendToServer("LIST_OF_CHATS "+str);
					

				}
			}
			else if (codeWord == "LIST_OF_CHATS_ANSWER")
			{
				emit signalTransmitChatsToForm(str);
			}
			else if (codeWord == "LIST_OF_CONTACTS_ANSWER")
			{
				emit signalTransmitContactsToForm(str);
			}
			else if (codeWord == "ADD_CHAT_ANSWER")
			{
				emit signalAddChatToForm(str);
			}
			else if (codeWord == "LIST_OF_MESSAGES_ANSWER")
			{
				emit signalTransmitMessangesToForm(str);
			}
			else if (codeWord == "ADD_MESSAGE_ANSWER")
			{
				emit signalAddMessageToForm(str);
			}
			break;
		}


	}
	else
	{
		//написать где то на форме ошибка чтения данных

	}
	nextBlockSize = 0;
}

SocketManager::SocketManager() {
	socket = new QTcpSocket;
	connect(socket, &QTcpSocket::readyRead, this, &SocketManager::readyRead);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
	
	
	nextBlockSize = 0;
}
