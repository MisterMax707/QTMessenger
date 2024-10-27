#pragma once
#include "User.h"

class User;

class Participator
{
public:
	Participator(User* member) : member(member) {};
	User* member;
	bool adminrights = false;
	void leaveChat();

private:

};

