#include "User.h"

QStringList splitFIOintoComponents(QString& fio)
{
	QRegularExpression re("\\s+"); // ���������� ��������� ��� ��������
	QStringList words = fio.split(re);
	words.removeAll(""); // ������� ������ ������
	refillingFullName(words);
	return words;
}

void refillingFullName(QStringList& words)
{
	int size = words.size();
	int lenghtFullName = 2;
	for (int i = size - 1; i < lenghtFullName; i++)
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
