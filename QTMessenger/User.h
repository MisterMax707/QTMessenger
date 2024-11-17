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
	User(QString nick, QString pass, QString telephoneNumber) : nickName(nick), password(pass), telephoneNumber(telephoneNumber) {}; // �������� ���������� ����, �������������� static
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
	GroupChat* getLastGroupChat();

private:
	int id_user;
	//FullName FIO;
	QString nickName;
	QString status;
	QString telephoneNumber;
	QString password;
	std::list<GroupChat*> ListGroupChats;
	std::list<ContactChat*> ListContactChats;
	std::list<Contact*> ListContacts;
};

