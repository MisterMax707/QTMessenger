#pragma once
#include <list>
#include "ContactChat.h"
#include "Participator.h"

class Message;
class Participator;

class GroupChat : public ContactChat
{
public:
	GroupChat(const QString& name, const QVector<QString>& usersId);
	
	QString getId();
	QString getGroupName() { return this->GroupName; };

private:
	QString id;
	QString GroupName;
	
	QList <QString> ListParticipators;
	//QList <Participator*> ListAdmins;

	static inline unsigned count{};
};