#pragma once
#include <list>
#include "Message.h"

class ContactChat
{
private:
	int id_Chat;

protected:
	//std::list<Message> messages;

public:
	void sendMessage();
	void deleteMessage();
	// change Message
};

