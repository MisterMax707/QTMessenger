#include "InterfaceChat.h"
#include "qmessagebox.h"
InterfaceChat::InterfaceChat(QString id, QString name, QString senderId, SocketManager* socket, QWidget* parent)
	: QMainWindow(parent), idOfChat(id), idOfSender(senderId), socket(socket)
{
	ui.setupUi(this);
	ui.lineEdit_nameChatOrContact->setEnabled(false);
	ui.lineEdit_nameChatOrContact->setText(name);

	QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this); // enter

	connect(this->socket, &SocketManager::signalTransmitMessangesToForm, this, &InterfaceChat::downloadMessages);
	connect(ui.pushButton_sendMessage, &QPushButton::clicked, this, &InterfaceChat::sendMessage);
	connect(shortcut, &QShortcut::activated, this, &InterfaceChat::sendMessage);
	connect(this->socket, &SocketManager::signalAddMessageToForm, this, &InterfaceChat::addMessageToForm);
	ui.listWidget_chat->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.listWidget_chat, &QListWidget::customContextMenuRequested, this, &InterfaceChat::showContextMenu);
	connect(this->socket, &SocketManager::signalTransmitChatsForForwardToForm, this, &InterfaceChat::downloadChats);
	connect(ui.listWidget, &QListWidget::itemClicked, this, &InterfaceChat::selectChatForForward);
	/*QShortcut* pressChangeMessage = new QShortcut(QKeySequence(Qt::Key_C), this);
	QShortcut* pressDeleteMessage = new QShortcut(QKeySequence(Qt::Key_D), this);*/
	//connect(ui.pushButton_sendMessage, & QPushButton::clicked, this, & InterfaceChat::callnewsignal);
	//connect(ui.pushButton_sendMessage, &QPushButton::clicked, this, &InterfaceChat::newpushSendMessage);
	//connect(ui.pushButton_changeMessage, &QPushButton::clicked, this, &InterfaceChat::pushChangeContentMessage);
	/*connect(this, &InterfaceChat::signalSendMessage, this, &InterfaceChat::sendMessage);
	connect(this, &InterfaceChat::signalAddMessageToChatForm, this, &InterfaceChat::addMessageToChatForm);
	connect(this, &InterfaceChat::signalChangeContentMessage, this, &InterfaceChat::changeContentMessage);
	connect(pressChangeMessage, &QShortcut::activated, this, &InterfaceChat::changeInputToChangeByPressedKeyC);
	connect(pressDeleteMessage, &QShortcut::activated, this, &InterfaceChat::deleteMessageByPressedKeyD);*/
}



InterfaceChat::~InterfaceChat()
{}

void InterfaceChat::downloadMessages(QString str)
{
	ui.listWidget_chat->clear();
	//QString idOfMessage, messageContent;
	while (!str.isEmpty())
	{
		QString messageContent = str.left(str.indexOf('#'));
		str = str.mid(str.indexOf('#') + 1);
		QString idOfSender = str.left(str.indexOf('#'));
		str = str.mid(str.indexOf('#') + 1);
		QString idOfMessage = str.left(str.indexOf('#'));
		QListWidgetItem* newItem = new QListWidgetItem(messageContent);
		if (str.indexOf('#') == -1)
		{
			setMessageParametersAndStyle(newItem, idOfSender, idOfMessage);
			ui.listWidget_chat->addItem(newItem);
			break;
		}
		else {
			str = str.mid(str.indexOf('#') + 1);
			setMessageParametersAndStyle(newItem, idOfSender, idOfMessage);
			ui.listWidget_chat->addItem(newItem);
		}
	}
}


void InterfaceChat::addMessageToForm(QString str)//строка состоит из содержания сообщения id отправителя и  id сообщения
{
	QString idChat = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	if (idChat == idOfChat)
	{
		QString messageContent = str.left(str.indexOf('#'));
		str = str.mid(str.indexOf('#') + 1);
		QString idOfSender = str.left(str.indexOf('#'));
		str = str.mid(str.indexOf('#') + 1);
		QString idOfMessage = str.left(str.indexOf('#'));
		QListWidgetItem* newItem = new QListWidgetItem(messageContent);
		setMessageParametersAndStyle(newItem, idOfSender, idOfMessage);
		ui.listWidget_chat->addItem(newItem);
	}
}

void InterfaceChat::sendMessage()
{
	socket->sendToServer("ADD_MESSAGE " + ui.lineEdit_chat->text() + "#" + idOfSender + "#" + idOfChat);
	ui.lineEdit_chat->clear();
}




//void InterfaceChat::inicializeChat(GroupChat* theChatUsed, QString chatUserIsYou, QString nameChat)
//{
//	chat = theChatUsed;
//	userSender = chatUserIsYou;
//	ui.lineEdit_nameChatOrContact->setText(nameChat);
//	updateInformationChat();
//}
//void InterfaceChat::inicializeContactChat(ContactChat* chat, QString nameChat, User* user1, User* user2) {
////	this->chat = chat;
//	ui.lineEdit_nameChatOrContact->setText(nameChat);
//
//}

//void InterfaceChat::updateInformationChat()
//{
//	clearChatContent();
//	showChatContent();
//}
//
//void InterfaceChat::clearChatContent()
//{
//	ui.listWidget_chat->clear();
//}

//void InterfaceChat::showChatContent()
//{
//	QQueue<Message*> queueMsg = chat->getListOfChatMessage();
//	for (auto* msg : queueMsg)
//		addMessageToChatForm(msg);
//}

//QString /*void*/ InterfaceChat::pushSendMessage()
//{
//	if (checkCorrectnessOfMessage(ui.lineEdit_chat->text()))
//	{
//		
//		return ui.lineEdit_chat->text();
//	}
//	ui.lineEdit_chat->clear();
//		
//
//		//emit signalSendMessage(ui.lineEdit_chat->text(), userSender); потом раскоментировать 
//	//else return void();
//}

bool InterfaceChat::checkCorrectnessOfMessage(QString contentMessage)
{
	if (contentMessage.trimmed().isEmpty())
		return false;
	else true;
}

//void InterfaceChat::sendMessage(QString contentMessage, QString nickName)
//{
//	Message* msg = new Message(contentMessage, nickName);
//	chat->addMessageToChatList(msg);
//	emit signalAddMessageToChatForm(msg);
//}
//
//void InterfaceChat::addMessageToChatForm(Message* msg)
//{
//	QString fullMessage = msg->getSender() + "\n" + msg->getContent();
//	QListWidgetItem* messageItem = new QListWidgetItem(fullMessage);
//	setMessageParametersAndStyle(messageItem, msg);
//	ui.listWidget_chat->addItem(messageItem);
//	ui.lineEdit_chat->clear();
//}
//
void InterfaceChat::setMessageParametersAndStyle(QListWidgetItem* messageItem, QString idSender, QString idMessage)
{
	int size = 14;
	QColor color(120, 120, 120);
	setFontSize(messageItem, size);
	setFontBackground(messageItem, color);
	setLinkToMessage(messageItem, idMessage);
	checkSender(messageItem, idSender);
}
//
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

void InterfaceChat::setLinkToMessage(QListWidgetItem* messageItem, QString idOfMessage)
{
	messageItem->setData(Qt::UserRole, idOfMessage);
}
//
void InterfaceChat::checkSender(QListWidgetItem* messageItem, QString idSender)
{
	if (idOfSender == idSender)
		messageItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	else
		messageItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void InterfaceChat::showContextMenu(const QPoint& pos)
{
	QListWidgetItem* item = ui.listWidget_chat->itemAt(pos);
	if (!item) return;

	// Создаем меню
	QMenu menu(this);

	// Добавляем действие "Переслать"
	QAction* forwardAction = menu.addAction("forward");
	forwardAction->setData(item->data(Qt::UserRole)); // Передаем ID в данные действия
	connect(forwardAction, &QAction::triggered, this, &InterfaceChat::forwardMessage);



	// Показываем меню
	menu.exec(ui.listWidget_chat->viewport()->mapToGlobal(pos));
}
void InterfaceChat::forwardMessage()
{
	QAction* action = qobject_cast<QAction*>(sender());
	if (!action) return;

	QString messageId = action->data().toString(); // Получаем ID из данных действия
	idOfMessageToForward = messageId;
	socket->sendToServer("LIST_OF_CHATS_FORWARD " + idOfSender);
	ui.stackedWidget_2->setCurrentIndex(1);




	// Здесь можно добавить реальную логику пересылки
}

void InterfaceChat::downloadChats(QString str)
{
	ui.listWidget->clear();
	QString chatName, id;
	while (!str.isEmpty())
	{
		chatName = str.left(str.indexOf('#'));
		str = str.mid(str.indexOf('#') + 1);
		QListWidgetItem* chatListItem = new QListWidgetItem(chatName);
		chatListItem->setSizeHint(QSize(60, 50));
		id = str.left(str.indexOf('#'));
		if (str.indexOf('#') == -1)
		{
			chatListItem->setData(Qt::UserRole, id);
			ui.listWidget->addItem(chatListItem);
			break;
		}
		else {
			str = str.mid(str.indexOf('#') + 1);
			chatListItem->setData(Qt::UserRole, id);
			ui.listWidget->addItem(chatListItem);
		}
	}
}
void InterfaceChat::selectChatForForward(QListWidgetItem* item) {
	socket->sendToServer("FORWARD_MESSAGE " + idOfMessageToForward + "#" + item->data(Qt::UserRole).toString());
	idOfMessageToForward = "";
	ui.stackedWidget_2->setCurrentIndex(0);
	QMessageBox::information(this, "Пересылка",
		QString("Message reposted succesfully! (ID: %1)\n")
		.arg(idOfMessageToForward));
	
}
//
//
//void InterfaceChat::deleteMessageByPressedKeyD()
//{
//	if (ui.listWidget_chat->currentItem())
//	{
//		QListWidgetItem* selectMessageItem = ui.listWidget_chat->currentItem();
//		Message* msg = selectMessageItem->data(Qt::UserRole).value<Message*>();
//
//		delete ui.listWidget_chat->takeItem(ui.listWidget_chat->row(selectMessageItem));
//		chat->deleteMessageFromChatList(msg);
//		ui.statusBar->showMessage("delete message" , 5000);
//
//		updateInformationChat();
//	}
//	else
//		ui.statusBar->showMessage("Select message for delete", 5000);
//
//}
//
//void InterfaceChat::changeInputToChangeByPressedKeyC()
//{
//	if (ui.listWidget_chat->currentItem())
//	{
//		QListWidgetItem* selectMessageItem = ui.listWidget_chat->currentItem();
//		Message* msg = selectMessageItem->data(Qt::UserRole).value<Message*>();
//		ui.lineEdit_changeMessage->setText(msg->getContent());
//
//		int pageChangMessage = 1;
//		ui.stackedWidget->setCurrentIndex(pageChangMessage);
//	}
//	else
//		ui.statusBar->showMessage("Select message for changing", 5000);
//}
//
//void InterfaceChat::pushChangeContentMessage()
//{
//	if (checkCorrectnessOfMessage(ui.lineEdit_changeMessage->text()))
//	{
//		emit signalChangeContentMessage(ui.lineEdit_changeMessage->text());
//	}
//	else
//	{
//		ui.statusBar->showMessage("The change cannot be empty", 5000);
//		return void();
//	}
//}
//
//void InterfaceChat::changeContentMessage(QString content)
//{
//	QListWidgetItem* selectMessageItem = ui.listWidget_chat->currentItem();
//	Message* msg = selectMessageItem->data(Qt::UserRole).value<Message*>();
//	msg->changeContent(content);
//
//	int pageSendMessage = 0;
//	ui.lineEdit_changeMessage->clear();
//	ui.stackedWidget->setCurrentIndex(pageSendMessage);
//
//	updateInformationChat();
//}
//
//
//void InterfaceChat::callnewsignal() {
//	emit newsignaladdmes(ui.lineEdit_chat->text());
//}
