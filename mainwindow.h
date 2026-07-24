#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QWidget>
#include <QScrollArea>
#include <QStringList>

#include "Controller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showLoginPage();
    void showSignUpPage();
    void showWelcomePage();
    void showArtistDashboardPage();
    void showArtistProfilePage();
    void showCollectionPage();

    void handleLogin();
    void handleSignUp();
    void handleDeleteProfile();

    void handleSinglesClicked();
    void handleAlbum1Clicked();
    void handleAlbum2Clicked();
    void handleAlbum3Clicked();

private:
    QStackedWidget *stackedWidget;

    // Welcome Page
    QWidget *welcomePage;
    QRadioButton *rbWelcomeLogin;
    QRadioButton *rbWelcomeSignUp;

    // Login Page
    QWidget *loginPage;
    QLineEdit *txtLoginUser;
    QLineEdit *txtLoginPass;

    // Sign Up Page
    QWidget *signUpPage;
    QLineEdit *txtSignFull;
    QLineEdit *txtSignUser;
    QLineEdit *txtSignPass;
    QLineEdit *txtSignBio;
    QRadioButton *rbSignListener;
    QRadioButton *rbSignArtist;

    // Artist Dashboard Page
    QWidget *artistDashboardPage;
    QPushButton *btnArtistName;
    QPushButton *btnSingles;
    QPushButton *btnAlbum1;
    QPushButton *btnAlbum2;
    QPushButton *btnAlbum3;
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

    // Collection Page (Singles / Album Songs)
    QWidget *collectionPage;
    QLabel *lblCollectionTitle;
    QWidget *songsContainer;
    QVBoxLayout *songsLayout;
    QScrollArea *songsScrollArea;
    QPushButton *btnBackFromCollection;

    // Helper functions
    void createWelcomePage();
    void createLoginPage();
    void createSignUpPage();
    void createArtistDashboardPage();
    void createArtistProfilePage();
    void createCollectionPage();

    void loadCollectionPage(const QString &title, const QStringList &songs);
    void clearSongsList();
    QPushButton* createSongItemButton(const QString &songTitle);
};

#endif // MAINWINDOW_H


