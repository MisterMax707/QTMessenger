#include "User.h"

int User::id_user = 0;

User::User(QString nick, QString pass, QString telephoneNumber) : nickName(nick), password(pass), telephoneNumber(telephoneNumber) 
{
	id_user++;
};
User::User(QString nick, QString telephoneNumber) : nickName(nick), telephoneNumber(telephoneNumber) 
{
	id_user++;
};

void User::changeTelephone(QString newtel)
{
	telephoneNumber = newtel;
}

void User::changeNickName(QString newNickName)
{
	nickName = newNickName;
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

int User::getIDUser()
{
	return id_user;
}

Contact* User::getLastContact()
{
	return ListContacts.back();
}

GroupChat* User::getLastGroupChat() 
{
	return ListGroupChats.back();
}


Contact* User::getAnIDContact(int id)
{
	for(auto& contact : ListContacts)
		if(contact->getIDContact() == id)
			return contact;
}

GroupChat* User::getAnIDGroupChat(int id)
{
	for (auto& group : ListGroupChats)
		if (group->getIDGroupChat() == id)
			return group;
}

ContactChat* User::getAnIDContactChat(int id)
{
	for (auto& chat : ListContactChats)
		if (chat->getIDContactChat() == id)
			return chat;
}


