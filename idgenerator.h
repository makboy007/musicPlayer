#ifndef IDGENERATOR_H
#define IDGENERATOR_H

class IdGenerator
{
private:
    IdGenerator() = delete; // prevent creating objects

    static int songIdCounter;
    static int playlistIdCounter;
    static int albumIdCounter;
    static int accountIdCounter;
public:
    static int generateSongId();
    static int generatePlaylistId();
    static int generateAlbumId();
    static int generateAccountId();
};

#endif // IDGENERATOR_H

