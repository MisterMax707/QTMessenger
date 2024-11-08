#pragma once
#include <QQueue>
#include "Message.h"

//class Message;

class ContactChat
{
private:
	int id;

protected:
	QQueue<Message*> messages;

public:
	ContactChat() {};

	QQueue<Message*> getListOfChatMessage();
	void addMessageToChatList(Message* msg);
	void deleteMessageFromChatList();

	int getId() {return this->id;}
};

