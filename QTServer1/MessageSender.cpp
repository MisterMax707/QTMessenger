#include "MessageSender.h"

MessageSender::MessageSender(QObject *parent, int id_chat)
	: QObject(parent)
{
    User user;
    chat = user.getAnIDGroupChat(id_chat);

    workerThread = new QThread;
    moveToThread(workerThread);
    connect(this, &MessageSender::signalSendMessage, this, &MessageSender::sendMessage, Qt::QueuedConnection);
    connect(workerThread, &QThread::finished, this, &MessageSender::onThreadFinished);

    workerThread->start();
}

MessageSender::~MessageSender()
{
    workerThread->quit();
    workerThread->wait();
    delete workerThread;
}

void MessageSender::onThreadFinished()
{
    qDebug() << "Worker thread has finished.";
    delete this;
}

void MessageSender::addMessageToQueueForSending(QString contentMessage, QString nickSender)
{
    QMutexLocker locker(&mutex);
    queueForSendingMessage.enqueue(qMakePair(contentMessage, nickSender));
    if (!(activeOperation))
    {
        activeOperation = true;
        emit signalSendMessage();
    }
}

void MessageSender::sendMessage()
{
    QMutexLocker locker(&mutex);
    if (!queueForSendingMessage.isEmpty())
    {
        auto messagePair = queueForSendingMessage.dequeue();
        QString contentMessage = messagePair.first;
        QString nickSender = messagePair.second;

        Message* msg = new Message(contentMessage, nickSender);
        //chat->addMessageToChatList(msg);
        qDebug() << "Emitting signalSendMessage";
        emit signalSendToClient(msg->getContent(), msg->getSender(), msg->getIDMessage());
        emit signalSendMessage();
    }
    else
        activeOperation = false;
}

