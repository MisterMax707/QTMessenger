#pragma once

#include <QMainWindow>
#include "ui_InterfaceChat.h"

class InterfaceChat : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceChat(QWidget *parent = nullptr);
	~InterfaceChat();

private:
	Ui::InterfaceChatClass ui;
};
