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
	//User* Mysender;
	QString content;
	std::chrono::system_clock::time_point timeSend;

public:
	Message(QString content) : content(content) {};
	QString getContent();
	void changeContent(QString newContent);

};

