#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QStringList drivers = QSqlDatabase::drivers();

    // Выводим список драйверов
    qDebug() << "Available drivers:";
    for (const QString& driver : drivers) {
        qDebug() << driver;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("test");
    db.setUserName("postgres");
    db.setPassword("maxim1106");

    if (db.open()) qDebug() << "cool";

    return a.exec();
}