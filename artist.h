#ifndef ARTIST_H
#define ARTIST_H

#include "acount.h"

class Artist : public Acount
{
public:
    Artist(string Fullname, string Username, bool Role, string Password, string Biography, int ID);
};

#endif // ARTIST_H
