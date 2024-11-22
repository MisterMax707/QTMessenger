#pragma once
#include <QQueue>
#include "Message.h"

//class Message;

class ContactChat
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

