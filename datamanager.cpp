#include<sstream>
#include <fstream>

#include "DataManager.h"
#include "SongRepository.h"
#include "ArtistRepository.h"
#include "ListenerRepository.h"
#include "PlaylistRepository.h"
#include "IdGenerator.h"

using namespace std;

const string DataManager::filePath = "database.txt";

string DataManager::joinVector(const vector<int>& vec) {
    if (vec.empty()) return "NONE";
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += to_string(vec[i]);
        if (i < vec.size() - 1) result += ",";
    }
    return result;
}

vector<int> DataManager::splitVector(const string& str) {
    vector<int> vec;
    if (str == "NONE" || str.empty()) return vec;
    stringstream ss(str);
    string item;
    while (getline(ss, item, ',')) {
        vec.push_back(stoi(item));
    }
    return vec;
}

void DataManager::saveAll() {
    ofstream outFile(filePath, ios::trunc);
    if (!outFile.is_open()) return;

    // 1. ذخیره Listeners (Role: false)
    for (const auto& l : ListenerRepository::getInstance().getAll())
    {
        outFile << "LISTENER|" << l.getID() << "|" << l.getUserName() << "|"
                << l.getPassword() << "|" << l.getFullName() << "|"
                << l.getBiography() << "|" << joinVector(l.getLikedSongs()) << "\n";
    }

    // 2. ذخیره Artists (Role: true)
    for (const auto& a : ArtistRepository::getInstance().getAll()) {
        outFile << "ARTIST|" << a.getID() << "|" << a.getUserName() << "|"
                << a.getPassword() << "|" << a.getFullName() << "|"
                << a.getBiography() << "\n";
    }

    // 3. ذخیره Songs
    for (const auto& s : SongRepository::getInstance().getAll()) {
        outFile << "SONG|" << s.getSongID() << "|" << s.getName() << "|"
                << s.getGenre() << "|" << s.getReleaseYear() << "|"
                << s.getArtistId() << "|" << s.getAlbumID() << "\n";
    }

    // 4. ذخیره Playlists
    for (const auto& p : PlaylistRepository::getInstance().getAll()) {
        outFile << "PLAYLIST|" << p.getListID() << "|" << p.getName() << "|"
                << p.getListenerID() << "|" << joinVector(p.getSongIDs()) << "\n";
    }

    // 5. ذخیره وضعیت IdGenerator
    outFile << "IDS|" << IdGenerator::songIdCounter << "|"
            << IdGenerator::playlistIdCounter << "|"
            << IdGenerator::albumIdCounter << "|"
            << IdGenerator::accountIdCounter << "\n";

    outFile.close();
}

void DataManager::loadAll() {
    ifstream inFile(filePath);
    if (!inFile.is_open()) return;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string tag;
        getline(ss, tag, '|');

        if (tag == "LISTENER") {
            string id, user, pass, full, bio, liked;
            getline(ss, id, '|'); getline(ss, user, '|'); getline(ss, pass, '|');
            getline(ss, full, '|'); getline(ss, bio, '|'); getline(ss, liked, '|');

            // ترتیب سازنده Account: Fullname, Username, Role(false), Password, Biography, ID
            Listener l(full, user, false, pass, bio, stoi(id));
            l.setLikedSongs(splitVector(liked));
            ListenerRepository::getInstance().save(l);
        }
        else if (tag == "ARTIST") {
            string id, user, pass, full, bio;
            getline(ss, id, '|'); getline(ss, user, '|'); getline(ss, pass, '|');
            getline(ss, full, '|'); getline(ss, bio, '|');

            // ترتیب سازنده Account: Fullname, Username, Role(true), Password, Biography, ID
            Artist a(full, user, true, pass, bio, stoi(id));
            ArtistRepository::getInstance().save(a);
        }
        else if (tag == "SONG") {
            string id, name, genre, year, aId, albId;
            getline(ss, id, '|'); getline(ss, name, '|'); getline(ss, genre, '|');
            getline(ss, year, '|'); getline(ss, aId, '|'); getline(ss, albId, '|');

            // ترتیب سازنده Song: name, releaseYear, genre, artistId, albumID, songID
            Song s(name, stoi(year), genre, stoi(aId), stoi(albId), stoi(id));
            SongRepository::getInstance().save(s);
        }
        else if (tag == "PLAYLIST") {
            string id, name, lId, sIds;
            getline(ss, id, '|'); getline(ss, name, '|'); getline(ss, lId, '|'); getline(ss, sIds, '|');

            // ترتیب سازنده Playlist: name, ListenerID, listID
            Playlist p(name, stoi(lId), stoi(id));
            p.setSongIDs(splitVector(sIds)); // فرض بر وجود متد setSongIDs
            PlaylistRepository::getInstance().save(p);
        }
        else if (tag == "IDS") {
            string sId, pId, albId, accId;
            getline(ss, sId, '|'); getline(ss, pId, '|'); getline(ss, albId, '|'); getline(ss, accId, '|');

            IdGenerator::songIdCounter = stoi(sId);
            IdGenerator::playlistIdCounter = stoi(pId);
            IdGenerator::albumIdCounter = stoi(albId);
            IdGenerator::accountIdCounter = stoi(accId);
        }
    }
    inFile.close();
}
