#include "listenerrepository.h"

int ListenerRepository:: save(const Acount& data)
{
     const Listener& listenerData = static_cast<const Listener&>(data);
    for(Acount &item:listeners)
    {
        if(item.getID()==data.getID())
        {

            item=data;
            return data.getID();
        }
    }
    listeners.push_back(listenerData);
    return data.getID();
}


bool ListenerRepository:: remove(int id)
{
    for (auto item = listeners.begin(); item != listeners.end(); ++item)
    {
        if (item->getID() == id)
        {
            listeners.erase(item);
            return true;
        }
    }
    return false;
}


optional<Acount> ListenerRepository:: search(int id) const
{
    int size=listeners.size();
    for(int i=0;i<size;i++)
    {
        if(listeners[i].getID()==id)
        {
            return listeners[i];
        }
    }
    return nullopt;
}

optional<Acount> ListenerRepository:: searchByUserName(string username)const
{
    int size=listeners.size();
    for(int i=0;i<size;i++)
    {
        if(listeners[i].getUserName()==username)
        {
            return listeners[i];
        }
    }
    return nullopt;
}

void ListenerRepository:: updateLiked(int listenerID,int songID,bool like)
{
    for (Listener &item : listeners)
    {
        if (item.getID() == listenerID)
        {
            if (like)
            {
                item.addLike(songID);
            }
            else
            {
                item.removeLike(songID);
            }
            return;
        }
    }
}

bool ListenerRepository:: isLiked(int listenerID,int songID)const
{
    for (const Listener &item : listeners)
    {
        if (item.getID() == listenerID)
        {
            if (item.checkLike(songID))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}














