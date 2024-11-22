#pragma once
#include <QList>
#include "QString.h"
#include "QStringList.h"
#include "QRegularExpression.h"
#include "QMessageBox.h"
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
	User(QString nick, QString pass, QString telephoneNumber); // ƒобавить присовение айди, воспользовать€ static
	User(QString nick, QString telephoneNumber);

	void changeTelephone(QString newtel);
	void changeNickName(QString newNickName);

	void addContact(User* user);
	void createGroupChat(QString name);

	void chooseAndOpenContactChat();
	void chooseAndOpenGroupChat();
	void deleteContactChat();
	void deleteGroupChat();

	QString getNickName();
	int getIDUser();
	Contact* getLastContact();
	GroupChat* getLastGroupChat();

	Contact* getAnIDContact(int id);
	GroupChat* getAnIDGroupChat(int id);
	ContactChat* getAnIDContactChat(int id);

private:
	static int id_user;
	bool status;
	QString nickName;
	QString telephoneNumber;
	QString password;
	QList<GroupChat*> ListGroupChats;
	QList<ContactChat*> ListContactChats;
	QList<Contact*> ListContacts;
};

