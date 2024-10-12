#pragma once
#include "ContactChat.h"
#include "list"
#include "string"
#include "Participator.h"
class GroupChat :ContactChat {
private:
	string GroupName;
	std::list<Participator*> ListParticipators;
	std::list <Participator*> ListAdmins;


};