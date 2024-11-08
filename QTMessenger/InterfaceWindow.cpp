#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(0);
	ui.lineEdit_userName->setEnabled(false);
	verticalLayout = new QVBoxLayout();
	verticalLayout->setAlignment(Qt::AlignTop);

	widget = new QWidget();
	widget->setLayout(verticalLayout);
	scrollArea = new QScrollArea(ui.page);
	scrollArea->setGeometry(50, 120, 300, 400);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(widget);
	
	verticalLayoutPage5 = new QVBoxLayout();
	verticalLayoutPage5->setAlignment(Qt::AlignTop);
	widgetPage5 = new QWidget();
	widgetPage5->setLayout(verticalLayoutPage5);
	scrollAreaPage5 = new QScrollArea(ui.page_5);
	scrollAreaPage5->setGeometry(20, 120, 350, 450);
	scrollAreaPage5->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollAreaPage5->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollAreaPage5->setWidgetResizable(true);
	scrollAreaPage5->setWidget(widgetPage5);

	connect(ui.pushButton_add, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);
	connect(ui.pushButton_createGroup, &QPushButton::clicked, this, &InterfaceWindow::openEnterNameGroupChat);
	connect(ui.pushButton_okCreateGroup, &QPushButton::clicked, this, &InterfaceWindow::pushOkCreateGroupChat);
	connect(this, &InterfaceWindow::signalOpenAddWidget, this, &InterfaceWindow::openAddWidget);
	connect(this, &InterfaceWindow::signalpushCreateGroupChat, this, &InterfaceWindow::createGroupChat);
	connect(this, &InterfaceWindow::signalAddChatToForm, this, &InterfaceWindow::addChatToForm);
	connect(ui.pushButton_backToMainWindow, &QPushButton::clicked, this, &InterfaceWindow::openMainWindow);
	connect(ui.pushButton_backToMainWindow_2, &QPushButton::clicked, this, &InterfaceWindow::openMainWindow);
	connect(ui.pushButton_returnToPageCreateGroupOrContact, &QPushButton::clicked, this, &InterfaceWindow::openAddWidget);
	connect(ui.pushButton_newContact, &QPushButton::clicked, this, &InterfaceWindow::openInicializateContactPage);
	connect(ui.pushButton_CreateContact, &QPushButton::clicked, this, &InterfaceWindow::pushCreateContact);
	connect(this, &InterfaceWindow::signalCreateContact, this, &InterfaceWindow::createContact);
	connect(ui.pushButton_writeMessage, &QPushButton::clicked, this, &InterfaceWindow::openContactsList);
}

InterfaceWindow::~InterfaceWindow()
{}

void InterfaceWindow::initializationUser(User* newUser, QString name)
{
	ui.lineEdit_userName->setText("User: " + name);
	user = newUser;
}

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
	QPushButton* newChat = new QPushButton(name);
	connect(newChat, &QPushButton::clicked, this, &InterfaceWindow::openGroupChat);//ccûëêà íà ÷àò â ìîäåëè ñîåäèíèòü
	newChat->setProperty("link", QVariant::fromValue(chat));
	connect(this, &InterfaceWindow::signalInicializateChat, IC, &InterfaceChat::inicializeChat);
	newChat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
	newChat->setFixedHeight(chatHeight);
	verticalLayout->addWidget(newChat);
}

void InterfaceWindow::openMainWindow()
{
	ui.stackedWidget->setCurrentIndex(0);
}

void InterfaceWindow::openGroupChat(/*GroupChat* chat*/)
{
	if (!IC->isVisible())
	{
		IC->show();
	}
	QPushButton* button = (QPushButton*)sender();
	emit signalInicializateChat(button->property("link").value<GroupChat*>(), user->getNickName(), button->text());

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
	QString fio = ui.lineEdit_FIO->text();
	QStringList splitFIO = splitFIOintoComponents(fio);

	FullName name(splitFIO[0], splitFIO[1], splitFIO[2]);
	QString nick = ui.lineEdit_Nick->text();
	int telephoneNum = ui.lineEdit_telephoneNumber->text().toInt();
	// new User(name, nick, telephoneNum);
	//создать контакт используя данные созданного экземпляра
	ui.lineEdit_FIO->clear();
	ui.lineEdit_telephoneNumber->clear();
	ui.lineEdit_Nick->clear();
	openMainWindow();
}
void InterfaceWindow::openContactsList() {
	ui.stackedWidget->setCurrentIndex(4);
	QPushButton* newChat = new QPushButton("Здесь будет список контактов");
	newChat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
	newChat->setFixedHeight(chatHeight);
	verticalLayoutPage5->addWidget(newChat);
}