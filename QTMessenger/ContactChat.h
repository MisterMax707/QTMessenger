#pragma once
#include "CustomQueue.h"
#include "Message.h"

class ContactChat
{
private:
	int id_contactChat;

protected:
	CustomQueue<Message> messages;

public:
	void sendMessage();
	void deleteMessage();
	// change Message
};

