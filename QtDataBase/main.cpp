#include <QCoreApplication>

#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::addLibraryPath("D:/FOR_WORKS/QTMessenger/6.8.0/msvc2022_64/plugins");


    //QSqlQuery query("SELECT * FROM users");
    //while (query.next()) {
    //    int id = query.value("id_user").toInt();
    //    QString username = query.value("nick_user").toString();
    //    QString password = query.value("password_user").toString();
    //    QString telephone_number = query.value("telephone_user").toString();

    //    qDebug() << "ID:" << id
    //        << "Username:" << username
    //        << "Password:" << password
    //        << "telephone:" << telephone_number;
    //}

    return a.exec();
}