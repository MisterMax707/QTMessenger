#include "GroupChat.h"

int GroupChat::id_group = 0;

GroupChat::GroupChat(QString name) : GroupName(name) 
{
    id_group++;
};

int GroupChat::getIDGroupChat()
{
    return id_group;
}
