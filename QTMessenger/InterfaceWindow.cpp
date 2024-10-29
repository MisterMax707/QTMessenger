#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(0);
	ui.lineEdit_userName->setEnabled(false);
	connect(ui.pushButton_add, &QPushButton::clicked, this, &InterfaceWindow::pushAdd);
	connect(this, &InterfaceWindow::signalOpenAddWidget, this, &InterfaceWindow::openAddWidget);
	connect(ui.pushButton_backToMainWindow, &QPushButton::clicked, this, &InterfaceWindow::openMainWindow);
	connect(ui.pushButton_createGroup, &QPushButton::clicked, this, &InterfaceWindow::openEnterName);
	connect(ui.pushButton_okCreateGroup, &QPushButton::clicked, this, &InterfaceWindow::pushOkCreateGroup);
	connect(this, &InterfaceWindow::signalpushCreateGroup, this, &InterfaceWindow::createGroup);
}

InterfaceWindow::~InterfaceWindow()
{}
void InterfaceWindow::inicialisationUser(QString name, QString password) {
	ui.lineEdit_userName->setText("User: " + name);
	user = new User(name, password);
}

void InterfaceWindow::createGroup(QString name) {

	user->createGroupChat(name);
	QPushButton* GroupChat=new QPushButton(name);
	//добавить создание виджета при клике на который открывается окно чата


	emit openMainWindow();
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

void InterfaceWindow::pushOkCreateGroup() {
	emit signalpushCreateGroup(ui.pushButton_okCreateGroup->text());
}