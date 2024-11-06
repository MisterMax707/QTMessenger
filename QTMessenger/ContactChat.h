#pragma once
#include <list>
//#include "Message.h"

class Message;

class ContactChat
{
private:
	int id;

protected:
	std::list<Message*> messages;

public:
	ContactChat() {};
	void sendMessage();
	void deleteMessage();
	int getId() {
		return this->id;
	}
	// change Message
};

