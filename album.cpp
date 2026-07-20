#include "album.h"
#include "idgenerator.h"
Album::Album(string name,int ArtistID)
{
    this->name=name;
    this->ArtistID=ArtistID;
    this->AlbumID=IdGenerator::generateAlbumId();
}
