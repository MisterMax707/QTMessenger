#pragma once
#include <Qlist>
#include "QString"
#include "QStringList"
#include "QRegularExpression"
#include "GroupChat.h"
#include "ContactChat.h"
#include "Contact.h"


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
	User(QString nick, QString pass, QString telephoneNumber) : nickName(nick), password(pass), telephoneNumber(telephoneNumber) 
	{
		id = QString::number(count++);
	}; // Добавить присовение айди, воспользоватья static
	User(QString nick, QString telephoneNumber) : nickName(nick), telephoneNumber(telephoneNumber) {};
	void changeTelephone(QString newtel);
	void changeNickName(QString newNickName);
	void changeStatus(QString newStatus);

	void addContact(QString id, QString NickName);
	void createGroupChat(QString name, QStringList listOfIdUsers);//возможно не понадобится так как чаты будут добавляться сначала на сервер а потом уже к пользователям по id пользователей
	void createGroupChat(GroupChat* chat);
	void chooseAndOpenContactChat();
	void chooseAndOpenGroupChat();
	void deleteContactChat();
	void deleteGroupChat();

	QString getNickName();
	QString getPassword();
	QString getGroupChats();
	QString getContacts();
	GroupChat* getLastGroupChat();
	QString id;
	
	static inline unsigned count{}; //статическая переменная для хранения последнего ID, созданного экземпляра


private:
	
	//FullName FIO;
	QString nickName;
	QString status;
	QString telephoneNumber;
	QString password;
	
	QList<GroupChat*> ListGroupChats;
	QList<ContactChat*> ListContactChats;
	QList<Contact*> ListContacts;
};

