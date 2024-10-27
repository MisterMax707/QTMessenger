#include "InterfaceLogin.h"
#include "InterfaceWindow.h"
#include "User.h"
#include <iostream>
InterfaceLogin::InterfaceLogin(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_confirm, &QPushButton::clicked, this, &InterfaceLogin::pushConfirm);
	connect(this, &InterfaceLogin::signalPushConfirm, IW, &InterfaceWindow::inicialisationUser);
}

InterfaceLogin::~InterfaceLogin()
{}

void InterfaceLogin::pushConfirm() {
	emit signalPushConfirm(ui.lineEdit_login->text(),ui.lineEdit_password->text());
	IW->show();
	emit close();
	//emit();//создать сигнал что нажата кнопка
}