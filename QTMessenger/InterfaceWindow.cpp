#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(0);
	ui.lineEdit_userName->setEnabled(false);
	verticalLayout = new QVBoxLayout();
	verticalLayout->setAlignment(Qt::AlignTop);
	//verticalLayout->setContentsMargins(;
	widget = new QWidget();
	widget->setLayout(verticalLayout);
	scrollArea = new QScrollArea(ui.page);
	scrollArea->setGeometry(50,120,300,400);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(widget);
	connect(ui.pushButton_add, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);
	connect(this, &InterfaceWindow::signalOpenAddWidget, this, &InterfaceWindow::openAddWidget);
	connect(ui.pushButton_backToMainWindow, &QPushButton::clicked, this, &InterfaceWindow::openMainWindow);
	connect(ui.pushButton_createGroup, &QPushButton::clicked, this, &InterfaceWindow::openEnterName);
	connect(ui.pushButton_okCreateGroup, &QPushButton::clicked, this, &InterfaceWindow::pushOkCreateGroupChat);
	connect(this, &InterfaceWindow::signalpushCreateGroupChat, this, &InterfaceWindow::createGroupChat);
	connect(this, &InterfaceWindow::signalAddChatToForm, this, &InterfaceWindow::addChatToForm);
	connect(ui.pushButton_returnToPageCreateGroupOrContact, &QPushButton::clicked, this, &InterfaceWindow::openAddWidget);
}

InterfaceWindow::~InterfaceWindow()
{}

void InterfaceWindow::initializationUser(User* newUser, QString name) {
	ui.lineEdit_userName->setText("User: " + name);
	user = newUser;
}

void InterfaceWindow::createGroupChat(QString name) {

	user->createGroupChat(name);
	//äîáàâèòü ñîçäàíèå âèäæåòà ïðè êëèêå íà êîòîðûé îòêðûâàåòñÿ îêíî ÷àòà

	emit signalAddChatToForm(name, user->getLastGroupChat());
    openMainWindow();
}


void InterfaceWindow::pushAdd() {
	emit signalOpenAddWidget();
}

void InterfaceWindow::openAddWidget() {
	ui.stackedWidget->setCurrentIndex(1);
}


void InterfaceWindow::openMainWindow() {
	ui.stackedWidget->setCurrentIndex(0);
}

void InterfaceWindow::openEnterName() {
	ui.stackedWidget->setCurrentIndex(2);
}

void InterfaceWindow::pushOkCreateGroupChat() {
	emit signalpushCreateGroupChat(ui.lineEdit_groupChatName->text());
	ui.lineEdit_groupChatName->clear();
}

void InterfaceWindow::addChatToForm(QString name, GroupChat* chat) {
	QPushButton* newChat = new QPushButton(name);
	connect(newChat, &QPushButton::clicked, this, &InterfaceWindow::openGroupChat);//ccûëêà íà ÷àò â ìîäåëè ñîåäèíèòü
	newChat->setProperty("link", QVariant::fromValue(chat));
	connect(this, &InterfaceWindow::signalInicializateChat, IC, &InterfaceChat::inicializeChat);
	newChat->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred));
	newChat->setFixedHeight(chatHeight);
	verticalLayout->addWidget(newChat);
	
}


void InterfaceWindow::openGroupChat(/*GroupChat* chat*/) {
	if (!IC->isVisible())
	{
		IC->show();
	}
	QPushButton* button = (QPushButton*)sender();
	emit signalInicializateChat(button->property("link").value<GroupChat*>(), user->getNickName(), button->text());
	
}

void InterfaceWindow::openChat(ContactChat& chat) {
	if (!IC->isVisible())
	{
		IC->show();
	}
}