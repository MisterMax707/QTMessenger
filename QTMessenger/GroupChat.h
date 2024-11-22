#pragma once
#include <QList>
#include "ContactChat.h"
#include "Participator.h"

class Message;
class Participator;

class GroupChat : public ContactChat
{
public:
	GroupChat(QString name);
	int getIDGroupChat();

private:
	static int id_group;
	QString GroupName;
	QList <Participator*> ListParticipators;
	QList <Participator*> ListAdmins;
};