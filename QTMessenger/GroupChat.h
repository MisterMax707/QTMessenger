#pragma once
#include <string>
#include <list>
#include "ContactChat.h"
#include "Participator.h"
#include "qstring.h"
class Participator;

class GroupChat //: public ContactChat
{
public:
	GroupChat(QString name) {
		GroupName = name;
	};
	
private:
	QString GroupName;
	std::list <Participator*> ListParticipators;
	std::list <Participator*> ListAdmins;
};