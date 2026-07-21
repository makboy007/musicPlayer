#include <algorithm>
#include "songrepository.h"
#include "playlistrepository.h"
#include"listenerrepository.h"

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

vector<Song> SongRepository:: singleSongs(int artistID) const
{
    vector<Song> singles;
    for (const Song &item : songs)
    {
        if (item.getArtistId() == artistID && item.getAlbumID() == 0)
        {
            singles.push_back(item);
        }
    }
    return singles;
}

vector<Song> SongRepository:: getByAlbum(int albumID)const
{
  vector<Song> album;

    for (const Song &item : songs)
    {
        if (item.getAlbumID() == albumID)
        {
            album.push_back(item);
        }
    }
    return album;
}

vector<Song> SongRepository:: getByArtist(int artistID)const
{
    vector<Song> listSongs;
    for (const Song &item : songs)
    {
        if (item.getArtistId() == artistID)
        {
            listSongs.push_back(item);
        }
    }
    return listSongs;
}

vector<Song> SongRepository:: getByPlaylist(int playlistID)const
{
    vector<Song> result;
    auto& playlistRepo = PlaylistRepository::getInstance();
    optional<Playlist> playlistOpt = playlistRepo.search(playlistID);

    if (!playlistOpt.has_value())
    {
        return result;
    }

    const vector<int>& songIDs = playlistOpt->getSongIDs();

    for (const auto& song : songs)
    {
        if (std::find(songIDs.begin(), songIDs.end(), song.getAlbumID()) != songIDs.end())
        {
            result.push_back(song);
        }
    }
    return result;
}

vector<Song> SongRepository::getByLikedSongs(int listenerID) {
    std::vector<Song> result;
    auto& listenerRepo = ListenerRepository::getInstance();

    for (const auto& song : songs)
    {
        if (listenerRepo.isLiked(listenerID, song.getSongID()))
        {
            result.push_back(song);
        }
    }
    return result;
}






