#pragma once

#include <QMainWindow>
#include "ui_InterfaceChat.h"
#include "GroupChat.h"
class InterfaceChat : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceChat(QWidget *parent = nullptr);
	~InterfaceChat();

private:
	Ui::InterfaceChatClass ui;
	//ContactChat* ñhat;
public slots:
	void inicializeChat(GroupChat* chat,QString name);
};
