#include "artistrepository.h"

int ArtistRepository:: save(const Acount& data)
{
    const Artist& artistData = static_cast<const Artist&>(data);
    for(Artist &item:artists)
    {
        if(item.getID()==data.getID())
        {

            item=artistData;
            return data.getID();
        }
    }
    artists.push_back(artistData);
    return data.getID();
}


bool ArtistRepository:: remove(int id)
{
    for (auto item = artists.begin(); item != artists.end(); ++item)
    {
        if (item->getID() == id)
        {
            artists.erase(item);
            return true;
        }
    }
    return false;
}


optional<Acount> ArtistRepository:: search(int id) const
{
    int size=artists.size();
    for(int i=0;i<size;i++)
    {
        if(artists[i].getID()==id)
        {
            return artists[i];
        }
    }
    return nullopt;
}

optional<Acount> ArtistRepository:: searchByUserName(string username)const
{
    int size=artists.size();
    for(int i=0;i<size;i++)
    {
        if(artists[i].getUserName()==username)
        {
            return artists[i];
        }
    }
    return nullopt;
}









