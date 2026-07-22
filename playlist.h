#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include <string>
#include<vector>
using namespace std;
class Playlist
{
private:
    string name;
    int ListenerID;
    int ListID;
    vector<int> songIDs;
public:
    Playlist(string name,int ListenerID);
    Playlist(string name,int ListenerID,int listID);

    string getName() const { return name; }
    void setName(string name) { this->name = name; }

    int getListenerID() const { return ListenerID; }
    void setListenerID(int listenerID) { ListenerID = listenerID; }

    int getListID() const { return ListID; }
    void setListID(int listID) { ListID = listID; }

    void addSong(int songID) { songIDs.push_back(songID); }
    void removeSong(int songID);
    const vector<int>& getSongIDs() const { return songIDs; }

    void setSongIDs(const vector<int>& ids);
};

#endif // PLAYLIST_H
