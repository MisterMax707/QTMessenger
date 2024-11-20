#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QWidget* parent, User* newUser, QString name)
	: QMainWindow(parent), user(newUser)
{
	ui.setupUi(this);

	ui.lineEdit_userName->setText("User: " + name);
	ui.stackedWidget->setCurrentIndex(0);
	ui.lineEdit_userName->setEnabled(false);

	connect(ui.pushButton_add, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);
	connect(ui.pushButton_createGroup, &QPushButton::clicked, this, &InterfaceWindow::openEnterNameGroupChat);
	connect(ui.pushButton_okCreateGroup, &QPushButton::clicked, this, &InterfaceWindow::pushOkCreateGroupChat);
	connect(this, &InterfaceWindow::signalOpenAddWidget, this, &InterfaceWindow::openAddWidget);
	connect(this, &InterfaceWindow::signalpushCreateGroupChat, this, &InterfaceWindow::createGroupChat);
	connect(this, &InterfaceWindow::signalAddChatToForm, this, &InterfaceWindow::addChatToForm);
	connect(ui.pushButton_backToMainWindow, &QPushButton::clicked, this, &InterfaceWindow::openMainWindow);
	connect(ui.pushButton_returnToPageCreateContact, &QPushButton::clicked, this, &InterfaceWindow::openAddWidget);
	connect(ui.pushButton_returnToPageCreateGroupOrContact, &QPushButton::clicked, this, &InterfaceWindow::openAddWidget);
	connect(ui.pushButton_newContact, &QPushButton::clicked, this, &InterfaceWindow::openInicializateContactPage);
	connect(ui.pushButton_CreateContact, &QPushButton::clicked, this, &InterfaceWindow::pushCreateContact);
	connect(this, &InterfaceWindow::signalCreateContact, this, &InterfaceWindow::createContact);

	connect(ui.listWidget_formChats, &QListWidget::itemClicked, this, &InterfaceWindow::openGroupChat);
	connect(this, &InterfaceWindow::signalAddContactToForm, this, &InterfaceWindow::AddContactToForm);
	
}

InterfaceWindow::~InterfaceWindow()
{}

void InterfaceWindow::pushAdd()
{
	emit signalOpenAddWidget();
}

void InterfaceWindow::openAddWidget()
{
	ui.stackedWidget->setCurrentIndex(1);
}

void InterfaceWindow::openEnterNameGroupChat()
{
	ui.stackedWidget->setCurrentIndex(2);
}

void InterfaceWindow::pushOkCreateGroupChat()
{
	emit signalpushCreateGroupChat(ui.lineEdit_groupChatName->text());
	ui.lineEdit_groupChatName->clear();
}

void InterfaceWindow::createGroupChat(QString name)
{

	user->createGroupChat(name);
	emit signalAddChatToForm(name, user->getLastGroupChat());
	openMainWindow();
}

void InterfaceWindow::addChatToForm(QString name, GroupChat* chat)
{
	//QPushButton* newChat = new QPushButton(name);
	//connect(newChat, &QPushButton::clicked, this, &InterfaceWindow::openGroupChat);//ccûëêà íà ÷àò â ìîäåëè ñîåäèíèòü
	//newChat->setProperty("link", QVariant::fromValue(chat));
	//connect(this, &InterfaceWindow::signalInicializateChat, IC, &InterfaceChat::inicializeChat);
	//newChat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
	//newChat->setFixedHeight(chatHeight);
	//ui.listWidget_formChats->addItem(newChat);
	//verticalLayout->addWidget(newChat);

	QListWidgetItem* newChatItem = new QListWidgetItem(name);
	//QFont messageFont = newChatItem->font();
	//messageFont.setPointSize(14);
	//newChatItem->setFont(messageFont);
	newChatItem->setData(Qt::UserRole, QVariant::fromValue(chat));
	ui.listWidget_formChats->addItem(newChatItem);
}

void InterfaceWindow::openMainWindow()
{
	ui.stackedWidget->setCurrentIndex(0);
}

void InterfaceWindow::openGroupChat(/*GroupChat* chat*/)
{
	//if (!IC->isVisible())
	//{
	//	IC->show();
	//}
	//QPushButton* button = (QPushButton*)sender();
	//emit signalInicializateChat(button->property("link").value<GroupChat*>(), user->getNickName(), button->text());
	if (IC != nullptr)
		IC->close();
	if (ui.listWidget_formChats->currentItem())
	{
		QListWidgetItem* currentChatItem = ui.listWidget_formChats->currentItem();
		GroupChat* linkToChat = currentChatItem->data(Qt::UserRole).value<GroupChat*>();
		IC = new InterfaceChat(nullptr, linkToChat, user->getNickName(), currentChatItem->text());
		IC->show();
	}
}

void InterfaceWindow::openChat(ContactChat& chat)
{
	if (!IC->isVisible())
	{
		IC->show();
	}
}
void InterfaceWindow::openInicializateContactPage() {
	ui.stackedWidget->setCurrentIndex(3);
}


void InterfaceWindow::pushCreateContact() {
	emit signalCreateContact();
}

void InterfaceWindow::createContact() {
	
	QString nick = ui.lineEdit_Nick->text();
	QString telephoneNum = ui.lineEdit_telephoneNumber->text();
	User* newContact = new User(nick, telephoneNum);
	user->addContact(newContact);
	emit signalAddContactToForm(nick, user->getLastContact());

	//QPushButton* newContact = new QPushButton(nick);
	//connect(newContact, &QPushButton::clicked, this, &InterfaceWindow::openContactChat);
	//newContact->setProperty("link", QVariant::fromValue());дописать свойство ссылки на чат с контактом и сделать хранение ссылки на двух участников чата
	//connect(this, &InterfaceWindow::signalInicializateContactChat, IC, &InterfaceChat::inicializeContactChat);
	//newContact->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
	//newContact->setFixedHeight(chatHeight);
	//verticalLayoutPage2->addWidget(newContact);
	
	ui.lineEdit_telephoneNumber->clear();
	ui.lineEdit_Nick->clear();
	openMainWindow();
}

void InterfaceWindow::AddContactToForm(QString nick, Contact* contact)
{
	QListWidgetItem* newContactItem = new QListWidgetItem(nick);
	//newContactItem->setData(Qt::UserRole, QVariant::fromValue()); дописать свойство ссылки на чат с контактом и сделать хранение ссылки на двух участников чата
	ui.listWidget_formContact->addItem(newContactItem);
	//создать контакт используя данные созданного экземпляра
}

void InterfaceWindow::openContactChat() {//дописать для создания чата с контактом
	if (!IC->isVisible())
	{
		IC->show();
	}
	QPushButton* button = (QPushButton*)sender();
	//emit signalInicializateContactChat(button->property("link").value<ContactChat*>(), button->text(),);
	
}