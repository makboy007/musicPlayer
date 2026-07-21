#include "playlist.h"
#include "idgenerator.h"
Playlist::Playlist(string name,int ListenerID)
{
    this->name=name;
    this->ListenerID=ListenerID;
    this->ListID=IdGenerator::generatePlaylistId();
}

void Playlist:: removeSong(int songID) {
    for (auto it = songIDs.begin(); it != songIDs.end(); ++it) {
        if (*it == songID) {
            songIDs.erase(it);
            break;
        }
    }
}