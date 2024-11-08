#pragma once
#include <list>
#include "QString"
#include "QStringList"
#include "QRegularExpression"
#include "QMessageBox"
#include "GroupChat.h"
#include "ContactChat.h"
#include "Contact.h"

// ��������������� �����, ����� �������� ����������� 
// Pragma once + ��������������� ����� + * = ��� ������
class ContactChat;
class GroupChat;
class Contact;

QStringList splitFIOintoComponents(QString& fio);
void refillingFullName(QStringList& words);

struct FullName
{
	FullName(QString name, QString surname, QString patronymic) :
		name(name), surname(surname), patronymic(patronymic) {}; // ����� �� ���� �������� ���� �������� ������� "" ��� ������ �� �������

	QString name;
	QString surname;
	QString patronymic;
};

class User
{
public:
	User(FullName fio, QString nick, QString pass, QString telephoneNumber="") : FIO(fio), nickName(nick), password(pass) {}; // �������� ���������� ����, �������������� static
	User(FullName fio, QString nick, int telephoneNumber) :FIO(fio), nickName(nick), telephoneNumber(telephoneNumber) {};
	void changeNameUser(FullName newFIO);
	void changeNickName(QString newNickName);
	void changeStatus(QString newStatus);

	void addContact();
	void createGroupChat(QString name);

	void chooseAndOpenContactChat();
	void chooseAndOpenGroupChat();
	void deleteContactChat();
	void deleteGroupChat();

	QString getNickName();
	GroupChat* getLastGroupChat();

private:
	int id_user;
	FullName FIO;
	QString nickName;
	QString status;
	/*QString*/ int telephoneNumber;
	QString password;
	std::list<GroupChat*> ListGroupChats;
	std::list<ContactChat*> ListContactChats;
	std::list<Contact*> ListContacts;
};

