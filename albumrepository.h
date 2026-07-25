#ifndef ALBUMREPOSITORY_H
#define ALBUMREPOSITORY_H
#include <vector>

#include"album.h"
#include "abstractrepository.h"

class AlbumRepository : public AbstractRepository<Album>
{
private:
    vector<Album>albums;
    AlbumRepository() {}
    AlbumRepository(const AlbumRepository&) = delete;
public:
    int  save(const Album& data) override;
    bool remove(int id) override;
    optional<Album> search(int id) const override;

    vector<Album> Albums(int artistID) const;

    static AlbumRepository& getInstance()
    {
        static AlbumRepository instance;
        return instance;
    }
    const vector<Album>& getAll() const { return albums; }

    bool updateAlbumName(int albumId, const string& newName);
};

#endif // ALBUMREPOSITORY_H
