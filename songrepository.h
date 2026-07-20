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
};

#endif // SONGREPOSITORY_H
