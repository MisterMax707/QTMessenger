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
	bool ChekingCorrectnessLoginOfData(QString login, QString pass);
	bool ChekingCorrectnessRegistartionOfData();
	bool ChekingCorrectnessRegTel(QString fio);
	bool ChekingCorrectnessRegNick(QString nick);
	bool ChekingCorrectnessRegPass(QString pass);

signals:
	void signalPushLogConfirm(QString loginNick, QString loginPass);
	void signalPushRegistartion(int pageRegistration);
	void signalPushRegConfirmWithPage(int pageLogin);
	void signalPushRegConfirmWithUser(User*, QString);

private slots:
	void pushRegistration();
	void pushLogConfirm();
	void pushRegConfirm();
	void carryOutAuthorization(QString loginNick, QString loginPass);
	void switchPageStackWidget(int page);
};
