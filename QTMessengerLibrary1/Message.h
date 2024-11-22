#pragma once
#include <chrono>
#include <ctime>
#include "QString.h"
//#include "User.h"

#ifndef BUILD_STATIC
# if defined(QTMESSENGERLIBRARY1_LIB)
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_EXPORT
# else
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTMESSENGERLIBRARY1_EXPORT
#endif


//class User;

class QTMESSENGERLIBRARY1_EXPORT Message
{
private:
	static int id_message;
	QString mySender;
	QString content;
	std::chrono::system_clock::time_point timeSend;

public:
	Message(QString content, QString sender);

	int getIDMessage();
	QString getContent();
	QString getSender();
	void changeContent(QString& newContent);

};

