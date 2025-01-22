#include "Message.h"

Message::Message(QString content, QString sender,QString senderid)
	: content(content), mySender(sender), Senderid(senderid)
{
	id = QString::number(count++);
	timeSend = std::chrono::system_clock::now();
};

QString Message::getContent()
{
	return content;
}

QString Message::getSenderid()
{
	return Senderid;
}
QString Message::getSender()
{
	return mySender;
}

void Message::changeContent(QString& newContent)
{
	content = newContent;
}

QString Message::getId()
{
	return id;
}