#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <optional>

#include"albumrepository.h"
#include"songrepository.h"
using namespace std;

class Controller {
private:
    Controller() = default;
    Controller(const Controller&) = delete;
    int currentUserId = -1;
    bool isCurrentArtist = false;
public:
    static Controller& getInstance()
    {
        static Controller instance;
        return instance;
    }

    int getCurrentUserId() const { return currentUserId; }
    bool isArtistMode() const { return isCurrentArtist; }


    bool signUp(string fullName, string username, string password, string bio, bool isArtistRole);
    bool login(string username, string password);
    void logout();

    bool addMyAlbum(string nameAlbum);
   optional<vector<Album>> myAlbums();
    bool removeAlbum(int albumID);
   bool editAlbum(int albumID ,string newName);

   bool addmySong(string nameSong,int year,string genre,int albumID);
   optional<vector<Song>> mySingleSong();
   optional<vector<Song>> showSongsInAlbum(int albumID);
   bool removeSong(int songID);
   bool editSong(int songID, string nameSong, int year, string genre, int albumID);
   optional<Song> getSong(int songID);
};

#endif