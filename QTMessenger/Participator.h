#pragma once
#include "User.h"
class Participator
{public:
	User* member;
	bool adminrights = false;
	void leaveChat();
private:

};

