#include "song.h"
#include "idgenerator.h"
Song::Song(string name,int releaseYear, string genre, int artistId, int albumID)
{
    this->name=name;
    this->releaseYear=releaseYear;
    this->genre=genre;
    this->artistId=artistId;
    this->albumID=albumID;
    this->songID=IdGenerator::generateSongId();
}

Song::Song(string name,int releaseYear, string genre, int artistId, int albumID,int songID)
{
    this->name=name;
    this->releaseYear=releaseYear;
    this->genre=genre;
    this->artistId=artistId;
    this->albumID=albumID;
    this->songID=songID;
}

void Song::edit(string name,int releaseYear, string genre, int artistId, int albumID)
{
    this->name=name;
    this->releaseYear=releaseYear;
    this->genre=genre;
    this->artistId=artistId;
    this->albumID=albumID;
}