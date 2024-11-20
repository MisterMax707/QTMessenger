#pragma once

#include <QObject>

class ChatServer  : public QObject
{
	Q_OBJECT

public:
	ChatServer(QObject *parent);
	~ChatServer();
};
