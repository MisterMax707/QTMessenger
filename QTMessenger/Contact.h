
#pragma once

#include "User.h"

class User;

class Contact
{
public:
	Contact(User* user): user(user)  {};
private:
	User* user;
};

