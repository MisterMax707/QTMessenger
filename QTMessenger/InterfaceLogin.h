#pragma once

#include <QMainWindow>
#include "ui_InterfaceLogin.h"

class InterfaceLogin : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceLogin(QWidget *parent = nullptr);
	~InterfaceLogin();

private:
	Ui::InterfaceLoginClass ui;
};
