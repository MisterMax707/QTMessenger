#include "InterfaceWindow.h"
#include "InterfaceLogin.h"
#include "InterfaceChat.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceLogin IF;
    InterfaceWindow IW;
    InterfaceChat IC;
    IC.show();
    IW.show();
    IF.show();
    return a.exec();
}