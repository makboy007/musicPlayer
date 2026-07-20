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
