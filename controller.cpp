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
