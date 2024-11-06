#pragma once
#include <QMainWindow>
#include "ui_InterfaceChat.h"
#include "QQueue.h"
#include "User.h"

class InterfaceChat : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceChat(QWidget *parent = nullptr);
	~InterfaceChat();

private:
	Ui::InterfaceChatClass ui;
	GroupChat* chat;
	void clearChatContent();
	void showChatContent();
	bool checkCorrectnessOfMessage(QString contentMessage);
	void setMessageParametersAndStyle(QListWidgetItem* message);
	void setFontSize(QListWidgetItem* message, int size);
	void setFontBackground(QListWidgetItem* message, QColor color);

signals:
	void signalPushSendMessage(QString contentMessage);
	void signalAddMessageToChatForm(QString contentMessage);

public slots:
	void inicializeChat(GroupChat* newChat, QString name);
	void pushSendMessage();
	void sendMessage(QString contentMessage);
	void addMessageToChatForm(QString msg);
};
