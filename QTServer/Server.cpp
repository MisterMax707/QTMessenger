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

	actionKey[cod::CodeWord::LOGIN] = &Server::performAction_Login;
	actionKey[cod::CodeWord::REGISTRATION] = &Server::performAction_Registration;
	actionKey[cod::CodeWord::LIST_OF_CHATS] = &Server::performAction_ListOfChat;
	actionKey[cod::CodeWord::LIST_OF_MESSAGES] = &Server::performAction_ListOfMessages;
	actionKey[cod::CodeWord::LIST_OF_CONTACTS] = &Server::performAction_ListOfContacts;
	actionKey[cod::CodeWord::ADD_CHAT] = &Server::performAction_AddChat;
	actionKey[cod::CodeWord::ADD_CONTACT] = &Server::performAction_AddContact;
	actionKey[cod::CodeWord::ADD_MESSAGE] = &Server::performAction_AddMessage;
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
		startRead(in);
	}
	else
	{
		qDebug() << "DataStream Error";
	}
	nextBlockSize = 0;
}

void Server::startRead(QDataStream& in)
{
	while (true)
	{
		////////////// спросить у макса
		if (nextBlockSize == 0)
		{
			if (socket->bytesAvailable() < 2)
				break;
			in >> nextBlockSize;
		}
		if (socket->bytesAvailable() > nextBlockSize)
			break;
		//////////////////

		qDebug() << "read....";
		cod::CodeWord key;
		InformationWord word;
		InformationNumber number;
		in >> key >> word >> number;

		QVector<QString> arrWord;//= word.createArrayWord<QVector, QString>();
		QVector<QString> arrNumber;// = number.createArrayNumber<QVector, QString>();
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

void Server::performAction_Login(const QVector<QString>& word, const QVector<QString>& number)
{
	QString userId = getIdOfLoggedUser(word[0], word[2]); //заменить word[1] на word[2]
	if (userId != "nan_error")
		socket->userId = userId;
	InformationNumber thisId = userId;
	InformationNumber yourIdSocket = socket->id;
	SendToClient(cod::CodeWord::LOGIN_ANSWER, std::nullopt, thisId, yourIdSocket);
	//SendToClient("LOGIN_ANSWER " + userId, socket->id);

	//qDebug() << "online user with id: " + checkUser(str.left(str.indexOf(' ')), str.mid(str.indexOf(' ') + 1));
}

QString Server::getIdOfLoggedUser(QString nick, QString tel) //проверяет есть ли пользователь зарегистрированный на сервере
{
	for (auto& us : users)
	{
		if (us->getNickName() == nick && us->getTel() == tel)
		{
			return us->id;
		}
	}
	return "nan_error";
}

void Server::performAction_Registration(const QVector<QString>& word, const QVector<QString>& number)
{
	AddUserOnServer(word);
	InformationNumber yourIdSocket = socket->id;
	SendToClient(cod::CodeWord::REGISTRATION_ANSWER, std::nullopt, std::nullopt, yourIdSocket);
	//SendToClient("REGISTRATION_ANSWER ", socket->id);
}

void Server::AddUserOnServer(const QVector<QString>& dateUser)
{
	QString nick = dateUser[0];
	QString pass = dateUser[1];
	QString tel = dateUser[2];
	QString idOfUser = getIdOfLoggedUser(nick, tel);
	if (idOfUser != "nan_error")
	{
		//User* user = findUserById(idOfUser);
		//if (user->getPassword().isEmpty())
		//{
		//	user->changeNickName(nick);
		//	user->changePassword(pass);
		//}
		// хз че это :D
		// если они совпали, надо сделать оповещение, что в данных, есть такой чел. но не заменять его ахахаххаххах
	}
	else
		users.push_back(new User(nick, pass, tel));
}

//QString Server::checkUser(QString tel)
//{
//	for (int i = 0; i < users.size(); i++)
//		if (users[i]->getTel() == tel)
//		{
//			return users[i]->id;
//
//		}
//	return "Error";
//}

void Server::performAction_ListOfChat(const QVector<QString>& word, const QVector<QString>& number)
{
	QString idUser = number.last();
	InformationWord nameOfChatByUser = findUserById(idUser)->getListNameGroupChats();
	InformationNumber idOfChatByUser = findUserById(idUser)->getListIdGroupChats();
	InformationNumber yourIdSocket = socket->id;
	SendToClient(cod::CodeWord::LIST_OF_CHATS_ANSWER, nameOfChatByUser, idOfChatByUser, yourIdSocket);
	//SendToClient("LIST_OF_CHATS_ANSWER " + findUserById(str)->getGroupChats(), socket->id);
	//qDebug() << "CHATS_OF_USER_ANSWER "  + findUserById(str)->getGroupChats();
}

void Server::performAction_ListOfMessages(const QVector<QString>& word, const QVector<QString>& number)
{
	//SendToClient("LIST_OF_MESSAGES_ANSWER " + findChatById(str)->getStringOfMessage(), socket->id);
	//qDebug() << "LIST_OF_MESSAGES_ANSWER";
}

void Server::performAction_ListOfContacts(const QVector<QString>& word, const QVector<QString>& number)
{
	QString idUser = number.last();
	InformationWord nameOfContactByUser = findUserById(idUser)->getListNameContacts();
	InformationNumber idOfContactByUser = findUserById(idUser)->getListIdContacts();
	InformationNumber yourIdSocket = socket->id;
	SendToClient(cod::CodeWord::LIST_OF_CONTACTS_ANSWER, nameOfContactByUser, idOfContactByUser, yourIdSocket);
	//SendToClient("LIST_OF_CONTACTS_ANSWER " + findUserById(str)->getContacts(), socket->id);
	//qDebug() << "LIST_OF_CONTACTS_ANSWER " + findUserById(str)->getContacts();
}

void Server::performAction_AddChat(const QVector<QString>& word, const QVector<QString>& number)
{
	AddChatOnServer(word, number);
	addChatForSelectedUsers(number);
	QString idOfNewGroupChat = getIdOfNewGroupChat();
	InformationWord nameChat = word.last();
	InformationNumber idChat = idOfNewGroupChat;
	InformationNumber groupIdSocket = idOfUsersToIdOfSockets(number);
	SendToClient(cod::CodeWord::ADD_CHAT_ANSWER, nameChat, idChat, groupIdSocket);
	//SendToClient("ADD_CHAT_ANSWER " + str.left(str.indexOf('#')) + "#" + idOfNewGroupChat, idOfUsersToIdOfSockets(str.mid(str.indexOf('#') + 1).split('#')));//возвращает на форму название и id чата
}

void Server::AddChatOnServer(const QVector<QString>& nameChat, const QVector<QString>& selectionIdForAddingChat)//добавляет чат на сервер и возвращает id чата на сервере
{
	GroupChat* newGroupChat = new GroupChat(nameChat[0], selectionIdForAddingChat);
	chats.push_back(newGroupChat);
}

void Server::addChatForSelectedUsers(const QVector<QString>& selectionIdForAddingChat)
{
	for (auto& selectId : selectionIdForAddingChat)
	{
		findUserById(selectId)->createGroupChat(chats.last());
	}
}

QString Server::getIdOfNewGroupChat()
{
	return chats.last()->getId();
}

void Server::performAction_AddContact(const QVector<QString>& word, const QVector<QString>& number)
{
	//AddContactToUser(str);
}

void Server::performAction_AddMessage(const QVector<QString>& word, const QVector<QString>& number)
{
	//QString textOfMessage = str.left(str.indexOf('#'));
	//str = str.mid(str.indexOf('#') + 1);
	//QString idOfSender = str.left(str.indexOf('#'));
	//str = str.mid(str.indexOf('#') + 1);
	//QString idOfChat = str.left(str.indexOf('#'));
	//Message* newMessage = new Message(textOfMessage, findUserById(idOfSender)->getNickName(), idOfSender);
	//findChatById(idOfChat)->addMessageToChatList(newMessage);
	//SendToClient("ADD_MESSAGE_ANSWER " + idOfChat + "#" + findUserById(idOfSender)->getNickName() + "\n" + textOfMessage + "#" + idOfSender + "#" + newMessage->getId(), idOfUsersToIdOfSockets(findChatById(idOfChat)->usersId));
	//qDebug() << "ADD_MESSAGE_ANSWER";
}


void Server::SendToClient(const cod::CodeWord& cod, OptInfoWord word = std::nullopt, 
	OptInfoNum number = std::nullopt, OptInfoNum idSocket = std::nullopt)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << quint16(0) << cod << word << number;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));

	QList<QString> listIdSocket = idSocket->createArrayNumber<QList, QString>();
	for (auto& lis : listIdSocket)
		findSocketById(lis)->write(Data);
}

//void Server::SendToClient(QString str)//отправка всем подключенным сокетам
//{
//	Data.clear();
//	QDataStream out(&Data, QIODevice::WriteOnly);
//	out.setVersion(QDataStream::Qt_6_2);
//	out << quint16(0) << str;
//	out.device()->seek(0);
//	out << quint16(Data.size() - sizeof(quint16));
//	//socket->write(Data);
//	for (int i = 0; i < Sockets.size(); i++) {
//		Sockets[i]->write(Data);
//	}
//}

//void Server::SendToClient(QString str, QString id)//отослать сокету по заданному id. Для единичной отправки, ответов на запросы
//{
//	Data.clear();
//	QDataStream out(&Data, QIODevice::WriteOnly);
//	out.setVersion(QDataStream::Qt_6_2);
//	out << quint16(0) << str;
//	out.device()->seek(0);
//	out << quint16(Data.size() - sizeof(quint16));
//
//	findSocketById(id)->write(Data);
//}

//void Server::SendToClient(QString str, QStringList listOfId)//отправка группе сокетов из заданного списка id
//{
//	Data.clear();
//	QDataStream out(&Data, QIODevice::WriteOnly);
//	out.setVersion(QDataStream::Qt_6_2);
//	out << quint16(0) << str;
//	out.device()->seek(0);
//	out << quint16(Data.size() - sizeof(quint16));
//	//socket->write(Data);
//	for (int i = 0; i < listOfId.size(); i++) {
//
//		findSocketById(listOfId[i])->write(Data);
//	}
//}


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

Socket* Server::findSocketById(QString id)// возвращает индекс в списке сокетов сервера по id сокета
{
	for (auto& soc : Sockets)
	{
		if (soc->id == id)
			return soc;//первое значение пары говорит о том что сокет подключен, второе значение пары сам сокет
	}

}
User* Server::findUserById(QString id)//возвращает пользователя из списка пользователей с данным id
{
	for (auto& us : users)
	{
		if (us->id == id)
			return us;
	}
}

GroupChat* Server::findChatById(QString id)//возвращает чат из списка чатов с данным id
{
	for (auto& ch : chats)
	{
		if (ch->getId() == id)
			return ch;
	}
}

QStringList Server::idOfUsersToIdOfSockets(QStringList idOfUsers)
{
	QStringList result;
	for (auto& idUs : idOfUsers)
	{
		for (auto& soc : Sockets)
		{
			if (soc->userId == idUs)
			{
				result.push_back(soc->id);
			}
		}
	}
	return result;
}

void Server::AddContactToUser(QString str)
{
	//QString nick = str.left(str.indexOf('#'));
	//str = str.mid(str.indexOf('#') + 1);
	//QString tel = str.left(str.indexOf('#'));
	//str = str.mid(str.indexOf('#') + 1);
	//QString idOfUser = str.left(str.indexOf('#'));
	//QString idOfContact = checkUser(tel);
	//if (idOfContact == "Error")
	//{
	//	User* newUser = new User(tel);
	//	users.push_back(newUser);
	//	findUserById(idOfUser)->addContact(newUser->id, nick);
	//}
	//else
	//	findUserById(idOfUser)->addContact(idOfContact, nick);

}


