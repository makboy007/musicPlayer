#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H
#include <vector>
#include"playlist.h"
#include "abstractrepository.h"

class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    vector<Playlist>playlists;

    PlaylistRepository(){};
    PlaylistRepository(const PlaylistRepository&) = delete;
public:
    static PlaylistRepository& getInstance()
    {
        static PlaylistRepository instance;
        return instance;
    }

    int save(const Playlist& data) override;
    bool remove(int id) override;
    optional<Playlist> search(int id) const override;

    void insertSong(int playlistID,int songID);
    void removeSong(int playlistID,int songID);
    vector<Playlist> Playlists(int listenerID) const;
};

#endif // PLAYLISTREPOSITORY_H
