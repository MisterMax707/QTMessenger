#include "GroupChat.h"

GroupChat::GroupChat(QString name) : GroupName(name) 
{
    id_group++;
};

int GroupChat::getIDGroupChat()
{
    return id_group;
}
