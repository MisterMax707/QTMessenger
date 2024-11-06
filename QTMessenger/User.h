#pragma once
#include <list>
#include "ContactChat.h"
#include "GroupChat.h"
#include "Contact.h"
#include "QString"
#include "QStringList"
#include "QRegularExpression"
#include "QMessageBox"

// предварительный вызов, чтобы избежать цикличности 
// Pragma once + предварительный вызов + * = все хорошо
class ContactChat;
class GroupChat;
class Contact;

QStringList splitFIOintoComponents(QString& fio);
void refillingFullName(QStringList& words);

struct FullName
{
	FullName(QString name, QString surname, QString patronymic) :
		name(name), surname(surname), patronymic(patronymic) {}; // чтобы не было отчества надо передать пустоту "" или ничего не ставить

	QString name;
	QString surname;
	QString patronymic;
};

class User
{
public:
	User(FullName fio, QString nick, QString pass) : FIO(fio), nickName(nick), password(pass) {}; // Добавить присовение айди, воспользоватья static
	
	void changeNameUser(FullName newFIO);
	void changeNickName(QString newNickName);
	void changeStatus(QString newStatus);

	void createContact();
	void createGroupChat(QString name);

	void chooseAndOpenContactChat();
	void chooseAndOpenGroupChat();
	void deleteContactChat();
	void deleteGroupChat();
	GroupChat* getLastGroupChat();

private:
	int id_user;
	FullName FIO;
	QString nickName;
	QString status;
	QString telephoneNumber;
	QString password;
	std::list<GroupChat*> ListGroupChats;
	std::list<ContactChat*> ListContactChats;
	std::list<Contact*> ListContacts;
};

