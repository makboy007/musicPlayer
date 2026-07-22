#include "album.h"
#include "idgenerator.h"
Album::Album(string name,int ArtistID)
{
    this->name=name;
    this->ArtistID=ArtistID;
    this->AlbumID=IdGenerator::generateAlbumId();
}

Album::Album(string name,int ArtistID,int albumID)
{
    this->name=name;
    this->ArtistID=ArtistID;
    this->AlbumID=albumID;
}