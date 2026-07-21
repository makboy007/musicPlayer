#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H
#include<vector>
#include "accountrepository.h"
#include"artist.h"
class ArtistRepository : public AccountRepository
{
private:
    vector<Artist>artists;
public:
    int  save(const Acount& data) override;
    bool remove(int id) override;
    optional<Acount> search(int id) const override;
    optional<Acount> searchByUserName(string username)const override;
};

#endif // ARTISTREPOSITORY_H
