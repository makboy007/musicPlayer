#include "albumrepository.h"

int AlbumRepository:: save(const Album& data)
{
    for(Album &item:albums)
    {
        if(item.getAlbumID()==data.getAlbumID())
        {

            item=data;
            return data.getAlbumID();
        }
    }
    albums.push_back(data);
    return data.getAlbumID();
}


bool AlbumRepository:: remove(int id)
{
    for (auto item = albums.begin(); item != albums.end(); ++item)
    {
        if (item->getAlbumID() == id)
        {
            albums.erase(item);
            return true;
        }
    }
    return false;
}


optional<Album> AlbumRepository:: search(int id) const
{
    int size=albums.size();
    for(int i=0;i<size;i++)
    {
        if(albums[i].getAlbumID()==id)
        {
            return albums[i];
        }
    }
    return nullopt;
}


vector<Album> AlbumRepository::Albums(int artistID) const
{
    std::vector<Album> result;

    for (const auto& album : albums)
    {
        if (album.getArtistID() == artistID)
        {
            result.push_back(album);
        }
    }

    return result;
}











