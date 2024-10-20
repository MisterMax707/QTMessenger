#include "InterfaceWindow.h"
#include "InterfaceLogin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceLogin IF;
    IF.show();
    return a.exec();
}