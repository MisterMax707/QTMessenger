#pragma once
#include <QMainWindow>
#include "ui_InterfaceLogin.h"
#include "InterfaceWindow.h"
#include "SocketManager.h"


class InterfaceLogin : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceLogin(QWidget* parent = nullptr);
	~InterfaceLogin();

private:

	Ui::InterfaceLoginClass ui;
	InterfaceWindow* IW;
	//User* createUserEnteredDataForReg();
	/*bool ChekingCorrectnessLoginOfData(QString login, QString pass);
	bool ChekingCorrectnessRegistartionOfData();
	bool ChekingCorrectnessRegTel(QString fio);
	bool ChekingCorrectnessRegNick(QString nick);
	bool ChekingCorrectnessRegPass(QString pass);*/
	SocketManager* socket;


signals:
	/*void signalPushLogConfirm(QString loginNick, QString loginPass);
	void signalPushRegistartion(int pageRegistration);
	void signalPushRegConfirmWithPage(int pageLogin);*/
	//void signalPushRegConfirmWithUser(User*, QString);
	void signalSetUserIdOnMainWindow(QString idOfUser);
	void signalSetSocketManagerOnMainWindow(SocketManager* socket);

private slots:
	//void pushRegistration();
	void pushLogConfirm();
	//void pushRegConfirm();
	void createMainWindow(QString str, SocketManager* socket);
	void writeErrorNoSuchUser();
	
	void deleteMainWindow();
	//void carryOutAuthorization(QString loginNick, QString loginPass);
	//void switchPageStackWidget(int page);
	//void displayMessage();
};
