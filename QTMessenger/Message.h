#pragma once
#include <chrono>
#include <ctime>
#include "User.h"

class User;

class Message
{
private:
	int id_message;
	User* Mysender;
	std::string content;
	std::chrono::system_clock::time_point timeSend;

public:
	void changeContent(std::string newContent);

};

