#include "Controller.h"
#include "ListenerRepository.h"
#include "ArtistRepository.h"
#include "IdGenerator.h"
#include "DataManager.h"
using namespace std;

bool Controller::signUp(string fullName, string username, string password, string bio, bool isArtistRole)
{
    auto listenerSearch = ListenerRepository::getInstance().searchByUserName(username);
    auto artistSearch = ArtistRepository::getInstance().searchByUserName(username);

    if (listenerSearch.has_value() || artistSearch.has_value())
    {
        return false;
    }
    int newId = IdGenerator::generateAccountId();

    if (isArtistRole)
    {
        Artist newArtist(fullName, username, true, password, bio, newId);
        ArtistRepository::getInstance().save(newArtist);
    }
    else
    {
        Listener newListener(fullName, username, false, password, bio, newId);
        ListenerRepository::getInstance().save(newListener);
    }
    DataManager::saveAll();

    return true;
}

bool Controller::login(string username, string password)
{
    auto listener = ListenerRepository::getInstance().searchByUserName(username);
    if (listener.has_value() && listener->getPassword() == password)
    {
        currentUserId = listener->getID();
        isCurrentArtist = false;
        return true; // لاگین موفق به عنوان شنونده
    }

    auto artist = ArtistRepository::getInstance().searchByUserName(username);
    if (artist.has_value() && artist->getPassword() == password)
    {
        currentUserId = artist->getID();
        isCurrentArtist = true;
        return true; // لاگین موفق به عنوان هنرمند
    }
    return false;
}

void Controller::logout()
{
    currentUserId = -1;
    isCurrentArtist = false;
}



optional<vector<Album>> Controller:: myAlbums()
{
    if(isCurrentArtist&&currentUserId != -1)
    {
        return AlbumRepository::getInstance().Albums(currentUserId);
    }
    return nullopt;
}

optional<vector<Song>> Controller:: mySingleSong()
{
    if(isCurrentArtist&&currentUserId != -1)
    {
        return SongRepository::getInstance().singleSongs(currentUserId);
    }
    return nullopt;
}

bool Controller::addMyAlbum(string nameAlbum)
{
    if(currentUserId!=-1&&isCurrentArtist)
    {
        Album newAlbum(nameAlbum,currentUserId);
        AlbumRepository::getInstance().save(newAlbum);
        DataManager::saveAll();
        return true;
    }
    return false;
}

bool Controller:: removeAlbum(int albumID)
{
    if(currentUserId!=-1&&isCurrentArtist)
    {
        AlbumRepository::getInstance().remove(albumID);
        DataManager::saveAll();
        return true;
    }
    return false;
}


bool Controller:: addmySong(string nameSong,int year,string genre,int albumID)
{
    if(currentUserId!=-1&&isCurrentArtist)
    {
        Song newSong(nameSong,year,genre,currentUserId,albumID);
        SongRepository::getInstance().save(newSong);
        DataManager::saveAll();
        return true;
    }
    return false;
}

bool Controller:: removeSong(int songID)
{
    if(currentUserId!=-1&&isCurrentArtist)
    {
        SongRepository::getInstance().remove(songID);
        DataManager::saveAll();
        return true;
    }
    return false;
}

optional<vector<Song>> Controller:: showSongsInAlbum(int albumID)
{
    if(isCurrentArtist&&currentUserId != -1)
    {
        return SongRepository::getInstance().getByAlbum(albumID);
    }
    return nullopt;
}

bool Controller:: editAlbum(int albumID,string newName)
{
    if (currentUserId != -1 && isCurrentArtist)
    {
        if (AlbumRepository::getInstance().updateAlbumName(albumID, newName))
        {
            DataManager::saveAll();
            return true;
        }
    }
    return false;
}

bool Controller::editSong(int songID, string nameSong, int year, string genre, int albumID)
{
    if (currentUserId != -1 && isCurrentArtist)
    {
        return SongRepository::getInstance().updateSong(songID, nameSong, year, genre, albumID);
        DataManager::saveAll();
        return true;
    }
    return false;
}

optional<Song> Controller::getSong(int songID)
{
    return SongRepository::getInstance().search(songID);
}

Artist* Controller::getCurrentAccount()
{
    if (currentUserId == -1) return nullptr;

    // گرفتن لیست (حتی اگر const باشد)
    auto& artists = ArtistRepository::getInstance().getAll();

    for (const auto& artist : artists)
    {
        if (artist.getID() == currentUserId)
        {
            return const_cast<Artist*>(&artist);
        }
    }
    return nullptr;
}

bool Controller::updateProfile(const string& fullName, const string& username,const string& biography,const string& password)
{
    if (fullName.empty() || username.empty() || password.empty()) {
        return false;
    }

    const auto& artists = ArtistRepository::getInstance().getAll();
    for (const auto& artist : artists) {
        if (artist.getUserName() == username &&
            artist.getID() != currentUserId) {
            return false;
        }
    }

    Artist* currentAccount = getCurrentAccount();
    if (currentAccount == nullptr) {
        return false;
    }

    currentAccount->setFullName(fullName);
    currentAccount->setUserName(username);
    currentAccount->setBiography(biography);
    currentAccount->setPassword(password);

    DataManager::saveAll();
    return true;
}
bool Controller:: removeArtist()
{
    if(currentUserId!=-1&&isCurrentArtist)
    {
        ArtistRepository::getInstance().remove(currentUserId);
        DataManager::saveAll();
        return true;
    }
    return false;
}











