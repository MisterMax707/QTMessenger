#include "InterfaceChat.h"

InterfaceChat::InterfaceChat(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.lineEdit_nameChatOrContact->setEnabled(false);
}

InterfaceChat::~InterfaceChat()
{}

void InterfaceChat::inicializeChat(GroupChat* chat, QString name) {
	ui.lineEdit_nameChatOrContact->setText(name);
	
	//ui.listView_chat//присоединить список сообщений к лист вью чат

}