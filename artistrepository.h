#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H
#include<vector>
#include "accountrepository.h"
#include"artist.h"
class ArtistRepository : public AccountRepository
{
private:
    vector<Artist>artists;
    ArtistRepository() = default;
public:
     ArtistRepository(const ArtistRepository&) = delete;
    int  save(const Acount& data) override;
    bool remove(int id) override;
    optional<Acount> search(int id) const override;
    optional<Acount> searchByUserName(string username)const override;
    const vector<Artist>& getAll() const { return artists; }


    static ArtistRepository& getInstance()
    {
        static ArtistRepository instance;
        return instance;
    }
};

#endif // ARTISTREPOSITORY_H
