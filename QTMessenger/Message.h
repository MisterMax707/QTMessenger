#pragma once
#include <chrono>
#include <ctime>
#include "QString.h"
//#include "User.h"

//class User;

class Message
{
private:
	int id_message;
	QString mySender;
	QString content;
	std::chrono::system_clock::time_point timeSend;

public:
	Message(QString content, QString sender) : content(content), mySender(sender) {};
	QString getContent();
	QString getSender();
	void changeContent(QString newContent);

};

