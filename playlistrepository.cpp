#include "playlistrepository.h"
#include "songrepository.h"
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


bool PlaylistRepository::insertSong(int playlistID, int songID)
{
    auto song = SongRepository::getInstance().search(songID);
    if (!song.has_value())
    {
        return 0;
    }


    for (auto& pl : playlists)
    {
        if (pl.getListID() == playlistID)
        {
            pl.addSong(songID);
            return 1;
        }
    }
    return 0;
}

bool PlaylistRepository::removeSong(int playlistID, int songID)
{
    for (auto& pl : playlists)
    {
        if (pl.getListID() == playlistID)
        {
            pl.removeSong(songID);
            return 1;
        }
    }
    return 0;
}

vector<Playlist> PlaylistRepository::Playlists(int listenerID) const
{
    std::vector<Playlist> result;

    for (const auto& pl : playlists)
    {
        if (pl.getListenerID() == listenerID)
        {
            result.push_back(pl);
        }
    }

    return result;
}

bool PlaylistRepository::updatePlaylistName(int playlistId, const string& newName)
{
    for (auto &playlist : playlists)
    {
        if (playlist.getListID() == playlistId)
        {
            playlist.setName(newName);
            return true;
        }
    }
    return false;
}




