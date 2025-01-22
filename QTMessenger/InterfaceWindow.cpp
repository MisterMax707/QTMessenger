#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(0);
	ui.lineEdit_userName->setEnabled(false);
	
	







	/*connect(ui.pushButton_add, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);
	connect(ui.pushButton_createGroup, &QPushButton::clicked, this, &InterfaceWindow::openEnterNameGroupChat);
	connect(ui.pushButton_okCreateGroup, &QPushButton::clicked, this, &InterfaceWindow::pushOkCreateGroupChat);
	connect(this, &InterfaceWindow::signalOpenAddWidget, this, &InterfaceWindow::openAddWidget);*/
	//connect(this, &InterfaceWindow::signalpushCreateGroupChat, this, &InterfaceWindow::createGroupChat);
	//connect(this, &InterfaceWindow::signalAddChatToForm, this, &InterfaceWindow::addChatToForm);
	/*connect(ui.pushButton_backToMainWindow, &QPushButton::clicked, this, &InterfaceWindow::openMainWindow);
	connect(ui.pushButton_returnToPageCreateContact, &QPushButton::clicked, this, &InterfaceWindow::openAddWidget);
	connect(ui.pushButton_returnToPageCreateGroupOrContact, &QPushButton::clicked, this, &InterfaceWindow::openAddWidget);
	connect(ui.pushButton_newContact, &QPushButton::clicked, this, &InterfaceWindow::openInicializateContactPage);
	connect(ui.pushButton_CreateContact, &QPushButton::clicked, this, &InterfaceWindow::pushCreateContact);
	connect(this, &InterfaceWindow::signalCreateContact, this, &InterfaceWindow::createContact);*/
	
}

InterfaceWindow::~InterfaceWindow()
{}


void InterfaceWindow::setUserId(QString idOfUser) {
	ui.lineEdit_userName->setText("UsersId: " + idOfUser);
}

void InterfaceWindow::setSocket(SocketManager* socket)
{
	this->socket = socket;
}



























//void InterfaceWindow::pushAdd()
//{
//	emit signalOpenAddWidget();
//}
//
//void InterfaceWindow::openAddWidget()
//{
//	ui.stackedWidget->setCurrentIndex(1);
//}
//
//void InterfaceWindow::openEnterNameGroupChat()
//{
//	ui.stackedWidget->setCurrentIndex(2);
//}
//
//void InterfaceWindow::pushOkCreateGroupChat()
//{
//	emit signalpushCreateGroupChat(ui.lineEdit_groupChatName->text());
//	ui.lineEdit_groupChatName->clear();
//}
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
//	connect(newChat, &QPushButton::clicked, this, &InterfaceWindow::openGroupChat);//ccûëêà íà ÷àò â ìîäåëè ñîåäèíèòü
//	newChat->setProperty("link", QVariant::fromValue(chat));
//	connect(this, &InterfaceWindow::signalInicializateChat, IC, &InterfaceChat::inicializeChat);
//	newChat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
//	newChat->setFixedHeight(chatHeight);
//	
//}
//
//void InterfaceWindow::openMainWindow()
//{
//	ui.stackedWidget->setCurrentIndex(0);
//}
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