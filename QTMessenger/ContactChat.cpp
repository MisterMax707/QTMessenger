#include "ContactChat.h"

void ContactChat::addMessageToChatList(Message* msg)
{
	messages.push_back(msg);
}

void ContactChat::deleteMessageFromChatList()
{

}

QQueue<Message*> ContactChat::getListOfChatMessage()
{
	return messages;
}