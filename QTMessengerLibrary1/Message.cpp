#include "Message.h"

int Message::id_message = 0;

Message::Message(QString content, QString sender) 
	: content(content), mySender(sender) 
{
	id_message++;
	timeSend = std::chrono::system_clock::now();
};

int Message::getIDMessage()
{
	return id_message;
}

QString Message::getContent()
{
	return content;
}

QString Message::getSender()
{
	return mySender;
}

void Message::changeContent(QString& newContent)
{
	content = newContent;
}