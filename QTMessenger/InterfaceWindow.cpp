#include "InterfaceWindow.h"

InterfaceWindow::InterfaceWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lineEdit_userName->setEnabled(false);
}

InterfaceWindow::~InterfaceWindow()
{}
void InterfaceWindow::inicialisationUser(QString name, QString password) {
    ui.lineEdit_userName->setText("User: "+name);
    user = new User(name, password);
}