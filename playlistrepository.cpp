#include "playlistrepository.h"

int PlaylistRepository:: save(const Playlist& data)
{
    for(Playlist& item:playlists)
    {
        if(item.getListID()==data.getListID())
        {

            item=data;
            return data.getListID();
        }
    }
    playlists.push_back(data);
    return data.getListID();
}


bool PlaylistRepository:: remove(int id)
{
    for (auto item = playlists.begin(); item != playlists.end(); ++item)
    {
        if (item->getListID() == id)
        {
            playlists.erase(item);
            return true;
        }
    }
    return false;
}


optional<Playlist> PlaylistRepository:: search(int id) const
{
    int size=playlists.size();
    for(int i=0;i<size;i++)
    {
        if(playlists[i].getListID()==id)
        {
            return playlists[i];
        }
    }
    return nullopt;
}




