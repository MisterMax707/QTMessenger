#pragma once
#include "../include/QtCore/qdatastream.h"

namespace cod
{
	enum CodeWord
	{
		LOGIN,
		REGISTRATION,

		LIST_OF_CHATS,
		LIST_OF_CONTACTS,
		LIST_OF_MESSAGES,
		ADD_CHAT,
		ADD_CONTACT,

		ADD_MESSAGE,


		LOGIN_ANSWER,
		REGISTRATION_ANSWER,

		LIST_OF_CHATS_ANSWER,
		LIST_OF_CONTACTS_ANSWER,
		LIST_OF_MESSAGES_ANSWER,
		ADD_CHAT_ANSWER,

		ADD_MESSAGE_ANSWER,
	};
}

QDataStream& operator<<(QDataStream& out, const cod::CodeWord& value) {
	return out << static_cast<quint8>(value); // Преобразуем в байт
}

QDataStream& operator>>(QDataStream& in, cod::CodeWord& value) {
	quint8 byteValue;
	in >> byteValue;
	value = static_cast<cod::CodeWord>(byteValue); // Преобразуем обратно в enum
	return in;
}


