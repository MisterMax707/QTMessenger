#include "User.h"

void User::changeTelephone(QString newtel)
{
	telephoneNumber = newtel;
}

void User::changeNickName(QString newNickName)
{
	nickName = newNickName;
}

void User::changeStatus(QString newStatus)
{
	status = newStatus;
}

void User::addContact(User* user)
{
	ListContacts.push_back(new Contact(user));
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

Contact* User::getLastContact()
{
	return ListContacts.back();
}

GroupChat* User::getLastGroupChat() 
{
	return ListGroupChats.back();
}
