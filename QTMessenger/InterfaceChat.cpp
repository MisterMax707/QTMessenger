#include "InterfaceChat.h"

InterfaceChat::InterfaceChat(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.lineEdit_nameChatOrContact->setEnabled(false);
	connect(ui.pushButton_sendMessage, &QPushButton::clicked, this, &InterfaceChat::pushSendMessage);
	connect(this, &InterfaceChat::signalPushSendMessage, this, &InterfaceChat::sendMessage);
	connect(this, &InterfaceChat::signalAddMessageToChatForm, this, &InterfaceChat::addMessageToChatForm);
}

InterfaceChat::~InterfaceChat()
{}

void InterfaceChat::inicializeChat(GroupChat* newChat, QString name) 
{
	ui.lineEdit_nameChatOrContact->setText(name);
	chat = newChat;
	clearChatContent();
	showChatContent();
}

void InterfaceChat::clearChatContent()
{
	ui.listWidget_chat->clear();
}

void InterfaceChat::showChatContent()
{
	QQueue<Message*> queueMsg = chat->showAllMessage();
	for (auto* msg : queueMsg)
		addMessageToChatForm(msg->getContent());
}

void InterfaceChat::pushSendMessage()
{
	if (checkCorrectnessOfMessage(ui.lineEdit_chat->text()))
		emit signalPushSendMessage(ui.lineEdit_chat->text());
	else return void();
}

bool InterfaceChat::checkCorrectnessOfMessage(QString contentMessage)
{
	if (contentMessage.trimmed().isEmpty())
		return false;
	else true;
}

void InterfaceChat::sendMessage(QString contentMessage)
{
	chat->addMessage(new Message(contentMessage));
	emit signalAddMessageToChatForm(contentMessage);
}

void InterfaceChat::addMessageToChatForm(QString msg)
{
	QListWidgetItem* message = new QListWidgetItem(msg);
	setMessageParametersAndStyle(message);
	ui.listWidget_chat->addItem(message);
	ui.lineEdit_chat->clear();
}

void InterfaceChat::setMessageParametersAndStyle(QListWidgetItem* message)
{
	int size = 14;
	QColor color(120, 120, 120);
	setFontSize(message, size);
	setFontBackground(message, color);
	message->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
}

void InterfaceChat::setFontSize(QListWidgetItem* message, int size)
{
	QFont messageFont = message->font();
	messageFont.setPointSize(14);
	message->setFont(messageFont);
}

void InterfaceChat::setFontBackground(QListWidgetItem* message, QColor color)
{
	QBrush brush(color);
	message->setBackground(brush);
}

