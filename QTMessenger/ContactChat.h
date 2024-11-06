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
	QQueue<Message*> showAllMessage();
	void addMessage(Message* msg);
	void deleteMessage();

	int getId() {return this->id;}
};

