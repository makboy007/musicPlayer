#include "listener.h"

Listener::Listener(string Fullname, string Username, bool Role, string Password, string Biography, int ID)
    : Acount(Fullname, Username, Role, Password, Biography, ID)
{

}

void Listener:: addLike(int ID)
{
    if(!checkLike(ID))
    {
        likedSongs.push_back(ID);
    }
}

void Listener:: removeLike(int ID)
{
    for (auto it = likedSongs.begin(); it != likedSongs.end(); ++it)
    {
        if (*it == ID)
        {
            likedSongs.erase(it);
            return;
        }
    }
}

bool Listener::checkLike(int ID)const
{
    for (auto it = likedSongs.begin(); it != likedSongs.end(); ++it)
    {
        if (*it == ID)
        {
            return 1;
        }
    }
    return 0;
}

void Listener::setLikedSongs(const vector<int>& songs)
{
    likedSongs = songs;
}