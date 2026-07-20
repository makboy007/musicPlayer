#include "idgenerator.h"

int IdGenerator::songIdCounter = 1;
int IdGenerator::playlistIdCounter = 1;
int IdGenerator::albumIdCounter = 1;
int IdGenerator::accountIdCounter = 1;

int IdGenerator::generateSongId()
{
    return songIdCounter++;
}

int IdGenerator::generatePlaylistId()
{
    return playlistIdCounter++;
}

int IdGenerator::generateAlbumId()
{
    return albumIdCounter++;
}

int IdGenerator::generateAccountId()
{
    return accountIdCounter++;
}