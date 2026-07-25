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
    QPushButton *btnEditAlbum = nullptr;   // دکمه ویرایش آلبوم
    QPushButton *btnDeleteAlbum = nullptr; // دکمه حذف آلبوم

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
    QPushButton* createSongItemButton(const QString &songTitle);
    void loadCollectionPage(const QString &title, const QStringList &songs);

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
    void handleDeleteAlbum(); // هندلر حذف آلبوم
    void handleEditAlbum();   // هندلر ویرایش آلبوم

    // Dynamic slot for album buttons
    void onAlbumButtonClicked();

private:
    int currentAlbumId = -1; // نگه داشتن آیدی آلبومِ فعال
};

#endif // MAINWINDOW_H




