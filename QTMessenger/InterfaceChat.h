#pragma once
#include <QMainWindow>
#include "ui_InterfaceChat.h"
#include "qtcpserver.h"
#include "qtcpsocket.h"
#include "QQueue.h"
#include "QListWidget.h"
#include "QShortcut.h"
#include "ContactChat.h"
#include "GroupChat.h"

class InterfaceChat : public QMainWindow
{
	Q_OBJECT

public:
	explicit InterfaceChat(QWidget* parent = nullptr, GroupChat* newChat = nullptr, QString nameUser = nullptr, QString nameChat = nullptr);
	~InterfaceChat();

private:
	Ui::InterfaceChatClass ui;
	GroupChat* chat;
	//ContactChat* chat;
	QString userSender;
	QTcpSocket* socket;
	QByteArray Data;

	void clearChatContent();
	void showChatContent();
	void updateInformationChat();

	void sendToServer(QString str, QString nick);
	void onReadyRead();

	bool checkCorrectnessOfMessage(QString contentMessage);
	void setMessageParametersAndStyle(QListWidgetItem* messageItem, QString sender, int id_msg);
	void setFontSize(QListWidgetItem* messageItem, int size);
	void setFontBackground(QListWidgetItem* messageItem, QColor color);
	void checkSender(QListWidgetItem* messageItem, QString sender);
	void setLinkToMessage(QListWidgetItem* messageItem, int id_msg);

signals:
	void signalSendToServer(QString content, QString sender);

	//void signalSendMessage(QString contentMessage, QString nickName);
	void signalAddMessageToChatForm(QString content, QString sender, int id_msg);
	void signalChangeContentMessage(QString);

public slots:
	//void inicializeContactChat(ContactChat* chat, QString nameChat, User* user1, User* user2);
	void pushSendMessage();
	//void sendMessage(QString contentMessage, QString nickName);
	void addMessageToChatForm(QString content, QString sender, int id_msg);

	//void changeInputToChangeByPressedKeyC();
	//void pushChangeContentMessage();
	//void changeContentMessage(QString);
	//void deleteMessageByPressedKeyD();
};
