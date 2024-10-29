#include "InterfaceLogin.h"
#include "InterfaceWindow.h"
#include "User.h"

InterfaceLogin::InterfaceLogin(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_confirm, &QPushButton::clicked, this, &InterfaceLogin::pushConfirm);
	connect(ui.pushButton_registration, &QPushButton::clicked, this, &InterfaceLogin::pushRegistration);
	connect(ui.pushButton_regConfirm, &QPushButton::clicked, this, &InterfaceLogin::pushRegConfirm);
	connect(this, &InterfaceLogin::signalPushRegConfirm, IW, &InterfaceWindow::initializationUser);
}

InterfaceLogin::~InterfaceLogin()
{}

void InterfaceLogin::pushConfirm() 
{
	QString lineNick = ui.lineEdit_login->text();
	QString linePass = ui.lineEdit_password->text();
	if (ChekingCorrectnessOfData(lineNick, linePass))
	{
		IW->show();
		this->close();
	}
	else
		QMessageBox::warning(this, "Warning", "Invalid password or login!", QMessageBox::Ok);

}

bool InterfaceLogin::ChekingCorrectnessOfData(QString nick, QString pass)
{
	if ((nick == saveNick) && pass == savePass) return true;
	else return false;
}

void InterfaceLogin::pushRegistration()
{
	ui.stackedWidget->setCurrentIndex(1);
}

User* InterfaceLogin::createUserEnteredDataForReg()
{
	QString fio = ui.lineEdit_regFIO->text();
	QStringList splitFIO = splitFIOintoComponents(fio);
	FullName name(splitFIO[0], splitFIO[1], splitFIO[2]);
	QString nick = ui.lineEdit_regNick->text();
	QString pass = ui.lineEdit_regPass->text();
	User* user = new User(name, nick, pass);
	
	return user;
}

void InterfaceLogin::pushRegConfirm() // тут бы бд
{
	User* user = createUserEnteredDataForReg();
	saveNick = ui.lineEdit_regNick->text();
	savePass = ui.lineEdit_regPass->text();
	emit signalPushRegConfirm(user, ui.lineEdit_regNick->text());
	ui.stackedWidget->setCurrentIndex(0); 
}