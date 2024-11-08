#include "InterfaceChat.h"

InterfaceChat::InterfaceChat(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.lineEdit_nameChatOrContact->setEnabled(false);
	connect(ui.pushButton_sendMessage, &QPushButton::clicked, this, &InterfaceChat::pushSendMessage);
	connect(this, &InterfaceChat::signalSendMessage, this, &InterfaceChat::sendMessage);
	connect(this, &InterfaceChat::signalAddMessageToChatForm, this, &InterfaceChat::addMessageToChatForm);
}

InterfaceChat::~InterfaceChat()
{}

void InterfaceChat::inicializeChat(GroupChat* theChatUsed, QString chatUserIsYou, QString nameChat)
{
	chat = theChatUsed;
	userSender = chatUserIsYou;
	ui.lineEdit_nameChatOrContact->setText(nameChat);
	clearChatContent();
	showChatContent();
}

void InterfaceChat::clearChatContent()
{
	ui.listWidget_chat->clear();
}

void InterfaceChat::showChatContent()
{
	QQueue<Message*> queueMsg = chat->getListOfChatMessage();
	for (auto* msg : queueMsg)
		addMessageToChatForm(msg);
}

void InterfaceChat::pushSendMessage()
{
	if (checkCorrectnessOfMessage(ui.lineEdit_chat->text()))
		emit signalSendMessage(ui.lineEdit_chat->text(), userSender);
	else return void();
}

bool InterfaceChat::checkCorrectnessOfMessage(QString contentMessage)
{
	if (contentMessage.trimmed().isEmpty())
		return false;
	else true;
}

void InterfaceChat::sendMessage(QString contentMessage, QString nickName)
{
	chat->addMessageToChatList(new Message(contentMessage, nickName));
	emit signalAddMessageToChatForm(new Message(contentMessage, nickName));
}

void InterfaceChat::addMessageToChatForm(Message* msg)
{
	QString fullMessage = msg->getSender() + "\n" + msg->getContent();
	QListWidgetItem* messageItem = new QListWidgetItem(fullMessage);
	setMessageParametersAndStyle(messageItem, msg);
	ui.listWidget_chat->addItem(messageItem);
	ui.lineEdit_chat->clear();
}

void InterfaceChat::setMessageParametersAndStyle(QListWidgetItem* messageItem, Message* msg)
{
	int size = 14;
	QColor color(120, 120, 120);
	setFontSize(messageItem, size);
	setFontBackground(messageItem, color);
	checkSender(messageItem, msg);
}

void InterfaceChat::setFontSize(QListWidgetItem* messageItem, int size)
{
	QFont messageFont = messageItem->font();
	messageFont.setPointSize(14);
	messageItem->setFont(messageFont);
}

void InterfaceChat::setFontBackground(QListWidgetItem* messageItem, QColor color)
{
	QBrush brush(color);
	messageItem->setBackground(brush);
}

void InterfaceChat::checkSender(QListWidgetItem* messageItem, Message* msg)
{
	if(msg->getSender() == userSender)
		messageItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	else
		messageItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

