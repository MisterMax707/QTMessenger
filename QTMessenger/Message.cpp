#include "Message.h"

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