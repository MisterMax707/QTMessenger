#include "GroupChat.h"

GroupChat::GroupChat(const QString& name, const QVector<QString>& usersId) : GroupName(name)
{
	ListParticipators = QList<QString>::fromVector(usersId.toVector());;
	id = QString::number(count++);
};

QString GroupChat::getId()
{
	return this->id;
}

