#include "Message.h"

Message::Message(QString content, QString sender) 
	: content(content), mySender(sender) 
{
	timeSend = std::chrono::system_clock::now();
};

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