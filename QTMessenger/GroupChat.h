#pragma once
#include "ContactChat.h"
#include "list"
class GroupChat :ContactChat {
private:
	string GroupName;
	std::list<Participator*> ListParticipators;
	std::list <Participator*> ListAdmins;


};