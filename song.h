#ifndef SONG_H
#define SONG_H
#include <iostream>
#include<string>
using namespace std;
class Song
{
private:
    string name;
    int releaseYear;
    string genre;
    int songID;
    int artistId;
    int albumID;
public:
    Song(string name,int releaseYear, string genre, int artistId, int albumID);

    string getName() const { return name; }
    void setName(string name) { this->name = name; }

    int getReleaseYear() const { return releaseYear; }
    void setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }

    string getGenre() const { return genre; }
    void setGenre(string genre) { this->genre = genre; }

    int getSongID() const { return songID; }
    void setSongID(int songID) { this->songID = songID; }

    int getArtistId() const { return artistId; }
    void setArtistId(int artistId) { this->artistId = artistId; }

    int getAlbumID() const { return albumID; }
    void setAlbumID(int albumID) { this->albumID = albumID; }
};

#endif // SONG_H
