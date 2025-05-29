#pragma once
#include <QMainWindow>
#include <QShortcut>
#include "ui_InterfaceChat.h"
#include "SocketManager.h"

class InterfaceChat : public QMainWindow
{
	Q_OBJECT

public:
	explicit InterfaceChat(QString id, QString name,QString senderId,SocketManager* socket, QWidget* parent = nullptr);
	~InterfaceChat();

private:
	Ui::InterfaceChatClass ui;
	QString userSender;

	void clearChatContent();
	//void showChatContent();
	void updateInformationChat();

	bool checkCorrectnessOfMessage(QString contentMessage);
	void setMessageParametersAndStyle(QListWidgetItem* messageItem,QString idSender,QString idMessage);
	void setFontSize(QListWidgetItem* messageItem, int size);
	void setFontBackground(QListWidgetItem* messageItem, QColor color);
	void checkSender(QListWidgetItem* messageItem, QString idSender);
	void setLinkToMessage(QListWidgetItem* messageItem, QString idOfMessage);
	SocketManager* socket;
	QByteArray Data;
	QString idOfChat;
	QString idOfParticipators;
	QString idOfSender;
	QString idOfMessageToForward;

signals:
	void signalSendMessage(QString contentMessage, QString nickName);
	//void signalAddMessageToChatForm(Message* msg);
	void signalChangeContentMessage(QString);
	void newsignaladdmes(QString mes);

public slots:
	void downloadMessages(QString str);
	void sendMessage();
	void addMessageToForm(QString idOfChat);
	void showContextMenu(const QPoint& pos);
	void forwardMessage();
	void downloadChats(QString str);
	void selectChatForForward(QListWidgetItem* item);
	//void inicializeChat(GroupChat* theChatUsed, QString chatUserIsYou, QString nameChat);
	//void inicializeContactChat(ContactChat* chat, QString nameChat, User* user1, User* user2);
	//QString /*void*/ pushSendMessage();
	//void sendMessage(QString contentMessage, QString nickName);
	//void addMessageToChatForm(Message* msg);

	/*void changeInputToChangeByPressedKeyC();
	void pushChangeContentMessage();
	void changeContentMessage(QString);
	void deleteMessageByPressedKeyD();
	void callnewsignal();*/
};
