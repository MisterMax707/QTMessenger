#include <QtCore/QCoreApplication>
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    
    //GroupChat* chat = new GroupChat("aaa");

    //// Создаем клиентский сокет для тестирования
    //QTcpSocket clientSocket;
    //clientSocket.connectToHost("127.0.0.1", 2323);

    //// Ждем, пока сокет подключится
    //if (!clientSocket.waitForConnected(3000)) {
    //    qDebug() << "Failed to connect to server";
    //    return -1;
    //}

    //// Отправляем тестовое сообщение
    //QString testMessage = "Hello, World!";
    //QString testNick = "TestUser";
    //int testChatId = 1; // Замените на нужный ID чата

    //QByteArray block;
    //QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_6_2);
    //out << testMessage << testNick << testChatId;

    //clientSocket.write(block);
    //clientSocket.flush();

    //// Ждем, пока данные будут отправлены
    //if (!clientSocket.waitForBytesWritten(3000)) {
    //    qDebug() << "Failed to write data to server";
    //}
    return a.exec();
}
