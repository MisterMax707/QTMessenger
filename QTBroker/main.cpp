#include <QtCore/QCoreApplication>
#include "Broker.h"
#include "qthread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Broker broker;
    return a.exec();
}
