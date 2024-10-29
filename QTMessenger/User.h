#pragma once
#include <string>
#include <list>
#include "GroupChat.h"
#include "Contact.h"
#include "ContactChat.h"
#include "qstring.h"
// ��������������� �����, ����� �������� ����������� 
// Pragma once + ��������������� ����� + * = ��� ������
class ContactChat;
class GroupChat;
class Contact;

//struct FullName
//{
//	FullName(QString name, QString surname, QString patronymic) :
//		name(name), surname(surname), patronymic(patronymic) {}; // ����� �� ���� �������� ���� �������� ������� "" ��� ������ �� �������
//
//	QString name;
//	QString surname;
//	QString patronymic;
//};

class User
{
public:
	User(QString nick, QString Password) {
		nickName = nick;
		password = Password;
	} ;
	//User(FullName fio, std::string nick) : FIO(fio), nickName(nick) {}; // �������� ���������� ����, �������������� static
	//User(std::string nick, std::string password) : nickName(nick), password(password) {};
	//void changeNameUser(FullName newFIO);
	void changeNickName(std::string newNickName);
	void changeStatus(std::string newStatus);

	void createContact();
	void createGroupChat();

	void chooseAndOpenContactChat();
	void chooseAndOpenGroupChat();
	void deleteContactChat();
	void deleteGroupChat();

private:
	int id_user;
	//FullName FIO;
	QString nickName;
	//std::string status;
	//std::string telephoneNumber;
	QString password;
	std::list<GroupChat*> ListGroupChats;
	std::list<ContactChat*> ListContactChats;
	std::list<Contact*> ListContacts;
};

