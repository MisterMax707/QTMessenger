#include "InterfaceLogin.h"
#include "InterfaceWindow.h"
#include "User.h"

InterfaceLogin::InterfaceLogin(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_confirm, &QPushButton::clicked, this, &InterfaceLogin::pushLogConfirm);
	connect(ui.pushButton_registration, &QPushButton::clicked, this, &InterfaceLogin::pushRegistration);
	connect(ui.pushButton_regConfirm, &QPushButton::clicked, this, &InterfaceLogin::pushRegConfirm);
	connect(this, &InterfaceLogin::signalPushLogConfirm, this, &InterfaceLogin::carryOutAuthorization);
	connect(this, &InterfaceLogin::signalPushRegistartion, this, &InterfaceLogin::switchPageStackWidget);
	connect(this, &InterfaceLogin::signalPushRegConfirmWithPage, this, &InterfaceLogin::switchPageStackWidget);
	connect(this, &InterfaceLogin::signalPushRegConfirmWithUser, IW, &InterfaceWindow::initializationUser);
}

InterfaceLogin::~InterfaceLogin()
{}

void InterfaceLogin::pushLogConfirm()
{
	emit signalPushLogConfirm(ui.lineEdit_login->text(), ui.lineEdit_password->text());
}

void InterfaceLogin::carryOutAuthorization(QString loginNick, QString loginPass)
{
	if (ChekingCorrectnessLoginOfData(loginNick, loginPass))
	{
		IW->show();
		this->close();
	}
	else
		QMessageBox::warning(this, "Warning", "Invalid password or login!", QMessageBox::Ok);
}

bool InterfaceLogin::ChekingCorrectnessLoginOfData(QString nick, QString pass)
{
	if ((nick == "") && (pass == "")) return false;
	if ((nick == saveNick) && (pass == savePass)) return true;
	else return false;
}

void InterfaceLogin::switchPageStackWidget(int page)
{
	ui.stackedWidget->setCurrentIndex(page);
}

void InterfaceLogin::pushRegistration()
{
	int pageRegisrtation = 1;
	emit signalPushRegistartion(pageRegisrtation);
}

void InterfaceLogin::pushRegConfirm()
{
	if (ChekingCorrectnessRegistartionOfData())
	{
		int pageLogin = 0;
		User* user = createUserEnteredDataForReg();
		saveNick = ui.lineEdit_regNick->text();
		savePass = ui.lineEdit_regPass->text();
		emit signalPushRegConfirmWithUser(user, ui.lineEdit_regNick->text());
		emit signalPushRegConfirmWithPage(pageLogin);
	}
	else return void();
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

bool InterfaceLogin::ChekingCorrectnessRegistartionOfData()
{
	bool correctnessRegFIO = ChekingCorrectnessRegFIO(ui.lineEdit_regFIO->text());
	bool correctnessRegNick = ChekingCorrectnessRegNick(ui.lineEdit_regNick->text());
	bool correctnessRegPass = ChekingCorrectnessRegPass(ui.lineEdit_regPass->text());
	return correctnessRegFIO * correctnessRegNick * correctnessRegPass;
}

bool InterfaceLogin::ChekingCorrectnessRegFIO(QString fio)
{
	QStringList splitFIO = splitFIOintoComponents(fio);
	QStringList nonEmptyWords = splitFIO.filter(QRegularExpression("\\S"));
	int lenghtFullName = 3;
	if (splitFIO.size() > lenghtFullName)
	{
		QMessageBox::warning(this, "Erorr", "So long full name!", QMessageBox::Ok);
		return false;
	}
	else if (nonEmptyWords.isEmpty())
	{
		QMessageBox::warning(this, "Erorr", "Fill in the name column", QMessageBox::Ok);
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