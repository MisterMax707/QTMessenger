#pragma once
#include <QQueue>
#include "Message.h"

#ifndef BUILD_STATIC
# if defined(QTMESSENGERLIBRARY1_LIB)
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_EXPORT
# else
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTMESSENGERLIBRARY1_EXPORT
#endif

//class Message;

class QTMESSENGERLIBRARY1_EXPORT ContactChat
{
public:
	ContactChat();

	QQueue<Message*> getListOfChatMessage();
	void addMessageToChatList(Message* msg);
	void deleteMessageFromChatList(Message* msg);
	int getIDContactChat();

protected:
	QQueue<Message*> messages;

private:
	static int id_chat;

};

