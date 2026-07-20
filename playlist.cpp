#include "playlist.h"
#include "idgenerator.h"
Playlist::Playlist(string name,int ListenerID)
{
    this->name=name;
    this->ListenerID=ListenerID;
    this->ListID=IdGenerator::generatePlaylistId();
}
