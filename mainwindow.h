#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // ================= Core =================
    QStackedWidget *stackedWidget;

    // ================= Pages =================
    QWidget *welcomePage;
    QWidget *loginPage;
    QWidget *signUpPage;
    QWidget *artistDashboardPage;
    QWidget *artistProfilePage;
    QWidget *collectionPage;
    QWidget *listenerDashboardPage;

    // playlist pages
    QWidget *playlistsPage;
    QWidget *playlistSongsPage;

    // ================= Welcome Page Widgets =================
    QRadioButton *rbWelcomeSignUp;
    QRadioButton *rbWelcomeLogin;

    // ================= Login Page Widgets =================
    QLineEdit *txtLoginUser;
    QLineEdit *txtLoginPass;

    // ================= Sign Up Page Widgets =================
    QRadioButton *rbSignListener;
    QRadioButton *rbSignArtist;
    QLineEdit *txtSignFull;
    QLineEdit *txtSignUser;
    QLineEdit *txtSignPass;
    QLineEdit *txtSignBio;

    // ================= Artist Dashboard Widgets =================
    QPushButton *btnArtistName;
    QPushButton *btnSingles;
    QPushButton *btnAddSong;
    QPushButton *btnAddAlbum;
    QPushButton *btnLogoutArtist;

    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;

    // ================= Listener Dashboard Widgets =================
    QPushButton *btnListenerName;
    QPushButton *btnBrowseArtists;
    QPushButton *btnMyPlaylists;
    QPushButton *btnLogoutListener;

    // ================= Artist Profile Widgets =================
    QLabel *lblProfileFullNameValue;
    QLabel *lblProfileUsernameValue;
    QLabel *lblProfileBioValue;

    QPushButton *btnEditProfile;
    QPushButton *btnDeleteProfile;
    QPushButton *btnBackToDashboard;

    // ================= Collection Page Widgets =================
    QLabel *lblCollectionTitle;

    QWidget *songsContainer;
    QVBoxLayout *songsLayout;
    QScrollArea *songsScrollArea;

    QPushButton *btnBackFromCollection;
    QPushButton *btnEditAlbum;
    QPushButton *btnDeleteAlbum;

    int currentAlbumId;

    // ================= Playlists Page Widgets =================
    QListWidget *playlistsListWidget;
    QPushButton *btnBackFromPlaylists;
    QPushButton *btnAddPlaylist;

    // ================= Playlist Songs Page Widgets =================
    QLabel *lblPlaylistSongsTitle;

    QWidget *playlistSongsContainer;
    QVBoxLayout *playlistSongsLayout;
    QScrollArea *playlistSongsScrollArea;

    QPushButton *btnBackFromPlaylistSongs;
    QPushButton *btnEditPlaylist;
    QPushButton *btnDeletePlaylist;

    int currentPlaylistId;
    QString currentPlaylistName;
    bool currentPlaylistIsFavorite = false;

private:
    // ================= Page Creation =================
    void createWelcomePage();
    void createLoginPage();
    void createSignUpPage();
    void createArtistDashboardPage();
    void createArtistProfilePage();
    void createCollectionPage();
    void createListenerDashboardPage();

    void createPlaylistsPage();
    void createPlaylistSongsPage();

    // ================= Navigation =================
    void showWelcomePage();
    void showLoginPage();
    void showSignUpPage();
    void showArtistDashboardPage();
    void showListenerDashboardPage();
    void showArtistProfilePage();
    void showCollectionPage();

    void showPlaylistsPage();
    void showPlaylistSongsPage();

    // ================= Artist Dashboard Helpers =================
    void refreshArtistDashboard();
    void clearAlbumsList();
    QPushButton* createAlbumItemButton(const QString &albumTitle, int albumId);

    // ================= Collection Helpers =================
    void clearSongsList();
    QPushButton* createSongItemButton(const QString &songTitle, int songID);
    void loadCollectionPage(const QString &title, const std::vector<class Song> &songs);

    // ================= Playlist Helpers =================
    void loadPlaylists();
    void loadPlaylistSongsPage(int playlistId, const QString &playlistName, bool isFavorite);
    void clearPlaylistSongsList();
    QPushButton* createPlaylistSongItemButton(const QString &songTitle, int songID);

    // ================= Event Handlers =================
    void handleLogin();
    void handleSignUp();

    void onAlbumButtonClicked();
    void handleAlbumClicked(int albumId, const QString &albumTitle);
    void handleSinglesClicked();

    void onSongButtonClicked();
    void handleSongClicked(int songID);
    void handleEditSong(const class Song &song);

    void handleEditProfile();
    void handleDeleteProfile();

    void handleDeleteAlbum();
    void handleEditAlbum();
    void handleAddAlbum();
    void handleAddSong();

    void onPlaylistItemClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H

