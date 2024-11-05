#include "InterfaceWindow.h"
#include "InterfaceLogin.h"
#include "InterfaceChat.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceLogin IF;
    IF.show();
    /*InterfaceChat IC;
    IC.show();
   */
   
    return a.exec();
}