#pragma once
#include <list>
#include "ContactChat.h"
#include "Participator.h"

class Message;
class Participator;

class GroupChat : public ContactChat
{
public:
	GroupChat(QString name, QStringList usersId) : GroupName(name),usersId(usersId) {
		id =QString::number( count++);

	};
	
	QString getId() { return this->id; };
	QString getGroupName() { return this->GroupName; };
	QStringList usersId;

private:
	QString id;
	QString GroupName;
	
	std::list <Participator*> ListParticipators;
	std::list <Participator*> ListAdmins;
private:
	static inline unsigned count{};
};