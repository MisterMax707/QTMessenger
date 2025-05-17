#include "Server.h"



Server::Server() {
	if (this->listen(QHostAddress::Any, 2323))
	{
		qDebug() << "server is running...";
	}
	else
	{
		qDebug() << "Error!!! Server is not running...";

	}
	nextBlockSize = 0;

	//автоматически добавляются два пользователя для отладки потом удалить
	users.push_back(new User("Max", "1", "89106337707"));//
	users.push_back(new User("Dan", "1", "i dont know Dans telephone"));
	users.push_back(new User("Darina", "1", "; sldfkg; sdlfg"));



	users[0]->addContact("1", "Dan");
	users[0]->addContact("2", "Darina");
	users[1]->addContact("0", "Max");


	QStringList drivers = QSqlDatabase::drivers();


	// Выводим список драйверов
	qDebug() << "Available drivers:";
	for (const QString& driver : drivers) {
		qDebug() << driver;
	}


	db = QSqlDatabase::addDatabase("QPSQL");
	db.setHostName("localhost");
	db.setPort(5432);
	db.setDatabaseName("postgres");
	db.setUserName("postgres");
	db.setPassword("maxim1106");

	if (!db.open()) {
		qDebug() << "Failed to connect to database:" << db.lastError().text();

	}
	else
		qDebug() << "database connected successfully...";

	QSqlQuery query("SELECT * FROM users");
	while (query.next()) {
		int id = query.value("id_user").toInt();
		QString username = query.value("nick_user").toString();
		QString password = query.value("password_user").toString();
		QString telephone_number = query.value("telephone_user").toString();
		QString id_socket = query.value("id_socket_user").toString();
		qDebug() << "ID:" << id
			<< "Username:" << username
			<< "Password:" << password
			<< "telephone:" << telephone_number
			<< "idSocket" << id_socket;
	}




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
				QString nick = str.left(str.indexOf(' '));
				QString pass = str.mid(str.indexOf(' ') + 1);
				QString userId = checkUser(nick, pass);
				if (userId != "ERROR") {
					recordUserIsOnline(userId, socket->id);
					//socket->userId = userId;
					qDebug() << "online user with id: " + userId;

				}
				else {
					qDebug() << "Error!!! User with such nick and pass not exist...";

				}
				SendToClient("LOGIN_ANSWER " + userId, socket->id);//посылаем либо сообщение об ошибке: "ERROR" либо id_user

			}
			else if (codeWord == "REGISTRATION")
			{
				AddUserOnServer(str);//во входной строке содержатся nick pass tel которые идут через символ #
				SendToClient("REGISTRATION_ANSWER ", socket->id);
			}
			else if (codeWord == "LIST_OF_CHATS")
			{
				SendToClient("LIST_OF_CHATS_ANSWER " + getListOfChatsByIdUser(str), socket->id);//посылает имя чата и его id через # // str на вход это idUser
				qDebug() << "CHATS_OF_USER_ANSWER " + getListOfChatsByIdUser(str);

			}
			else if (codeWord == "ADD_CHAT")
			{
				QString nameOfChat = str.left(str.indexOf('#'));
				QString idOfNewGroupChat = AddChatOnServer(str);
				SendToClient("ADD_CHAT_ANSWER " + nameOfChat + "#" + idOfNewGroupChat, idOfUsersToIdOfSockets(str.mid(str.indexOf('#') + 1).split('#')));//возвращает на форму название и id чата

			}
			else if (codeWord == "LIST_OF_MESSAGES")
			{

				SendToClient("LIST_OF_MESSAGES_ANSWER " + getListOfMessagesByIdChat(str), socket->id);
				qDebug() << "LIST_OF_MESSAGES_ANSWER";
			}
			else if (codeWord == "ADD_CONTACT")
			{
				if(AddContactToUser(str)=="error")
					SendToClient("ADD_CONTACT_ANSWER ERROR",socket->id);
				else
					SendToClient("ADD_CONTACT_ANSWER OK", socket->id);
				

			}
			else if (codeWord == "LIST_OF_CONTACTS")
			{
				SendToClient("LIST_OF_CONTACTS_ANSWER " + getContactsByIdUser(str), socket->id);
				/*SendToClient("LIST_OF_CONTACTS_ANSWER " + findUserById(str)->getContacts(), socket->id);
				qDebug() << "LIST_OF_CONTACTS_ANSWER " + findUserById(str)->getContacts();*/
				
			}
			else if (codeWord == "ADD_MESSAGE")
			{
				QString newstr = str;  
				newstr = newstr.mid(newstr.indexOf('#') + 1);
				newstr = newstr.mid(newstr.indexOf('#') + 1);
				QString idOfChat = newstr.left(newstr.indexOf('#'));
				SendToClient("ADD_MESSAGE_ANSWER " +addMessageOnServer(str), idOfUsersToIdOfSockets(getListOfParticipatorsByIdChat(idOfChat)));
				qDebug() << "ADD_MESSAGE_ANSWER";
			}
			else if (codeWord == "DELETE_CHAT")
			{

				/*QStringList listofid = findUserById(str)->getOnlyIdChats();
				for (int i = 0; i < listofid.size(); i++)
				{
					QString text = str;
					QString text2 = "was deleted user with id:";
					Message* newMessage = new Message(text, text2, str);
					findChatById(listofid[i])->addMessageToChatList(newMessage);
					SendToClient("ADD_MESSAGE_ANSWER " + listofid[i] + "#" + text2 + "\n" + str + "#" + str + "#" + newMessage->getId(), idOfUsersToIdOfSockets(findChatById(listofid[i])->usersId));

				}
				deleteUser(str);*/
				//SendToClient("DELETE_USER_ANSWER " +findUserById(str)->getNickName(), idOfUsersToIdOfSockets(findUserById(str)->getOnlyIdContacts()));//уже было закомментировано
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
	QSqlQuery query;
	query.prepare("SELECT\
					CASE \
						WHEN EXISTS(SELECT * FROM USERS WHERE password_user = :pass AND nick_user = :nick)\
							THEN cast((SELECT id_user from users WHERE password_user = :pass AND nick_user = :nick) as text)\
						ELSE 'ERROR'\
					END");
	query.bindValue(":nick", nick);
	query.bindValue(":pass", pass);
	//добавлять по id пользователю номер сокета
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();

	}
	if (query.next()) {
		return query.value(0).toString();
	}
	else {

		qDebug() << "Error!!! Can't check user in dataBase correctly...";
		return "ERROR";
	}

	/*for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getNickName() == nick && users[i]->getPassword() == pass)
		{
			return users[i]->id;
		}
	}*/

}

bool Server::checkUser(QString tel)
{
	QSqlQuery query;
	query.prepare("SELECT EXISTS(SELECT * FROM users WHERE telephone_user = :phone)");
	query.bindValue(":phone", tel);

	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();
		return false;
	}

	if (query.next()) {
		return query.value(0).toBool();
	}

	return false;
}

QString Server::checkContact(QString tel)
{
	QSqlQuery query;
	query.prepare("SELECT\
					CASE \
						WHEN EXISTS(SELECT * FROM USERS WHERE telephone_user = :tel)\
							THEN cast((SELECT id_user from users WHERE telephone_user = :tel) as text)\
						ELSE 'ERROR'\
					END");
	query.bindValue(":tel", tel);
	//добавлять по id пользователю номер сокета
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();

	}
	if (query.next()) {
		return query.value(0).toString();
	}
	else {

		qDebug() << "Error!!! Can't check user in dataBase correctly...";
		return "ERROR";
	}
}



void Server::deleteSocket(QString idSocket)//удаляет из списка Sockets сокет по id сокета при отключении сокета от сервера
{

	QSqlQuery query;
	query.prepare("UPDATE USERS\
					SET id_socket_user=NULL \
					WHERE id_socket_user=:idSocket");
	query.bindValue(":idSocket", idSocket);
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();

	}

}
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
//User* Server::findUserById(QString id)//возвращает пользователя из списка пользователей с данным id
//{
//	for (int i = 0; i < users.size(); i++)
//	{
//		if (users[i]->id == id)
//			return users[i];
//	}
//}//
//GroupChat* Server::findChatById(QString id)//возвращает чат из списка чатов с данным id
//{
//	for (int i = 0; i < chats.size(); i++)
//	{
//		if (chats[i]->getId() == id)
//			return chats[i];
//	}
//}
QString Server::AddChatOnServer(QString str)//добавляет чат на сервер и возвращает id чата на сервере
{
	QString nameOfChat = str.left(str.indexOf('#'));//имя чата
	QString newstr = str.mid(str.indexOf('#') + 1);
	QStringList listOfId = newstr.split('#');//список участников
	QString idChat;
	//GroupChat* newGroupChat = new GroupChat(nameOfChat, listOfId);
	QSqlQuery query(db);
	db.transaction();

	query.prepare("INSERT INTO chat (name_chat) VALUES (:nameOfChat) RETURNING id_chat;");
	query.bindValue(":nameOfChat", nameOfChat);
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();
		db.rollback();
	}
	if (query.next())
	{
		idChat = query.value(0).toString();

	}
	query.prepare("INSERT INTO user_chat_link (id_chat,id_user) VALUES(:id_chat,:id_user)");
	query.bindValue(":id_chat", idChat.toInt());

	foreach(const QString idUser, listOfId) {
		query.bindValue(":id_user", idUser);
		if (!query.exec()) {
			qDebug() << "Ошибка вставки:" << query.lastError().text();
			db.rollback();

		}
	}

	if (!db.commit()) {
		qWarning() << "Commit failed:" << db.lastError();
	}
	/*chats.push_back(newGroupChat);
	for (int i = 0; i < listOfId.size(); i++)
	{
		findUserById(listOfId[i])->createGroupChat(newGroupChat);

	}
	return newGroupChat->getId();*/
	return idChat;
}


QStringList Server::idOfUsersToIdOfSockets(QStringList idOfUsers)/*на ввод id пользователей на выход id сокетов подключенных
к серверу пользователей которым в данный момент нужно разослать информацию*/
{
	QString idString = idOfUsers.join(',');
	QString queryString = QString("SELECT id_socket_user FROM users WHERE id_user IN(%1) and id_socket_user is not null").arg(idString);
	QStringList result;
	QSqlQuery query;
	query.prepare(queryString);

	if (!query.exec()) {
		qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();

	}


	while (query.next()) {
		result.push_back(query.value("id_socket_user").toString());

	}
	/*for (int i = 0; i < idOfUsers.size(); i++)
	{
		for (int j = 0; j < Sockets.size(); j++)
		{
			if (Sockets[j]->userId == idOfUsers[i])
			{
				result.push_back(Sockets[j]->id);
			}
		}

	}*/
	return result;
}


void Server::AddUserOnServer(QString str)//во входной строке содержатся nick pass tel которые идут через символ #
{
	QString nick = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString pass = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString tel = str.left(str.indexOf('#'));
	if (checkUser(tel))
	{
		QSqlQuery query;
		query.prepare("UPDATE users SET nick_user=:nick, password_user=:pass \
						WHERE telephone_user=:tel AND password_user IS NULL");
		query.bindValue(":nick", nick);
		query.bindValue(":pass", pass);
		query.bindValue(":tel", tel);

		if (!query.exec()) {
			qDebug() << "Query error:" << query.lastError().text();

		}
		/*User* user = findUserById(idOfUser);
		if (user->getPassword().isEmpty())
		{
			user->changeNickName(nick);
			user->changePassword(pass);
		}*/


	}
	else
		createNewUserOnServer(tel, nick, pass);
}

QString Server::AddContactToUser(QString str)
{
	QString nick = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString tel = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString idOfUser = str.left(str.indexOf('#'));
	QString idOfContact = checkContact(tel);
	if (idOfContact=="ERROR") {
		
		return "error";
	}
	else {
		QSqlQuery query;
		query.prepare("INSERT INTO user_contacts (user_id,contact_id,contact_name) VALUES (:user_id,:contact_id,:nick)");
		query.bindValue(":nick", nick);
		query.bindValue(":user_id", idOfUser);
		query.bindValue(":contact_id", idOfContact);
		if (!query.exec()) {
			qDebug() << "Query error:" << query.lastError().text();

		}
		return "ok";
	}
	/*if (idOfContact == "Error")
	{
		User* newUser = new User(tel);
		users.push_back(newUser);
		findUserById(idOfUser)->addContact(newUser->id, nick);
	}
	else
		findUserById(idOfUser)->addContact(idOfContact, nick);*/

}

void Server::deleteUser(QString id)
{

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->id == id)
		{
			users.erase(users.begin() + i);

		}

	}
}


void Server::createNewUserOnServer(QString tel, QString nick, QString pass) {
	QSqlQuery query;
	query.prepare("INSERT INTO users (nick_user, telephone_user, password_user) \
				   VALUES (:nick,:tel ,:pass )");
	query.bindValue(":tel", tel);
	query.bindValue(":pass", pass);
	query.bindValue(":nick", nick);

	if (!query.exec())
		qDebug() << "Insert error:" << query.lastError().text();

}


void Server::recordUserIsOnline(QString userId, QString socketId)
{
	QSqlQuery query;
	query.prepare("UPDATE users\
					SET id_socket_user=:socket \
					WHERE id_user=:userId");
	query.bindValue(":userId", userId.toInt());
	query.bindValue(":socket", socketId.toInt());
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();

	}
}

QString Server::getListOfChatsByIdUser(QString userId)
{
	QString result = "";
	QSqlQuery query;
	query.prepare("SELECT  name_chat,id_chat \
				   FROM chat \
				   WHERE id_chat IN (SELECT id_chat FROM user_chat_link WHERE id_user=:idUser) ");
	query.bindValue(":idUser", userId);
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();

	}
	while (query.next()) {
		result += query.value("name_chat").toString() + '#' + query.value("id_chat").toString() + '#';
	}
	result.chop(1);
	return result;

}

QString Server::getListOfMessagesByIdChat(QString chatId)
{
	QString result = "";
	QSqlQuery query;
	query.prepare("SELECT chat_message_link.id_message, message.content_message, users.id_user, users.nick_user\
		FROM message\
		INNER JOIN chat_message_link ON chat_message_link.id_message = message.id_message\
		INNER JOIN users ON users.id_user = message.id_user\
		where id_chat=:id_chat");
	query.bindValue(":id_chat", chatId);
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();

	}
	while (query.next()) {
		result += query.value("nick_user").toString() +  "\n" + query.value("content_message").toString() + '#' + query.value("id_user").toString() + '#' + query.value("id_message").toString() + '#';
	}
	result.chop(1);
	return result;
}

QString Server::addMessageOnServer(QString str) {
	QString textOfMessage = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString idOfSender = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QString idOfChat = str.left(str.indexOf('#'));
	QString idMessage,nickSender;
	QSqlQuery query(db);
	db.transaction();
	query.prepare("INSERT INTO message (content_message,id_user) VALUES(:content_mes,:id_user) RETURNING id_message;");
	query.bindValue(":content_mes", textOfMessage);
	query.bindValue(":id_user", idOfSender.toInt());
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();
		db.rollback();
	}

	if (query.next())
	{

		idMessage = query.value("id_message").toString();

	}
	query.prepare("INSERT INTO chat_message_link (id_message, id_chat) VALUES (:id_messages,:id_chat);\
					");
	
	query.bindValue(":id_chat", idOfChat.toInt());
	query.bindValue(":id_messages", idMessage.toInt());
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();
		db.rollback();
	}
	query.prepare("SELECT nick_user FROM users WHERE id_user=:id_user");
	query.bindValue(":id_user", idOfSender.toInt());
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();
		db.rollback();
	}
	if (query.next()) {
		nickSender = query.value("nick_user").toString();

	}
	if (!db.commit()) {
		qWarning() << "Commit failed:" << db.lastError();
	}

	return idOfChat + "#" + nickSender + '\n' + textOfMessage + '#' + idOfSender + '#' + idMessage;
}


QStringList Server::getListOfParticipatorsByIdChat(QString chatId) {
	QSqlQuery query;
	QString result;
	query.prepare("SELECT id_user from user_chat_link WHERE id_chat=:id_chat");
	query.bindValue(":id_chat", chatId);
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();
		
	}
	while (query.next())
	{
		result += query.value("id_user").toString() + ' ';
	}
	result.chop(1);
	return result.split(' ');
}


QString Server::getContactsByIdUser(QString idUser)
{
	QSqlQuery query;
	QString result;
	query.prepare("SELECT contact_name,contact_id from user_contacts WHERE user_id=:idUser");
	query.bindValue(":idUser", idUser);
	if (!query.exec()) {
		qDebug() << "Query error:" << query.lastError().text();

	}
	while (query.next())
	{
		result += query.value("contact_name").toString() + '#'+ query.value("contact_id").toString()+'#';
	}
	result.chop(1);
	return result;
}