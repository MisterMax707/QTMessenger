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
	QString saveNick, savePass;
	User* createUserEnteredDataForReg();
	bool ChekingCorrectnessOfData(QString, QString);

signals:
	void signalPushRegConfirm(User*, QString);

private slots:
	void pushConfirm();
	void pushRegistration();
	void pushRegConfirm();
	//void createInterfaceWindow();
};
