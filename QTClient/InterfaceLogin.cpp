#include "InterfaceLogin.h"

InterfaceLogin::InterfaceLogin(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_confirm, &QPushButton::clicked, this, &InterfaceLogin::pushLogConfirm);
	connect(ui.pushButton_registration, &QPushButton::clicked, this, &InterfaceLogin::pushRegistration);
	connect(ui.pushButton_regConfirm, &QPushButton::clicked, this, &InterfaceLogin::pushRegConfirm);

	connect(IW, &InterfaceWindow::destroyed, this, &InterfaceLogin::deleteMainWindow);
	//connect(this, &InterfaceLogin::signalPushLogConfirm, this, &InterfaceLogin::carryOutAuthorization);
	//connect(this, &InterfaceLogin::signalPushRegistartion, this, &InterfaceLogin::switchPageStackWidget);
	//connect(this, &InterfaceLogin::signalPushRegConfirmWithPage, this, &InterfaceLogin::switchPageStackWidget);
	//connect(this, &InterfaceLogin::signalPushRegConfirmWithUser, IW, &InterfaceWindow::initializationUser);
}

InterfaceLogin::~InterfaceLogin()
{}

void InterfaceLogin::pushLogConfirm()
{
	socket = new SocketManager();
	connect(socket, &SocketManager::signalCreateMainWindow, this, &InterfaceLogin::createMainWindow);
	connect(socket, &SocketManager::signalErrorNoSuchUser, this, &InterfaceLogin::writeErrorNoSuchUser);
	QString login = ui.lineEdit_login->text();
	QString pass = ui.lineEdit_password->text();
	InformationWord word = space::combine(login, pass);
	socket->sendToServer(cod::CodeWord::LOGIN, word, std::nullopt);
}
void InterfaceLogin::pushRegistration()
{
	ui.stackedWidget->setCurrentIndex(1);
}

void InterfaceLogin::pushRegConfirm()
{
	if (ChekingCorrectnessRegistartionOfData())
	{
		socket = new SocketManager();
		connect(socket, &SocketManager::signalRegistrationSuccess, this, &InterfaceLogin::registrationSuccess);
		InformationWord word = ui.lineEdit_regNick->text() + ui.lineEdit_regPass->text() + ui.lineEdit_regTel->text();
		socket->sendToServer(cod::CodeWord::REGISTRATION, word, std::nullopt);
		ui.stackedWidget->setCurrentIndex(0);
		/*int pageLogin = 0;
		User* user = createUserEnteredDataForReg();
		saveNick = ui.lineEdit_regNick->text();
		savePass = ui.lineEdit_regPass->text();
		emit signalPushRegConfirmWithUser(user, ui.lineEdit_regNick->text());
		emit signalPushRegConfirmWithPage(pageLogin);*/
	}
	else return void();
}

void InterfaceLogin::createMainWindow(QString idOfUser, SocketManager* socket) 
{
	IW = new InterfaceWindow(idOfUser, socket);
	IW->show();
	this->close();//закрытие окна входа/регистрации
}

void InterfaceLogin::writeErrorNoSuchUser() 
{
	QMessageBox::warning(this, "Error!", "NO SUCH USER!", QMessageBox::Ok);
}


void InterfaceLogin::registrationSuccess() 
{
	QMessageBox::warning(this, "MESSAGE", "REGISTRATION WAS SUCCSESFULL!", QMessageBox::Ok);
}

void InterfaceLogin::deleteMainWindow()
{
	delete IW;
}



















//void InterfaceLogin::carryOutAuthorization(QString loginNick, QString loginPass)
//{
//	if (ChekingCorrectnessLoginOfData(loginNick, loginPass))
//	{
//		IW->show();
//		this->close();
//	}
//	else
//		QMessageBox::warning(this, "Warning", "Invalid password or login!", QMessageBox::Ok);
//}

//bool InterfaceLogin::ChekingCorrectnessLoginOfData(QString nick, QString pass)
//{
//	if ((nick == "") && (pass == "")) return false;
//	if ((nick == saveNick) && (pass == savePass)) return true;
//	else return false;
//}

//void InterfaceLogin::switchPageStackWidget(int page)
//{
//	ui.stackedWidget->setCurrentIndex(page);
//}





//User* InterfaceLogin::createUserEnteredDataForReg()
//{
//	QString tel = ui.lineEdit_regTel->text();
//	QString nick = ui.lineEdit_regNick->text();
//	QString pass = ui.lineEdit_regPass->text();
//	User* user = new User( nick, pass,tel);
//
//	return user;
//}

bool InterfaceLogin::ChekingCorrectnessRegistartionOfData()
{
	bool correctnessRegTel = ChekingCorrectnessRegTel(ui.lineEdit_regTel->text());
	bool correctnessRegNick = ChekingCorrectnessRegNick(ui.lineEdit_regNick->text());
	bool correctnessRegPass = ChekingCorrectnessRegPass(ui.lineEdit_regPass->text());
	return  correctnessRegNick * correctnessRegPass;
}

bool InterfaceLogin::ChekingCorrectnessRegTel(QString tel)
{
	if (tel== "")
	{
		QMessageBox::warning(this, "Erorr", "Fill in the telephone column", QMessageBox::Ok);
		return false;
	}
	else if (tel.contains(" "))
	{
		QMessageBox::warning(this, "Erorr", "The telephone must have one word", QMessageBox::Ok);
		return false;
	}
	else return true;
}

bool InterfaceLogin::ChekingCorrectnessRegNick(QString nick)
{
	if (nick == "")
	{
		QMessageBox::warning(this, "Erorr", "Fill in the nick column", QMessageBox::Ok);
		return false;
	}
	else if (nick.contains(" "))
	{
		QMessageBox::warning(this, "Erorr", "The nick must have one word", QMessageBox::Ok);
		return false;
	}
	else return true;
}

bool InterfaceLogin::ChekingCorrectnessRegPass(QString pass)
{
	if (pass == "")
	{
		QMessageBox::warning(this, "Erorr", "Fill in the password column", QMessageBox::Ok);
		return false;
	}
	else if (pass.contains(" "))
	{
		QMessageBox::warning(this, "Erorr", "The password must have one word", QMessageBox::Ok);
		return false;
	}
	else return true;
}
