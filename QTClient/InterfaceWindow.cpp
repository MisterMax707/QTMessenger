#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QString id, SocketManager* socket, QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.listWidget_2->setSelectionMode(QAbstractItemView::MultiSelection);
	ui.stackedWidget->setCurrentIndex(0);
	ui.lineEdit_userName->setEnabled(false);

	ui.lineEdit_userName->setText("UsersId: " + id);
	userId = id;
	this->socket = socket;

	connect(this->socket, &SocketManager::signalTransmitChatsToForm, this, &InterfaceWindow::downloadChats);
	connect(this->socket, &SocketManager::signalTransmitContactsToForm, this, &InterfaceWindow::createContacts);
	connect(this->socket, &SocketManager::signalAddChatToForm, this, &InterfaceWindow::addChat);
	connect(ui.pushButton_add, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);
	connect(ui.pushButton_backToMainWindow, &QPushButton::clicked, this, &InterfaceWindow::openMainWindow);
	connect(ui.pushButton_createGroup, &QPushButton::clicked, this, &InterfaceWindow::openEnterNameGroupChat);
	connect(ui.pushButton_okCreateGroup, &QPushButton::clicked, this, &InterfaceWindow::pushOkCreateGroupChat);
	connect(ui.pushButton_returnToPageCreateGroupOrContact, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);
	connect(ui.listWidget, &QListWidget::itemClicked, this, &InterfaceWindow::onGroupChatClicked);
	connect(this, &InterfaceWindow::signalCreateChatWindow, this, &InterfaceWindow::createChatWindow);
	//connect(ui.pushButton_returnToPageCreateContact, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);

	//connect(this, &InterfaceWindow::signalpushCreateGroupChat, this, &InterfaceWindow::createGroupChat);
	//connect(this, &InterfaceWindow::signalAddChatToForm, this, &InterfaceWindow::addChatToForm);
	/*connect(ui.pushButton_newContact, &QPushButton::clicked, this, &InterfaceWindow::openInicializateContactPage);
	connect(ui.pushButton_CreateContact, &QPushButton::clicked, this, &InterfaceWindow::pushCreateContact);
	connect(this, &InterfaceWindow::signalCreateContact, this, &InterfaceWindow::createContact);*/

}

InterfaceWindow::~InterfaceWindow()
{}




void InterfaceWindow::downloadChats(QString str)
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



void InterfaceWindow::pushAdd()
{
	ui.stackedWidget->setCurrentIndex(1);
}

void InterfaceWindow::openMainWindow()
{
	socket->sendToServer("LIST_OF_CHATS " + userId);
	ui.stackedWidget->setCurrentIndex(0);
}
void InterfaceWindow::openEnterNameGroupChat()
{
	socket->sendToServer("LIST_OF_CONTACTS " + userId);
	ui.stackedWidget->setCurrentIndex(2);



}

void InterfaceWindow::pushOkCreateGroupChat()
{
	QList<QListWidgetItem*> selectedItems = ui.listWidget_2->selectedItems();
	QString idOfSelectedContacts = "";
	for (int i = 0; i < selectedItems.size(); i++)
	{
		idOfSelectedContacts += selectedItems[i]->data(256).toString() + "#";
	}
	idOfSelectedContacts += userId;
	socket->sendToServer("ADD_CHAT " + ui.lineEdit_groupChatName->text() + "#" + idOfSelectedContacts);
	ui.lineEdit_groupChatName->clear();
}


void InterfaceWindow::createContacts(QString str)
{
	ui.listWidget_2->clear();
	QString contactName, id;
	while (!str.isEmpty())
	{
		contactName = str.left(str.indexOf('#'));
		str = str.mid(str.indexOf('#') + 1);
		QListWidgetItem* chatListItem = new QListWidgetItem(contactName);
		chatListItem->setSizeHint(QSize(60, 50));
		id = str.left(str.indexOf('#'));
		if (str.indexOf('#') == -1)
		{
			chatListItem->setData(Qt::UserRole, id);
			ui.listWidget_2->addItem(chatListItem);
			break;
		}
		else {
			str = str.mid(str.indexOf('#') + 1);
			chatListItem->setData(Qt::UserRole, id);
			ui.listWidget_2->addItem(chatListItem);
		}


	}
}



void InterfaceWindow::addChat(QString str)
{
	QString chatName = str.left(str.indexOf('#'));
	str = str.mid(str.indexOf('#') + 1);
	QListWidgetItem* newItem = new QListWidgetItem(chatName);
	newItem->setSizeHint(QSize(60, 50));
	newItem->setData(Qt::UserRole, str);
	ui.listWidget->addItem(newItem);
}



void InterfaceWindow::onGroupChatClicked(QListWidgetItem* item)
{
	emit signalCreateChatWindow(item->data(Qt::UserRole).toString(), item->text(),userId, socket);
	socket->sendToServer("LIST_OF_MESSAGES " + item->data(Qt::UserRole).toString());//передать id чата взятые из item на серве


}


void InterfaceWindow::createChatWindow(QString id, QString name,QString userId, SocketManager* socket)
{if(IC!=nullptr)
	if (IC->isVisible())
		IC->close();
	IC = new InterfaceChat(id, name,userId, socket);
	IC->show();

}



//
//void InterfaceWindow::openAddWidget()
//{
//	ui.stackedWidget->setCurrentIndex(1);
//}
//
//

//
//void InterfaceWindow::createGroupChat(QString name)
//{
//
//	user->createGroupChat(name);
//	emit signalAddChatToForm(name, user->getLastGroupChat());
//	openMainWindow();
//}
//
//void InterfaceWindow::addChatToForm(QString name, GroupChat* chat)
//{
//	QPushButton* newChat = new QPushButton(name);
//	connect(newChat, &QPushButton::clicked, this, &InterfaceWindow::openGroupChat);//ccueea ia ?ao a iiaaee niaaeieou
//	newChat->setProperty("link", QVariant::fromValue(chat));
//	connect(this, &InterfaceWindow::signalInicializateChat, IC, &InterfaceChat::inicializeChat);
//	newChat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
//	newChat->setFixedHeight(chatHeight);
//	
//}
//

//
//void InterfaceWindow::openGroupChat(/*GroupChat* chat*/)
//{
//	if (!IC->isVisible())
//	{
//		IC->show();
//	}
//	QPushButton* button = (QPushButton*)sender();
//	emit signalInicializateChat(button->property("link").value<GroupChat*>(), user->getNickName(), button->text());
//
//}
//
//void InterfaceWindow::openChat(ContactChat& chat)
//{
//	if (!IC->isVisible())
//	{
//		IC->show();
//	}
//}
//void InterfaceWindow::openInicializateContactPage() {
//	ui.stackedWidget->setCurrentIndex(3);
//}
//
//
//void InterfaceWindow::pushCreateContact() {
//	emit signalCreateContact();
//}
//
//void InterfaceWindow::createContact() {
//	
//	QString nick = ui.lineEdit_Nick->text();
//	QString telephoneNum = ui.lineEdit_telephoneNumber->text();
//	User* newUser = new User(nick, telephoneNum);
//	user->addContact(newUser);
//	QPushButton* newContact = new QPushButton(nick);
//	connect(newContact, &QPushButton::clicked, this, &InterfaceWindow::openContactChat);
//	//newContact->setProperty("link", QVariant::fromValue());дописать свойство ссылки на чат с контактом и сделать хранение ссылки на двух участников чата
//	connect(this, &InterfaceWindow::signalInicializateContactChat, IC, &InterfaceChat::inicializeContactChat);
//	newContact->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
//	newContact->setFixedHeight(chatHeight);
//	
//	//создать контакт используя данные созданного экземпляра
//	
//	ui.lineEdit_telephoneNumber->clear();
//	ui.lineEdit_Nick->clear();
//	openMainWindow();
//}
//void InterfaceWindow::openContactChat() {//дописать для создания чата с контактом
//	if (!IC->isVisible())
//	{
//		IC->show();
//	}
//	QPushButton* button = (QPushButton*)sender();
//	//emit signalInicializateContactChat(button->property("link").value<ContactChat*>(), button->text(),);
//	
//}


//только для теста



//
