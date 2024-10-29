#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lineEdit_userName->setEnabled(false);
}

InterfaceWindow::~InterfaceWindow()
{}
void InterfaceWindow::initializationUser(User* newUser, QString name) {
    ui.lineEdit_userName->setText("User: " + name);
    user = newUser;
}