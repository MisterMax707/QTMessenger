#pragma once

#include <QMainWindow>
#include "ui_InterfaceLogin.h"
#include "InterfaceWindow.h"
class InterfaceLogin : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceLogin(QWidget *parent = nullptr);
	~InterfaceLogin();

private:
	Ui::InterfaceLoginClass ui;
	InterfaceWindow* IW = new InterfaceWindow();
signals:
	void signalPushConfirm(QString,QString);
private slots:
	void pushConfirm();
	//void createInterfaceWindow();
};
