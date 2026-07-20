#include "songrepository.h"

//SongRepository::SongRepository() {}

int SongRepository:: save(const Song& data)
{
    for(Song &item:songs)
    {
        if(item.getSongID()==data.getSongID())
        {

            item=data;
            return data.getSongID();
        }
    }
    songs.push_back(data);
    return data.getSongID();
}


bool SongRepository:: remove(int id)
{
    for (auto item = songs.begin(); item != songs.end(); ++item)
    {
        if (item->getSongID() == id)
        {
            songs.erase(item);
            return true;
        }
    }
    return false;
}


optional<Song> SongRepository:: search(int id) const
{
    int size=songs.size();
    for(int i=0;i<size;i++)
    {
        if(songs[i].getSongID()==id)
        {
            return songs[i];
        }
    }
    return nullopt;
}
