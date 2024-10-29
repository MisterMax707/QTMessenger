#include "User.h"

QStringList splitFIOintoComponents(QString& fio)
{
	QStringList words = fio.split(' '); // Разбиваем строку по пробелам
	words.removeAll(""); // Удаляем пустые строки
	determineEnteredFIO(words);
	return words;
}

void determineEnteredFIO(QStringList& words)
{
	int size = words.size();
	for (int i = size - 1; i < 3; i++)
		words.push_back("");
}


void User::changeNameUser(FullName newFIO)
{
	FIO.name = newFIO.name;
	FIO.surname = newFIO.surname;
	FIO.patronymic = newFIO.patronymic;
}

void User::changeNickName(QString newNickName)
{
	nickName = newNickName;
}

void User::changeStatus(QString newStatus)
{
	status = newStatus;
}

void User::createContact()
{

}

void User::createGroupChat()
{

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
