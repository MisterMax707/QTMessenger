#pragma once
#include "User.h"

#ifndef BUILD_STATIC
# if defined(QTMESSENGERLIBRARY1_LIB)
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_EXPORT
# else
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTMESSENGERLIBRARY1_EXPORT
#endif

class User;

class QTMESSENGERLIBRARY1_EXPORT Participator
{
public:
	//Participator(User* member) : member(member) {};
	//User* member;
	bool adminrights = false;
	void leaveChat();

private:

};

