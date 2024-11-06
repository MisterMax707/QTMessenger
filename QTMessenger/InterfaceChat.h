#pragma once
#include <QMainWindow>
#include "ui_InterfaceChat.h"
#include "QQueue.h"
#include "User.h"

class InterfaceChat : public QMainWindow
{
	Q_OBJECT

public:
	explicit InterfaceChat(QWidget *parent = nullptr);
	~InterfaceChat();

private:
	Ui::InterfaceChatClass ui;
	User* user;
	GroupChat* chat;
	void clearChatContent();
	void showChatContent();
	bool checkCorrectnessOfMessage(QString contentMessage);
	void setMessageParametersAndStyle(QListWidgetItem* message);
	void setFontSize(QListWidgetItem* message, int size);
	void setFontBackground(QListWidgetItem* message, QColor color);

signals:
	void signalPushSendMessage(QString contentMessage, QString nickName);
	void signalAddMessageToChatForm(QString contentMessage, QString nickName);

public slots:
	void inicializeChat(GroupChat* newChat, User* userChat, QString name);
	void pushSendMessage();
	void sendMessage(QString contentMessage, QString nickName);
	void addMessageToChatForm(QString msg, QString nick);
};
