#include "ContactChat.h"

void ContactChat::addMessage(Message* msg)
{
	messages.push_back(msg);
}

void ContactChat::deleteMessage()
{

}

QQueue<Message*> ContactChat::showAllMessage()
{
	return messages;
}