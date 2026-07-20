#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H
#include <vector>
#include"playlist.h"
#include "abstractrepository.h"

class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    vector<Playlist>playlists;
public:
int  save(const Playlist& data) override;
    bool remove(int id) override;
    optional<Playlist> search(int id) const override;
};

#endif // PLAYLISTREPOSITORY_H
