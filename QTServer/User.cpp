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

void User::addContact(QString id, QString NickName)//передаем id пользовател€
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

//QString User::getGroupChats() //выдает строку дл€ передачи с сервера в которой чередуютс€ им€ чата и его id
//{
//	QString result = "";
//	for (int i = 0; i < ListGroupChats.size(); i++)
//	{
//		result += ListGroupChats[i]->getGroupName() + '#' + ListGroupChats[i]->getId() + '#';
//	}
//	result.chop(1);
//	return result;
//}
QStringList User::getOnlyIdChats()
{
	QString result = "";
	for (int i = 0; i < ListGroupChats.size(); i++)
	{
		result +=  ListGroupChats[i]->getId() + '#';
	}
	result.chop(1);
	QStringList myresult = result.split('#');
	return myresult;
	
}
QString User::getContacts()
{
	QString result = "";
	for (int i = 0; i < ListContacts.size(); i++)
	{
		result += ListContacts[i]->getName() + '#' + ListContacts[i]->getId() + '#';
	}
	result.chop(1);
	return result;
}
QStringList User::getOnlyIdContacts()
{
	QString result = "";
	for (int i = 0; i < ListContacts.size(); i++)
	{
		result += ListContacts[i]->getId() + '#';
	}
	result.chop(1);
	QStringList myresult=result.split('#');
	return myresult;
}