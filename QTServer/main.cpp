#include <QtCore/QCoreApplication>
#include "Server.h"

#include "qlocale.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    // Установка кодека для консольного вывода
   // QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    
    Server server ;
    return a.exec();
}
