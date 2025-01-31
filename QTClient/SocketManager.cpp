#include "SocketManager.h"

SocketManager::SocketManager()
{
	socket = new QTcpSocket;
	connect(socket, &QTcpSocket::readyRead, this, &SocketManager::readyRead);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
	connectToServer();

	nextBlockSize = 0;

	actionKey[cod::CodeWord::LOGIN_ANSWER] = &SocketManager::performAction_LoginAnswer;
	actionKey[cod::CodeWord::REGISTRATION_ANSWER] = &SocketManager::performAction_RegistrationAnswer;
	actionKey[cod::CodeWord::LIST_OF_CHATS_ANSWER] = &SocketManager::performAction_ListOfChatAnswer;
	actionKey[cod::CodeWord::LIST_OF_MESSAGES_ANSWER] = &SocketManager::performAction_ListOfMessagesAnswer;
	actionKey[cod::CodeWord::LIST_OF_CONTACTS_ANSWER] = &SocketManager::performAction_ListOfContactsAnswer;
	actionKey[cod::CodeWord::ADD_CHAT_ANSWER] = &SocketManager::performAction_AddChatAnswer;
	//actionKey[cod::CodeWord::ADD_CONTACT_] = &SocketManager::performAction_;
	actionKey[cod::CodeWord::ADD_MESSAGE_ANSWER] = &SocketManager::performAction_AddMessageAnswer;
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
		startRead(in);
	}
	else
	{
		//написать где то на форме ошибка чтения данных
	}
	nextBlockSize = 0;
}

void SocketManager::startRead(QDataStream& in)
{
	while (true)
	{
		/////////////////
		if (nextBlockSize == 0)
		{
			if (socket->bytesAvailable() < 2)
				break;
			in >> nextBlockSize;

		}
		if (socket->bytesAvailable() > nextBlockSize)
			break;
		///////////////////

		cod::CodeWord key;
		InformationWord word;
		InformationNumber number;
		in >> key >> word >> number;

		QVector<QString> arrWord = word.createArrayWord<QVector, QString>();
		QVector<QString> arrNumber = number.createArrayNumber<QVector, QString>();
		if (actionKey.contains(key))
		{
			(this->*actionKey[key])(arrWord, arrNumber);
		}
		else
		{
			qDebug() << "Coding Data Error";
		}

		break;
	}
}

void SocketManager::performAction_LoginAnswer(const QVector<QString>& word, const QVector<QString>& number)
{
	QString idUs = number.last();
	if (idUs == "nan_error")
	{
		emit signalErrorNoSuchUser();
		socket->disconnect();
	}
	else
	{
		emit signalCreateMainWindow(idUs, this);//передаем InterfaceWindow id пользователя(в данном случае str это id пользователя) и указатель на SocketManager(он один у всего приложения
		InformationNumber thisId = idUs;
		sendToServer(cod::CodeWord::LIST_OF_CHATS, std::nullopt, thisId);
		//sendToServer("LIST_OF_CHATS " + str);
	}
}

void SocketManager::performAction_RegistrationAnswer(const QVector<QString>& word, const QVector<QString>& number)
{
	emit signalRegistrationSuccess();
	socket->disconnect();
}

void SocketManager::performAction_ListOfChatAnswer(const QVector<QString>& word, const QVector<QString>& number)
{
	emit signalTransmitChatsToForm(word, number);
}

void SocketManager::performAction_ListOfMessagesAnswer(const QVector<QString>& word, const QVector<QString>& number)
{
	//emit signalTransmitMessangesToForm(str);
}

void SocketManager::performAction_ListOfContactsAnswer(const QVector<QString>& word, const QVector<QString>& number)
{
	emit signalTransmitContactsToForm(word, number);
}

void SocketManager::performAction_AddChatAnswer(const QVector<QString>& word, const QVector<QString>& number)
{
	emit signalAddChatToForm(word, number);
}

void SocketManager::performAction_AddMessageAnswer(const QVector<QString>& word, const QVector<QString>& number)
{
	//emit signalAddMessageToForm(str);
}
