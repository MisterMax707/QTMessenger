#pragma once
#include <list>
#include "Message.h"

class Message;

class ContactChat
{
private:
	int id_Chat;

protected:
	std::list<Message*> messages;

public:
	ContactChat() {};
	void sendMessage();
	void deleteMessage();
	// change Message
};

