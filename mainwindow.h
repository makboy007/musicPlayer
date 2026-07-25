#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QStringList>
#include <QList>

#include <optional>
#include <vector>

#include "Song.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Pages
    QStackedWidget *stackedWidget = nullptr;
    QWidget *welcomePage = nullptr;
    QWidget *loginPage = nullptr;
    QWidget *signUpPage = nullptr;
    QWidget *artistDashboardPage = nullptr;
    QWidget *artistProfilePage = nullptr;
    QWidget *collectionPage = nullptr;

    // Welcome Page
    QRadioButton *rbWelcomeSignUp = nullptr;
    QRadioButton *rbWelcomeLogin = nullptr;

    // Login Page
    QLineEdit *txtLoginUser = nullptr;
    QLineEdit *txtLoginPass = nullptr;

    // Sign Up Page
    QRadioButton *rbSignListener = nullptr;
    QRadioButton *rbSignArtist = nullptr;
    QLineEdit *txtSignFull = nullptr;
    QLineEdit *txtSignUser = nullptr;
    QLineEdit *txtSignPass = nullptr;
    QLineEdit *txtSignBio = nullptr;

    // Artist Dashboard
    QPushButton *btnArtistName = nullptr;
    QPushButton *btnSingles = nullptr;
    QPushButton *btnAddSong = nullptr;
    QPushButton *btnAddAlbum = nullptr;
    QPushButton *btnLogoutArtist = nullptr;

    QVBoxLayout *albumsLayout = nullptr;
    QWidget *albumsContainer = nullptr;

    // Artist Profile
    QLabel *lblProfileFullNameValue = nullptr;
    QLabel *lblProfileUsernameValue = nullptr;
    QLabel *lblProfileBioValue = nullptr;
    QPushButton *btnEditProfile = nullptr;
    QPushButton *btnDeleteProfile = nullptr;
    QPushButton *btnBackToDashboard = nullptr;

    // Collection Page
    QLabel *lblCollectionTitle = nullptr;
    QWidget *songsContainer = nullptr;
    QVBoxLayout *songsLayout = nullptr;
    QScrollArea *songsScrollArea = nullptr;
    QPushButton *btnBackFromCollection = nullptr;
    QPushButton *btnEditAlbum = nullptr;
    QPushButton *btnDeleteAlbum = nullptr;

private:
    // Page creators
    void createWelcomePage();
    void createLoginPage();
    void createSignUpPage();
    void createArtistDashboardPage();
    void createArtistProfilePage();
    void createCollectionPage();

    // Navigation
    void showWelcomePage();
    void showLoginPage();
    void showSignUpPage();
    void showArtistDashboardPage();
    void showArtistProfilePage();
    void showCollectionPage();

    // Collection helpers
    void clearSongsList();
    QPushButton* createSongItemButton(const QString &songTitle, int songID);
    void loadCollectionPage(const QString &title, const std::vector<Song> &songs);

    // Dashboard helpers
    void clearAlbumsList();
    QPushButton* createAlbumItemButton(const QString &albumTitle, int albumId);
    void refreshArtistDashboard();

    // Handlers
    void handleLogin();
    void handleSignUp();
    void handleDeleteProfile();

    void handleAddAlbum();
    void handleAddSong();
    void handleSinglesClicked();
    void handleAlbumClicked(int albumId, const QString &albumTitle);
    void handleDeleteAlbum();
    void handleEditAlbum();

    void onAlbumButtonClicked();
    void onSongButtonClicked();
    void handleSongClicked(int songID);
    void handleEditSong(const Song &song);

private:
    int currentAlbumId = -1;
};

#endif // MAINWINDOW_H





