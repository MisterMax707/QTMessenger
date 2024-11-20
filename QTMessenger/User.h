#pragma once
#include <list>
#include "QString"
#include "QStringList"
#include "QRegularExpression"
#include "QMessageBox"
#include "GroupChat.h"
#include "ContactChat.h"
#include "Contact.h"

// предварительный вызов, чтобы избежать цикличности 
// Pragma once + предварительный вызов + * = все хорошо
class ContactChat;
class GroupChat;
class Contact;

class User
{
public:
	User(QString nick, QString pass, QString telephoneNumber) : nickName(nick), password(pass), telephoneNumber(telephoneNumber) {}; // ƒобавить присовение айди, воспользовать€ static
	User( QString nick, QString telephoneNumber) : nickName(nick), telephoneNumber(telephoneNumber) {};
	void changeTelephone(QString newtel);
	void changeNickName(QString newNickName);
	void changeStatus(QString newStatus);

	void addContact(User* user);
	void createGroupChat(QString name);

	void chooseAndOpenContactChat();
	void chooseAndOpenGroupChat();
	void deleteContactChat();
	void deleteGroupChat();

	QString getNickName();
	Contact* getLastContact();
	GroupChat* getLastGroupChat();

private:
	int id_user;
	QString nickName;
	QString status;
	QString telephoneNumber;
	QString password;
	std::list<GroupChat*> ListGroupChats;
	std::list<ContactChat*> ListContactChats;
	std::list<Contact*> ListContacts;
};

