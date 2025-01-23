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
	nextBlockSize = 0;

	//автоматически добавляются два пользователя для отладки потом удалить
	users.push_back(new User("Max", "1", "89106337707"));//
	users.push_back(new User("Dan", "1", "i dont know Dans telephone"));
	users.push_back(new User("Darina", "1", "; sldfkg; sdlfg"));

	//users[0]->createGroupChat("a;dlkfjas;dkl");//

	users[0]->addContact("1", "Dan");
	users[0]->addContact("2", "Darina");
	users[1]->addContact("0", "Max");

}

void Server::incomingConnection(qintptr socketDescriptor)
{
	socket = new Socket();
	socket->setSocketDescriptor(socketDescriptor);
	connect(socket, &Socket::readyRead, this, &Server::readyRead);
	connect(socket, &Socket::signalDeleteSocket, this, &Server::deleteSocket);
	connect(socket, &Socket::disconnected, socket, &Socket::deleteLater);
	Sockets.push_back(socket);
	qDebug() << "client " << socketDescriptor << " connected...";

}

void Server::readyRead()
{
	socket = (Socket*)sender();
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
			qDebug() << "read....";
			QString str;
			in >> str;
			QString codeWord = str.left(str.indexOf(' '));
			str = str.mid(str.indexOf(' ') + 1);
			if (codeWord == "LOGIN")
			{
				QString userId = checkUser(str.left(str.indexOf(' ')), str.mid(str.indexOf(' ') + 1));
				if (userId != "ERROR")
					socket->userId = userId;
				SendToClient("LOGIN_ANSWER " + userId, socket->id);

				qDebug() << "online user with id: " + checkUser(str.left(str.indexOf(' ')), str.mid(str.indexOf(' ') + 1));

			}
			else if (codeWord == "REGISTRATION")
			{
				AddUserOnServer(str);
				SendToClient("REGISTRATION_ANSWER ", socket->id);
			}
			else if (codeWord == "LIST_OF_CHATS")
			{
				SendToClient("LIST_OF_CHATS_ANSWER " + findUserById(str)->getGroupChats(), socket->id);
				//qDebug() << "CHATS_OF_USER_ANSWER "  + findUserById(str)->getGroupChats();

			}
			else if (codeWord == "ADD_CHAT")
			{
				QString idOfNewGroupChat = AddChatOnServer(str);
				SendToClient("ADD_CHAT_ANSWER " + str.left(str.indexOf('#')) + "#" + idOfNewGroupChat, idOfUsersToIdOfSockets(str.mid(str.indexOf('#') + 1).split('#')));//возвращает на форму название и id чата

			}
			else if (codeWord == "LIST_OF_MESSAGES")
			{

				SendToClient("LIST_OF_MESSAGES_ANSWER " + findChatById(str)->getStringOfMessage(), socket->id);
				qDebug() << "LIST_OF_MESSAGES_ANSWER";
			}
			else if (codeWord == "ADD_CONTACT")
			{
				AddContactToUser(str);

			}
			else if (codeWord == "LIST_OF_CONTACTS")
			{
				SendToClient("LIST_OF_CONTACTS_ANSWER " + findUserById(str)->getContacts(), socket->id);
				qDebug() << "LIST_OF_CONTACTS_ANSWER " + findUserById(str)->getContacts();

			}
			else if (codeWord == "ADD_MESSAGE")
			{

				QString textOfMessage = str.left(str.indexOf('#'));
				str = str.mid(str.indexOf('#') + 1);
				QString idOfSender = str.left(str.indexOf('#'));
				str = str.mid(str.indexOf('#') + 1);
				QString idOfChat = str.left(str.indexOf('#'));
				Message* newMessage = new Message(textOfMessage, findUserById(idOfSender)->getNickName(), idOfSender);
				findChatById(idOfChat)->addMessageToChatList(newMessage);
				SendToClient("ADD_MESSAGE_ANSWER " + idOfChat + "#" + findUserById(idOfSender)->getNickName() + "\n" + textOfMessage + "#" + idOfSender + "#" + newMessage->getId(), idOfUsersToIdOfSockets(findChatById(idOfChat)->usersId));
				qDebug() << "ADD_MESSAGE_ANSWER";
			}
			else {
				qDebug() << "Coding Data Error";
			}

			break;
		}
	}
	else
	{
		qDebug() << "DataStream Error";

	}
	nextBlockSize = 0;
}


void Server::SendToClient(QString str)//отправка всем подключенным сокетам
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << quint16(0) << str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));
	//socket->write(Data);
	for (int i = 0; i < Sockets.size(); i++) {
		Sockets[i]->write(Data);
	}
}
void Server::SendToClient(QString str, QString id)//отослать сокету по заданному id. Для единичной отправки, ответов на запросы
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << quint16(0) << str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));

	findSocketById(id)->write(Data);
}
void Server::SendToClient(QString str, QStringList listOfId)//отправка группе сокетов из заданного списка id
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << quint16(0) << str;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));
	//socket->write(Data);
	for (int i = 0; i < listOfId.size(); i++) {

		findSocketById(listOfId[i])->write(Data);
	}
}

QString Server::checkUser(QString nick, QString pass) {//проверяет есть ли пользователь зарегистрированный на сервере
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getNickName() == nick && users[i]->getPassword() == pass)
		{
			return users[i]->id;
		}
	}
	return "Error";
}

QString Server::checkUser(QString tel)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i]->getTel() == tel)
		{
			return users[i]->id;

		}
	return "Error";
}



void Server::deleteSocket(QString id)//удаляет из списка Sockets сокет по id сокета
{
	for (int i = 0; i < Sockets.size(); i++)
	{
		if (Sockets[i]->id == id)
		{
			Sockets.removeAt(i);
			break;
		}
	}
}
//ХЕРНЮ НАПИСАЛ
Socket* Server::findSocketById(QString id)// возвращает индекс в списке сокетов сервера по id сокета
{
	for (int i = 0; i < Sockets.size(); i++)
	{
		if (Sockets[i]->id == id)
		{
			return  Sockets[i];//первое значение пары говорит о том что сокет подключен, второе значение пары сам сокет
		}
	}

}
User* Server::findUserById(QString id)//возвращает пользователя из списка пользователей с данным id
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->id == id)
			return users[i];
	}
}//
GroupChat* Server::findChatById(QString id)//возвращает чат из списка чатов с данным id
{
	for (int i = 0; i < chats.size(); i++)
	{
		if (chats[i]->getId() == id)
			return chats[i];
	}
}
QString Server::AddChatOnServer(QString str)//добавляет чат на сервер и возвращает id чата на сервере
{
	QString nameOfChat = str.left(str.indexOf('#'));
	QString newstr = str.mid(str.indexOf('#') + 1);
	QStringList listOfId = newstr.split('#');
	GroupChat* newGroupChat = new GroupChat(nameOfChat, listOfId);
	chats.push_back(newGroupChat);
	for (int i = 0; i < listOfId.size(); i++)
	{
		findUserById(listOfId[i])->createGroupChat(newGroupChat);

	}
	return newGroupChat->getId();
}

QStringList Server::idOfUsersToIdOfSockets(QStringList idOfUsers)
{
	QStringList result;
	for (int i = 0; i < idOfUsers.size(); i++)
	{
		for (int j = 0; j < Sockets.size(); j++)
		{
			if (Sockets[j]->userId == idOfUsers[i])
			{
				result.push_back(Sockets[j]->id);
			}
		}

	}
	return result;
}


void Server::AddUserOnServer(QString str)
{
	QString nick = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString pass = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString tel = str.left(str.indexOf('#'));
	QString idOfUser = checkUser(tel);
	if (idOfUser != "Error")
	{
		User* user = findUserById(idOfUser);
		if (user->getPassword().isEmpty())
		{
			user->changeNickName(nick);
			user->changePassword(pass);
		}

	}
	else
		users.push_back(new User(nick, pass, tel));
}

void Server::AddContactToUser(QString str)
{
	QString nick = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString tel = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString idOfUser = str.left(str.indexOf('#'));
	QString idOfContact = checkUser(tel);
	if (idOfContact == "Error")
	{
		User* newUser = new User(tel);
		users.push_back(newUser);
		findUserById(idOfUser)->addContact(newUser->id, nick);
	}
	else
		findUserById(idOfUser)->addContact(idOfContact, nick);

}