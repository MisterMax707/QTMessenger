#include "User.h"

QStringList splitFIOintoComponents(QString& fio)
{
	QRegularExpression re("\\s+"); // –егул€рное выражение дл€ пробелов
	QStringList words = fio.split(re);
	words.removeAll(""); // ”дал€ем пустые строки
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


void User::changeNameUser(FullName newFIO)
{
	FIO.name = newFIO.name;
	FIO.surname = newFIO.surname;
	FIO.patronymic = newFIO.patronymic;
}

void User::changeNickName(QString newNickName)
{
	nickName = newNickName;
}

void User::changeStatus(QString newStatus)
{
	status = newStatus;
}

void User::addContact()
{
	ListContacts.push_back(new Contact());
}

void User::createGroupChat(QString name)
{
	ListGroupChats.push_back(new GroupChat(name));
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

GroupChat* User::getLastGroupChat() {
	return ListGroupChats.back();
}
