#include "InterfaceChat.h"

InterfaceChat::InterfaceChat(QWidget* parent, GroupChat* newChat, QString nameUser, QString nameChat)
	: QMainWindow(parent), chat(newChat), userSender(nameUser)
{
	ui.setupUi(this);
	updateInformationChat();

	socket = new QTcpSocket(this);
	socket->connectToHost("127.0.0.1", 2323);
	ui.lineEdit_nameChatOrContact->setText(nameChat);
	ui.lineEdit_nameChatOrContact->setEnabled(false);
	ui.stackedWidget->setCurrentIndex(0);

	QShortcut* pressChangeMessage = new QShortcut(QKeySequence(Qt::Key_C), this);
	QShortcut* pressDeleteMessage = new QShortcut(QKeySequence(Qt::Key_D), this);

	connect(ui.pushButton_sendMessage, &QPushButton::clicked, this, &InterfaceChat::pushSendMessage);
	connect(ui.pushButton_changeMessage, &QPushButton::clicked, this, &InterfaceChat::pushChangeContentMessage);
	connect(this, &InterfaceChat::signalSendMessage, this, &InterfaceChat::sendMessage);
	connect(this, &InterfaceChat::signalAddMessageToChatForm, this, &InterfaceChat::addMessageToChatForm);
	connect(this, &InterfaceChat::signalChangeContentMessage, this, &InterfaceChat::changeContentMessage);
	connect(pressChangeMessage, &QShortcut::activated, this, &InterfaceChat::changeInputToChangeByPressedKeyC);
	connect(pressDeleteMessage, &QShortcut::activated, this, &InterfaceChat::deleteMessageByPressedKeyD);

	connect(socket, &QTcpSocket::readyRead, this, &InterfaceChat::onReadyRead);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
	connect(this, &InterfaceChat::signalSendToServer, this, &InterfaceChat::sendToServer);
}

InterfaceChat::~InterfaceChat()
{}

//void InterfaceChat::inicializeContactChat(ContactChat* chat, QString nameChat, User* user1, User* user2) {
//	this->chat = chat;
//	ui.lineEdit_nameChatOrContact->setText(nameChat);
//
//}

void InterfaceChat::updateInformationChat()
{
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
	{
		//emit signalSendMessage(ui.lineEdit_chat->text(), userSender);
		emit signalSendToServer(ui.lineEdit_chat->text(), userSender);
		ui.lineEdit_chat->clear();
	}
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
	Message* msg = new Message(contentMessage, nickName);
	chat->addMessageToChatList(msg);
	emit signalAddMessageToChatForm(msg);
}

void InterfaceChat::addMessageToChatForm(Message* msg)
{
	QString fullMessage = msg->getSender() + "\n" + msg->getContent();
	QListWidgetItem* messageItem = new QListWidgetItem(fullMessage);
	setMessageParametersAndStyle(messageItem, msg);
	ui.listWidget_chat->addItem(messageItem);
}

void InterfaceChat::setMessageParametersAndStyle(QListWidgetItem* messageItem, Message* msg)
{
	int size = 14;
	QColor color(120, 120, 120);
	setFontSize(messageItem, size);
	setFontBackground(messageItem, color);
	setLinkToMessage(messageItem, msg);
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

void InterfaceChat::setLinkToMessage(QListWidgetItem* messageItem, Message* msg)
{
	messageItem->setData(Qt::UserRole, QVariant::fromValue(msg));
}

void InterfaceChat::checkSender(QListWidgetItem* messageItem, Message* msg)
{
	if(msg->getSender() == userSender)
		messageItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	else
		messageItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}


void InterfaceChat::deleteMessageByPressedKeyD()
{
	if (ui.listWidget_chat->currentItem())
	{
		QListWidgetItem* selectMessageItem = ui.listWidget_chat->currentItem();
		Message* msg = selectMessageItem->data(Qt::UserRole).value<Message*>();

		delete ui.listWidget_chat->takeItem(ui.listWidget_chat->row(selectMessageItem));
		chat->deleteMessageFromChatList(msg);
		ui.statusBar->showMessage("delete message" , 5000);

		updateInformationChat();
	}
	else
		ui.statusBar->showMessage("Select message for delete", 5000);

}

void InterfaceChat::changeInputToChangeByPressedKeyC()
{
	if (ui.listWidget_chat->currentItem())
	{
		QListWidgetItem* selectMessageItem = ui.listWidget_chat->currentItem();
		Message* msg = selectMessageItem->data(Qt::UserRole).value<Message*>();
		ui.lineEdit_changeMessage->setText(msg->getContent());

		int pageChangMessage = 1;
		ui.stackedWidget->setCurrentIndex(pageChangMessage);
	}
	else
		ui.statusBar->showMessage("Select message for changing", 5000);
}

void InterfaceChat::pushChangeContentMessage()
{
	if (checkCorrectnessOfMessage(ui.lineEdit_changeMessage->text()))
	{
		emit signalChangeContentMessage(ui.lineEdit_changeMessage->text());
	}
	else
	{
		ui.statusBar->showMessage("The change cannot be empty", 5000);
		return void();
	}
}

void InterfaceChat::changeContentMessage(QString content)
{
	QListWidgetItem* selectMessageItem = ui.listWidget_chat->currentItem();
	Message* msg = selectMessageItem->data(Qt::UserRole).value<Message*>();
	msg->changeContent(content);

	int pageSendMessage = 0;
	ui.lineEdit_changeMessage->clear();
	ui.stackedWidget->setCurrentIndex(pageSendMessage);

	updateInformationChat();
}



void InterfaceChat::sendToServer(QString str, QString nick)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << str << nick;
	socket->write(Data);

}

void InterfaceChat::onReadyRead()
{
	socket = (QTcpSocket*)sender();
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_6_2);
	if (in.status() == QDataStream::Ok)
	{
		QString str;
		QString nick;
		in >> str >> nick;
		emit signalSendMessage(str, nick);
	}
	else
	{
		emit signalSendMessage("read error", "ошибка+ошибка");
	}
}