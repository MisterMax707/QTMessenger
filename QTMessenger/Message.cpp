#include "Message.h"

QString Message::getContent()
{
	return content;
}

void Message::changeContent(QString newContent)
{
	content = newContent;
}