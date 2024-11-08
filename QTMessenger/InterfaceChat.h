#pragma once
#include <QMainWindow>
#include "ui_InterfaceChat.h"
#include "QQueue.h"
#include "QListWidget.h"
#include "QShortcut.h"
#include "ContactChat.h"
#include "GroupChat.h"

class InterfaceChat : public QMainWindow
{
	Q_OBJECT

public:
	explicit InterfaceChat(QWidget *parent = nullptr);
	~InterfaceChat();

private:
	Ui::InterfaceChatClass ui;
	GroupChat* chat;
	QString userSender;

	void clearChatContent();
	void showChatContent();

	bool checkCorrectnessOfMessage(QString contentMessage);
	void setMessageParametersAndStyle(QListWidgetItem* messageItem, Message* msg);
	void setFontSize(QListWidgetItem* messageItem, int size);
	void setFontBackground(QListWidgetItem* messageItem, QColor color);
	void setLinkToMessage(QListWidgetItem* messageItem, Message* msg);
	void checkSender(QListWidgetItem* messageItem, Message* msg);

signals:
	void signalSendMessage(QString contentMessage, QString nickName);
	void signalAddMessageToChatForm(Message* msg);

public slots:
	void inicializeChat(GroupChat* theChatUsed, QString chatUserIsYou, QString nameChat);

	void pushSendMessage();
	void sendMessage(QString contentMessage, QString nickName);
	void addMessageToChatForm(Message* msg);

	void deleteMessageByPressedKeyD();
};
