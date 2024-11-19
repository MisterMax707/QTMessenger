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

	verticalLayoutPage2 = new QVBoxLayout();
	verticalLayoutPage2->setAlignment(Qt::AlignTop);
	widgetPage2 = new QWidget();
	widgetPage2->setLayout(verticalLayoutPage2);
	scrollAreaPage2 = new QScrollArea(ui.page_2);
	scrollAreaPage2->setGeometry(20, 120, 350, 450);
	scrollAreaPage2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollAreaPage2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollAreaPage2->setWidgetResizable(true);
	scrollAreaPage2->setWidget(widgetPage2);
	//поменять чисто для теста

	socket = new QTcpSocket(this);
	connect(socket, &QTcpSocket::readyRead, this, &InterfaceWindow::readyRead);
	connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
	
	//

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
	
}

InterfaceWindow::~InterfaceWindow()
{}

void InterfaceWindow::initializationUser(User* newUser, QString name)
{
	ui.lineEdit_userName->setText("User: " + name);
	user = newUser;
	user->createGroupChat("***ПЕРВЫЙ ТЕСТОВЫЙ ЧАТ***");
	QPushButton* newChat = new QPushButton("***ПЕРВЫЙ ТЕСТОВЫЙ ЧАТ***");
	connect(newChat, &QPushButton::clicked, this, &InterfaceWindow::openGroupChat);
	connect(newChat, &QPushButton::clicked, this, &InterfaceWindow::connectToServer);
	newChat->setProperty("link", QVariant::fromValue(user->getLastGroupChat()));
	connect(this, &InterfaceWindow::signalInicializateChat, IC, &InterfaceChat::inicializeChat);
	newChat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
	newChat->setFixedHeight(chatHeight);
	verticalLayout->addWidget(newChat);
	connect(IC, &InterfaceChat::newsignaladdmes, this, &InterfaceWindow::sendToServer);
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
	
	QString nick = ui.lineEdit_Nick->text();
	QString telephoneNum = ui.lineEdit_telephoneNumber->text();
	User* newUser = new User(nick, telephoneNum);
	user->addContact(newUser);
	QPushButton* newContact = new QPushButton(nick);
	connect(newContact, &QPushButton::clicked, this, &InterfaceWindow::openContactChat);
	//newContact->setProperty("link", QVariant::fromValue());дописать свойство ссылки на чат с контактом и сделать хранение ссылки на двух участников чата
	connect(this, &InterfaceWindow::signalInicializateContactChat, IC, &InterfaceChat::inicializeContactChat);
	newContact->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred));
	newContact->setFixedHeight(chatHeight);
	verticalLayoutPage2->addWidget(newContact);
	//создать контакт используя данные созданного экземпляра
	
	ui.lineEdit_telephoneNumber->clear();
	ui.lineEdit_Nick->clear();
	openMainWindow();
}
void InterfaceWindow::openContactChat() {//дописать для создания чата с контактом
	if (!IC->isVisible())
	{
		IC->show();
	}
	QPushButton* button = (QPushButton*)sender();
	//emit signalInicializateContactChat(button->property("link").value<ContactChat*>(), button->text(),);
	
}


//только для теста
void InterfaceWindow::connectToServer()
{
	socket->connectToHost("198.168.135.240",2323);
}
void InterfaceWindow::sendToServer(QString str)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_2);
	out << str;
	socket->write(Data);

}
void InterfaceWindow::readyRead()
{
	socket = (QTcpSocket*)sender();
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_6_2);
	if (in.status() == QDataStream::Ok)
	{
		QString str;
		in >> str;
		IC->sendMessage(str, "алеша");
		
	}
	else
	{
		IC->sendMessage("read error", "ошибка+ошибка");

	}
}



//