#include "User.h"

QStringList splitFIOintoComponents(QString& fio)
{
	QRegularExpression re("\\s+"); // Регулярное выражение для пробелов
	QStringList words = fio.split(re);
	words.removeAll(""); // Удаляем пустые строки
	refillingFullName(words);
	return words;
}

void refillingFullName(QStringList& words)
{
	int size = words.size();
	int lenghtFullName = 2;
	for (int i = size - 1; i < lenghtFullName; i++)
		words.push_back("");
}


void User::changeTelephone(QString newtel)
{
	telephoneNumber = newtel;
}

void User::changeNickName(QString newNickName)
{
	nickName = newNickName;
}
void User::changePassword(QString newpassword)
{
	password = newpassword;
}
void User::changeStatus(QString newStatus)
{
	status = newStatus;
}

void User::addContact(QString id, QString NickName)//передаем id пользователя
{
	ListContacts.push_back(new Contact(id,NickName));
}

void User::createGroupChat(QString name, QStringList listOfIdUsers)
{
	ListGroupChats.push_back(new GroupChat(name,listOfIdUsers));
}
void User::createGroupChat(GroupChat* chat)
{
	ListGroupChats.push_back(chat);
}

void User::chooseAndOpenContactChat()
{

}

void User::chooseAndOpenGroupChat()
{

}

void User::deleteContactChat()
{

}
void User::deleteGroupChat()
{

}

QString User::getNickName()
{
	return nickName;
}
QString User::getPassword()
{
	return password;
}
QString User::getTel()
{
	return telephoneNumber;
}
GroupChat* User::getLastGroupChat() {
	return ListGroupChats.back();
}

QList<QString> User::getListNameGroupChats() //выдает строку для передачи с сервера в которой чередуются имя чата и его id
{
	QList<QString> listNameGroupChat;
	for (auto& listChat : ListGroupChats)
		listNameGroupChat.push_back(listChat->getGroupName());
	return listNameGroupChat;
}

QList<QString> User::getListIdGroupChats() //выдает строку для передачи с сервера в которой чередуются имя чата и его id
{
	//QString result = "";
	//for (int i = 0; i < ListGroupChats.size(); i++)
	//{
	//	result += ListGroupChats[i]->getGroupName() + '#' + ListGroupChats[i]->getId() + '#';
	//}
	//result.chop(1);
	//return result;
	QList<QString> listIdGroupChat;
	for (auto& listChat : ListGroupChats)
		listIdGroupChat.push_back(listChat->getId());
	return listIdGroupChat;
}

QList<QString> User::getListNameContacts()
{
	QList<QString> listNameContacts;
	for (auto& listCont : ListContacts)
		listNameContacts.push_back(listCont->getName());
	return listNameContacts;
}

QList<QString> User::getListIdContacts()
{
	QList<QString> listIdContacts;
	for (auto& listCont : ListContacts)
		listIdContacts.push_back(listCont->getId());
	return listIdContacts;
}

