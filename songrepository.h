#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H
#include <vector>
#include "AbstractRepository.h"
#include "song.h"
class SongRepository : public AbstractRepository<Song>
{
private:
    vector<Song> songs;
public:
    int  save(const Song& data) override;
    bool remove(int id) override;
    optional<Song> search(int id) const override;
    vector<Song> singleSongs(int artistID)const;
    vector <Song> getByAlbum(int albumID)const;
    vector<Song> getByArtist(int artistID)const;
    vector<Song> getByPlaylist(int playlistID)const;
    vector<Song> getByLikedSongs(int listenerID);
};

#endif // SONGREPOSITORY_H
