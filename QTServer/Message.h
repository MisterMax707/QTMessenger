#pragma once
#include <chrono>
#include <ctime>
#include "QString.h"
//#include "User.h"

//class User;

class Message
{
private:
	QString id;
	QString mySender;
	QString Senderid;
	QString content;
	std::chrono::system_clock::time_point timeSend;
	static inline unsigned count{};

public:
	Message(QString content, QString sender, QString senderid);

	void changeContent(QString& newContent);
	QString getContent();
	QString getSenderid();
	QString getSender();
	QString getId();

};

