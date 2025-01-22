#include "ContactChat.h"

void ContactChat::addMessageToChatList(Message* msg)
{
	messages.push_back(msg);
}

void ContactChat::deleteMessageFromChatList(Message* msg)
{
	QQueue<Message*> tempQueue;
	while (!messages.isEmpty())
	{
		Message* current = messages.dequeue();
		if (current != msg)
			tempQueue.enqueue(current);
	}
	messages = tempQueue;
}

QQueue<Message*> ContactChat::getListOfChatMessage()
{
	return messages;
}

QString ContactChat::getStringOfMessage()
{
	QString result = "";
	for (int i = 0; i < messages.size(); i++)
	{
		result += messages[i]->getSender() + "\n" + messages[i]->getContent() + "#" +messages[i]->getSenderid()+"#"+ messages[i]->getId() + "#";
	}
	result.chop(1);
	return result;
}