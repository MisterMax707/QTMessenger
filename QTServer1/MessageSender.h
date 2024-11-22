#pragma once
#include <QObject>
#include "QTimer.h"
#include "QThread.h"
#include "QMutex.h"
#include "QQueue.h"
#include "QString.h"
#include <GroupChat.h>

class MessageSender  : public QObject
{
	Q_OBJECT

public:
	MessageSender(QObject *parent = nullptr, int chat = 0);
	~MessageSender();
	void addMessageToQueueForSending(QString contentMessage, QString nickSender);

signals:
	void signalSendMessage();
	void signalSendToClient(QString content, QString sender, int id);

private slots:
	void sendMessage();
	void onThreadFinished();

private:
	QQueue < QPair<QString, QString> > queueForSendingMessage;
	GroupChat* chat;
	QThread* workerThread;
	QMutex mutex;
	bool activeOperation = false;
};
