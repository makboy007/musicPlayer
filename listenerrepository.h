#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H
#include <vector>
#include "accountrepository.h"
#include"listener.h"
class ListenerRepository : public AccountRepository
{
private:
    vector<Listener>listeners;
    ListenerRepository() = default;
    ListenerRepository(const ListenerRepository&) = delete;
public:
    int  save(const Acount& data) override;
    bool remove(int id) override;
    optional<Acount> search(int id) const override;
    optional<Acount> searchByUserName(string username)const override;
    void updateLiked(int listenerID,int songID,bool like);
    bool isLiked(int listenerID,int songID)const;

    static ListenerRepository& getInstance()
    {
        static ListenerRepository instance;
        return instance;
    }

    const vector<Listener>& getAll() const { return listeners; }
};

#endif // LISTENERREPOSITORY_H
