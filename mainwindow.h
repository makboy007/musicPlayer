#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <optional>
#include <vector>
#include <QTextEdit>
class QWidget;
class QStackedWidget;
class QRadioButton;
class QLineEdit;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QScrollArea;
class QListWidget;
class QListWidgetItem;

class Song;
class Album;
class Artist;
class Listener;
class Playlist;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // --- Page creation ---
    void createWelcomePage();
    void createLoginPage();
    void createSignUpPage();
    void createArtistDashboardPage();
    void createArtistProfilePage();
    void createCollectionPage();
    void createListenerDashboardPage();
    void createPlaylistsPage();
    void createPlaylistSongsPage();
    void createListenerProfilePage();
    void showListenerProfilePage();
    void handleEditListenerProfile();
    void handleDeleteListenerProfile();
    // --- Artist Browser pages ---
    void createArtistBrowserPage();
    void createArtistAlbumsPage();
    void createArtistSongsPage();

    // --- Navigation ---
    void showWelcomePage();
    void showLoginPage();
    void showSignUpPage();
    void showArtistDashboardPage();
    void showListenerDashboardPage();
    void showArtistProfilePage();
    void showCollectionPage();
    void showPlaylistsPage();
    void showPlaylistSongsPage();

    // --- Artist Browser navigation ---
    void showArtistBrowserPage();
    void showArtistAlbumsPage(int artistID, const QString &artistName);
    void showArtistSongsPage(int albumID, const QString &albumTitle, int artistID);

    // --- Helpers: artist dashboard / collection ---
    void clearAlbumsList();
    void clearSongsList();
    QPushButton* createAlbumItemButton(const QString &albumTitle, int albumId);
    QPushButton* createSongItemButton(const QString &songTitle, int songID);
    void refreshArtistDashboard();
    void loadCollectionPage(const QString &title, const std::vector<Song> &songs);

    // --- Helpers: playlists ---
    void clearPlaylistSongsList();
    QPushButton* createPlaylistSongItemButton(const QString &songTitle, int songID);
    void loadPlaylists();
    void loadPlaylistSongsPage(int playlistId, const QString &playlistName, bool isFavorite);

    // --- Song / album handlers ---
    void handleAlbumClicked(int albumId, const QString &albumTitle);
    void handleSinglesClicked();
    void handleSongClicked(int songID);
    void handleListenerSongClicked(int songID);
    void handleEditSong(const Song& song);

    // --- Profile / auth / CRUD handlers ---
    void handleEditProfile();
    void handleDeleteAlbum();
    void handleEditAlbum();
    void handleLogin();
    void handleSignUp();
    void handleDeleteProfile();
    void handleAddAlbum();
    void handleAddSong();

private slots:
    void onAlbumButtonClicked();
    void onSongButtonClicked();
    void onPlaylistItemClicked(QListWidgetItem *item);

private:
    // --- Core ---
    QStackedWidget *stackedWidget;

    // --- Welcome Page ---
    QWidget *welcomePage;
    QRadioButton *rbWelcomeSignUp;
    QRadioButton *rbWelcomeLogin;

    // --- Login Page ---
    QWidget *loginPage;
    QLineEdit *txtLoginUser;
    QLineEdit *txtLoginPass;

    // --- Sign Up Page ---
    QWidget *signUpPage;
    QRadioButton *rbSignListener;
    QRadioButton *rbSignArtist;
    QLineEdit *txtSignFull;
    QLineEdit *txtSignUser;
    QLineEdit *txtSignPass;
    QLineEdit *txtSignBio;

    // --- Artist Dashboard Page ---
    QWidget *artistDashboardPage;
    QPushButton *btnArtistName;
    QPushButton *btnSingles;
    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;
    QPushButton *btnAddSong;
    QPushButton *btnAddAlbum;
    QPushButton *btnLogoutArtist;

    // --- Listener Dashboard Page ---
    QWidget *listenerDashboardPage;
    QPushButton *btnListenerName;
    QPushButton *btnBrowseArtists;
    QPushButton *btnMyPlaylists;
    QPushButton *btnLogoutListener;

    // --- Artist Profile Page ---
    QWidget *artistProfilePage;
    QLabel *lblProfileFullNameValue;
    QLabel *lblProfileUsernameValue;
    QLabel *lblProfileBioValue;
    QPushButton *btnEditProfile;
    QPushButton *btnDeleteProfile;
    QPushButton *btnBackToDashboard;

    // --- Collection Page ---
    QWidget *collectionPage;
    QLabel *lblCollectionTitle;
    QWidget *songsContainer;
    QVBoxLayout *songsLayout;
    QScrollArea *songsScrollArea;
    QPushButton *btnBackFromCollection;
    QPushButton *btnEditAlbum;
    QPushButton *btnDeleteAlbum;

    // --- Playlists Page ---
    QWidget *playlistsPage;
    QListWidget *playlistsListWidget;
    QPushButton *btnBackFromPlaylists;
    QPushButton *btnAddPlaylist;

    // --- Playlist Songs Page ---
    QWidget *playlistSongsPage;
    QLabel *lblPlaylistSongsTitle;
    QWidget *playlistSongsContainer;
    QVBoxLayout *playlistSongsLayout;
    QScrollArea *playlistSongsScrollArea;
    QPushButton *btnBackFromPlaylistSongs;
    QPushButton *btnEditPlaylist;
    QPushButton *btnDeletePlaylist;

    // --- Artist Browser Page ---
    QWidget *artistBrowserPage;
    QWidget *artistBrowserContainer;
    QVBoxLayout *artistBrowserLayout;
    QPushButton *btnBackFromArtistBrowser;

    // --- Artist Albums Page ---
    QWidget *artistAlbumsPage;
    QLabel *lblArtistAlbumsTitle;
    QWidget *artistAlbumsContainer;
    QVBoxLayout *artistAlbumsLayout;
    QPushButton *btnBackFromArtistAlbums;

    // --- Artist Songs Page ---
    QWidget *artistSongsPage;
    QLabel *lblArtistSongsTitle;
    QWidget *artistSongsContainer;
    QVBoxLayout *artistSongsLayout;
    QPushButton *btnBackFromArtistSongs;

    // --- State ---
    int currentAlbumId;
    int currentPlaylistId = -1;
    QString currentPlaylistName;
    bool currentPlaylistIsFavorite = false;

    int currentSelectedArtistId = -1;
    QString currentSelectedArtistName;
    int currentSelectedAlbumId = -1;
    QString currentSelectedAlbumTitle;

    QWidget *listenerProfilePage = nullptr;

    QLineEdit *listenerProfileFullNameEdit = nullptr;
    QLineEdit *listenerProfileUsernameEdit = nullptr;
    QTextEdit *listenerProfileBiographyEdit=nullptr;
    QLineEdit *listenerProfilePasswordEdit = nullptr;

    QPushButton *btnEditListenerProfile = nullptr;
    QPushButton *btnDeleteListenerProfile = nullptr;
    QPushButton *btnBackFromListenerProfile = nullptr;
};

#endif // MAINWINDOW_H