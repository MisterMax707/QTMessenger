#pragma once
#include <string>
#include <list>
#include "ContactChat.h"
#include "Participator.h"

class Participator;

class GroupChat //: public ContactChat
{
public:
	GroupChat() {};

private:
	std::string GroupName;
	std::list <Participator*> ListParticipators;
	std::list <Participator*> ListAdmins;
};