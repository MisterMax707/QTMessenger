#include <QtCore/QCoreApplication>
#include "Server.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <Windows.h>
#include "qlocale.h"
int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

	QCoreApplication::addLibraryPath("D:/FOR_WORKS/QTMessenger/6.8.0/msvc2022_64/plugins");
	SetConsoleOutputCP(CP_UTF8);

	Server server;
	return a.exec();
}

//---------------------------------ПРИМЕР ПОДКЛЮЧЕНИЯ БАЗЫ ДАННЫХ-------------------------------------------------
//QStringList drivers = QSqlDatabase::drivers();
//// Выводим список драйверов
//qDebug() << "Available drivers:";
//for (const QString& driver : drivers) {
//	qDebug() << driver;
//}

//QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//db.setHostName("localhost");
//db.setPort(5432);
//db.setDatabaseName("postgres");
//db.setUserName("postgres");
//db.setPassword("maxim1106");

//if (!db.open()) {
//	qDebug() << "Failed to connect to database:" << db.lastError().text();
//	return -1;
//}


//QSqlQuery query("SELECT * FROM users");
//while (query.next()) {
//	int id = query.value("id_user").toInt();
//	QString username = query.value("nick_user").toString();
//	QString password = query.value("password_user").toString();
//	QString telephone_number = query.value("telephone_user").toString();

//	qDebug() << "ID:" << id
//		<< "Username:" << username
//		<< "Password:" << password
//		<< "telephone:" << telephone_number;
//}