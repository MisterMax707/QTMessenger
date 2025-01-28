#include "SocketManager.h"



SocketManager::SocketManager()
{
	socket = new QTcpSocket;
	connect(socket, &QTcpSocket::readyRead, this, &SocketManager::readyRead);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
	connectToServer();

	nextBlockSize = 0;
}

void SocketManager::connectToServer()
{
	socket->connectToHost(host, port);
}


void SocketManager::sendToServer(const cod::CodeWord& cd, const OptInfoWord& word = std::nullopt, const OptInfoNum& number = std::nullopt)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << quint16(0) << cd << word << number;
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
			else if (codeWord == "REGISTRATION_ANSWER")
			{
				emit signalRegistrationSuccess();
				socket->disconnect();
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


QDataStream& operator<<(QDataStream& out, const cod::CodeWord& value) {
	return out << static_cast<quint8>(value); // Преобразуем в байт
}

QDataStream& operator>>(QDataStream& in, cod::CodeWord& value) {
	quint8 byteValue;
	in >> byteValue;
	value = static_cast<cod::CodeWord>(byteValue); // Преобразуем обратно в enum
	return in;
}