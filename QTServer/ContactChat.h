#pragma once
#include <QQueue>
#include "Message.h"

//class Message;

class ContactChat
{
private:
	QString id;
	QString name;
protected:
	QQueue<Message*> messages;

public:
	ContactChat() {};

	QQueue<Message*> getListOfChatMessage();
	void addMessageToChatList(Message* msg);
	void deleteMessageFromChatList(Message* msg);
	QString getStringOfMessage();
	QString getId() { return this->id; }
};

