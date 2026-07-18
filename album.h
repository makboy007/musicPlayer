#ifndef ALBUM_H
#define ALBUM_H
#include <iostream>
#include <string>
using namespace std;
class Album
{
private:
    string name ;
    int ArtistID;
    int AlbumID;
public:
    Album(string name,int ArtistID);

    string getName() const { return name; }
    void setName(string name) { this->name = name; }

    int getArtistID() const { return ArtistID; }
    void setArtistID(int artistID) { ArtistID = artistID; }

    int getAlbumID() const { return AlbumID; }
    void setAlbumID(int albumID) { AlbumID = albumID; }
};

#endif // ALBUM_H
