#ifndef LISTENER_H
#define LISTENER_H
#include<vector>
#include "acount.h"

class Listener : public Acount
{
private:
    vector<int> likedSongs;
public:
    Listener(string Fullname, string Username, bool Role, string Password, string Biography, int ID);
    void addLike(int ID);
    void removeLike(int ID);
    bool checkLike(int ID)const;
    vector<int> getLikedSongs() const { return likedSongs; }
    void setLikedSongs(const vector<int>& songs);
};

#endif // LISTENER_H
