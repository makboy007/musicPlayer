#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <optional>

using namespace std;

class Controller {
private:
    Controller() = default;
    Controller(const Controller&) = delete;
    int currentUserId = -1;
    bool isCurrentArtist = false;
public:
    static Controller& getInstance()
    {
        static Controller instance;
        return instance;
    }

    int getCurrentUserId() const { return currentUserId; }
    bool isArtistMode() const { return isCurrentArtist; }


    bool signUp(string fullName, string username, string password, string bio, bool isArtistRole);

};

#endif