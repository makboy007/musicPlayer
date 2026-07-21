#ifndef LISTENER_H
#define LISTENER_H
#include<vector>
#include "acount.h"

class Listener : public Acount
{
private:
    vector<int> likedSongs;
public:
    void addLike(int ID);
    void removeLike(int ID);
    bool checkLike(int ID)const;
};

#endif // LISTENER_H
