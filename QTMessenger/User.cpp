#include "User.h"

//void User::changeNameUser(FullName newFIO)
//{
//	FIO.name = newFIO.name;
//	FIO.surname = newFIO.surname;
//	FIO.patronymic = newFIO.patronymic;
//}
//
//void User::changeNickName(std::string newNickName)
//{
//	nickName = newNickName;
//}
//
//void User::changeStatus(std::string newStatus)
//{
//	status = newStatus;
//}

void User::createContact()
{

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
GroupChat* User::getLastGroupChat() {
	return ListGroupChats.back();
}
