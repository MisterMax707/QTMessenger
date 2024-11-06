#pragma once
#include <list>
#include "ContactChat.h"
#include "Participator.h"

class Message;
class Participator;

class GroupChat : public ContactChat
{
public:
	GroupChat(QString name) : GroupName(name) {};

private:
	int id;
	QString GroupName;
	std::list <Participator*> ListParticipators;
	std::list <Participator*> ListAdmins;
};