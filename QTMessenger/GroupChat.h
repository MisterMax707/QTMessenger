#pragma once
#include <string>
#include <list>
#include "ContactChat.h"
#include "Participator.h"
#include "qstring.h"

class ContactChat;
class Participator;
class Message;

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