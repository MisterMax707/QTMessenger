
#pragma once

#include "User.h"

class User;

class Contact
{
public:
	Contact(QString id, QString NickName) :id(id), NickName(NickName) {};
	QString getId() { return this->id; };
	QString getName() {return this->NickName; };
private:
	QString id;
	QString NickName;
};

