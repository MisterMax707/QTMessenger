#pragma once
#include <string>
#include <list>
#include"GroupChat.h"
#include"Contact.h"
#include"ContactChat.h"
struct FullName
{
	FullName(std::string name, std::string surname, std::string patronymic) :
		name(name), surname(surname), patronymic(patronymic) {}; // чтобы не было отчества надо передать пустоту "" или ничего не ставить

	std::string name;
	std::string surname;
	std::string patronymic;
};

class User
{
public:
	
	User(FullName fio, std::string nick) : FIO(fio), nickName(nick) {}; // Добавить присовение айди, воспользоватья static

	void changeNameUser(FullName newFIO);
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
	FullName FIO;
	std::string nickName;
	std::string status;
	std::string telephoneNumber;
	std::string password;

	//std::list<GroupChat> ListGroupChats;
//	std::list<ContactChat> ListContactChats;
//	std::list <Contact> ListContacts;
};

