#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <vector>

#include "Song.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Navigation
    void showWelcomePage();
    void showLoginPage();
    void showSignUpPage();
    void showArtistDashboardPage();
    void showArtistProfilePage();
    void showCollectionPage();

    // Main handlers
    void handleLogin();
    void handleSignUp();
    void handleAddAlbum();
    void handleAddSong();
    void handleSinglesClicked();
    void handleEditAlbum();
    void handleDeleteAlbum();
    void handleEditProfile();
    void handleDeleteProfile();

    // Click handlers
    void onAlbumButtonClicked();
    void onSongButtonClicked();

private:
    QStackedWidget *stackedWidget;

    // Welcome Page
    QWidget *welcomePage;
    QRadioButton *rbWelcomeSignUp;
    QRadioButton *rbWelcomeLogin;

    // Login Page
    QWidget *loginPage;
    QLineEdit *txtLoginUser;
    QLineEdit *txtLoginPass;

    // Sign Up Page
    QWidget *signUpPage;
    QRadioButton *rbSignListener;
    QRadioButton *rbSignArtist;
    QLineEdit *txtSignFull;
    QLineEdit *txtSignUser;
    QLineEdit *txtSignPass;
    QLineEdit *txtSignBio;

    // Artist Dashboard Page
    QWidget *artistDashboardPage;
    QPushButton *btnArtistName;
    QPushButton *btnSingles;
    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;
    QPushButton *btnAddSong;
    QPushButton *btnAddAlbum;
    QPushButton *btnLogoutArtist;

    // Artist Profile Page
    QWidget *artistProfilePage;
    QLabel *lblProfileFullNameValue;
    QLabel *lblProfileUsernameValue;
    QLabel *lblProfileBioValue;
    QPushButton *btnEditProfile;
    QPushButton *btnDeleteProfile;
    QPushButton *btnBackToDashboard;

    // Collection Page
    QWidget *collectionPage;
    QLabel *lblCollectionTitle;
    QScrollArea *songsScrollArea;
    QWidget *songsContainer;
    QVBoxLayout *songsLayout;
    QPushButton *btnBackFromCollection;
    QPushButton *btnEditAlbum;
    QPushButton *btnDeleteAlbum;

    // State
    int currentAlbumId;

    // Page builders
    void createWelcomePage();
    void createLoginPage();
    void createSignUpPage();
    void createArtistDashboardPage();
    void createArtistProfilePage();
    void createCollectionPage();

    // Dashboard / Collection helpers
    void refreshArtistDashboard();
    void clearAlbumsList();
    void clearSongsList();
    void loadCollectionPage(const QString &title, const std::vector<Song> &songs);

    // Item actions
    void handleAlbumClicked(int albumId, const QString &albumTitle);
    void handleSongClicked(int songID);
    void handleEditSong(const Song& song);

    // UI item factories
    QPushButton* createAlbumItemButton(const QString &albumTitle, int albumId);
    QPushButton* createSongItemButton(const QString &songTitle, int songID);
};

#endif // MAINWINDOW_H



