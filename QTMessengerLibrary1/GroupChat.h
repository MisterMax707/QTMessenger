#pragma once
#include <QList>
#include "ContactChat.h"
#include "Participator.h"

#ifndef BUILD_STATIC
# if defined(QTMESSENGERLIBRARY1_LIB)
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_EXPORT
# else
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTMESSENGERLIBRARY1_EXPORT
#endif

class Message;
class Participator;

class QTMESSENGERLIBRARY1_EXPORT GroupChat : public ContactChat
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