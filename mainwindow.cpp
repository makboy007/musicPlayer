#include "mainwindow.h"
#include "Controller.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"
#include "Listener.h"
#include "Playlist.h"

#include <QMessageBox>
#include <QApplication>
#include <QSpacerItem>
#include <QInputDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QDate>
#include <QDialogButtonBox>
#include <QScrollArea>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QRadioButton>
#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>

// --- Constructor ---
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentAlbumId(-1), currentPlaylistId(-1) {
    setWindowTitle("Music App");
    resize(500, 500);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    createWelcomePage();
    createLoginPage();
    createSignUpPage();
    createArtistDashboardPage();
    createArtistProfilePage();
    createCollectionPage();
    createListenerDashboardPage();
    createListenerProfilePage();

    // pages for listener playlists
    createPlaylistsPage();
    createPlaylistSongsPage();

    // pages for artist browser (newly added)
    createArtistBrowserPage();
    createArtistAlbumsPage();
    createArtistSongsPage();

    stackedWidget->addWidget(welcomePage);
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(signUpPage);
    stackedWidget->addWidget(artistDashboardPage);
    stackedWidget->addWidget(artistProfilePage);
    stackedWidget->addWidget(collectionPage);
    stackedWidget->addWidget(listenerDashboardPage);
    stackedWidget->addWidget(listenerProfilePage);
    stackedWidget->addWidget(playlistsPage);
    stackedWidget->addWidget(playlistSongsPage);

    // add newly created pages to stacked widget
    stackedWidget->addWidget(artistBrowserPage);
    stackedWidget->addWidget(artistAlbumsPage);
    stackedWidget->addWidget(artistSongsPage);

    showWelcomePage();
}

MainWindow::~MainWindow() {}


// --- Welcome Page ---
void MainWindow::createWelcomePage() {
    welcomePage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(welcomePage);
    layout->setContentsMargins(50, 50, 50, 50);

    QLabel *lblWelcome = new QLabel("Welcome to the world of music.", welcomePage);
    lblWelcome->setStyleSheet("color: red; font-size: 18px; font-weight: bold;");
    lblWelcome->setAlignment(Qt::AlignCenter);

    QHBoxLayout *radioLayout = new QHBoxLayout();
    rbWelcomeSignUp = new QRadioButton("Sign up", welcomePage);
    rbWelcomeLogin = new QRadioButton("Log in", welcomePage);
    radioLayout->addWidget(rbWelcomeSignUp);
    radioLayout->addWidget(rbWelcomeLogin);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnExit = new QPushButton("Exit", welcomePage);
    QPushButton *btnNext = new QPushButton("Next", welcomePage);
    btnLayout->addWidget(btnExit);
    btnLayout->addStretch();
    btnLayout->addWidget(btnNext);

    layout->addWidget(lblWelcome);
    layout->addLayout(radioLayout);
    layout->addStretch();
    layout->addLayout(btnLayout);

    connect(btnExit, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(btnNext, &QPushButton::clicked, this, [this]() {
        if (rbWelcomeLogin->isChecked())
            showLoginPage();
        else if (rbWelcomeSignUp->isChecked())
            showSignUpPage();
        else
            QMessageBox::warning(this, "Wait", "Please select an option.");
    });
}


// --- Login Page ---
void MainWindow::createLoginPage() {
    loginPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(loginPage);

    txtLoginUser = new QLineEdit(loginPage);
    txtLoginUser->setPlaceholderText("user name:");

    txtLoginPass = new QLineEdit(loginPage);
    txtLoginPass->setPlaceholderText("password:");
    txtLoginPass->setEchoMode(QLineEdit::Password);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnExit = new QPushButton("Exit", loginPage);
    QPushButton *btnBack = new QPushButton("Back", loginPage);
    QPushButton *btnLogin = new QPushButton("Log in", loginPage);

    btnLayout->addWidget(btnExit);
    btnLayout->addWidget(btnBack);
    btnLayout->addStretch();
    btnLayout->addWidget(btnLogin);

    layout->addWidget(new QLabel("user name:"));
    layout->addWidget(txtLoginUser);
    layout->addWidget(new QLabel("password:"));
    layout->addWidget(txtLoginPass);
    layout->addStretch();
    layout->addLayout(btnLayout);

    connect(btnExit, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(btnBack, &QPushButton::clicked, this, &MainWindow::showWelcomePage);
    connect(btnLogin, &QPushButton::clicked, this, &MainWindow::handleLogin);
}


// --- Sign Up Page ---
void MainWindow::createSignUpPage() {
    signUpPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(signUpPage);

    QLabel *lblHead = new QLabel("you are:", signUpPage);
    rbSignListener = new QRadioButton("listener", signUpPage);
    rbSignArtist = new QRadioButton("artist", signUpPage);

    txtSignFull = new QLineEdit(signUpPage);
    txtSignUser = new QLineEdit(signUpPage);
    txtSignPass = new QLineEdit(signUpPage);
    txtSignPass->setEchoMode(QLineEdit::Password);
    txtSignBio = new QLineEdit(signUpPage);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnExit = new QPushButton("Exit", signUpPage);
    QPushButton *btnBack = new QPushButton("Back", signUpPage);
    QPushButton *btnSign = new QPushButton("Sign up", signUpPage);

    btnLayout->addWidget(btnExit);
    btnLayout->addWidget(btnBack);
    btnLayout->addStretch();
    btnLayout->addWidget(btnSign);

    layout->addWidget(lblHead);
    layout->addWidget(rbSignListener);
    layout->addWidget(rbSignArtist);
    layout->addWidget(new QLabel("FullName:"));
    layout->addWidget(txtSignFull);
    layout->addWidget(new QLabel("UserName:"));
    layout->addWidget(txtSignUser);
    layout->addWidget(new QLabel("Password:"));
    layout->addWidget(txtSignPass);
    layout->addWidget(new QLabel("Biography:"));
    layout->addWidget(txtSignBio);
    layout->addStretch();
    layout->addLayout(btnLayout);

    connect(btnExit, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(btnBack, &QPushButton::clicked, this, &MainWindow::showWelcomePage);
    connect(btnSign, &QPushButton::clicked, this, &MainWindow::handleSignUp);
}


// --- Artist Dashboard Page ---
void MainWindow::createArtistDashboardPage() {
    artistDashboardPage = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(artistDashboardPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QHBoxLayout *topLayout = new QHBoxLayout();

    btnArtistName = new QPushButton("Artist Name", artistDashboardPage);
    btnArtistName->setCursor(Qt::PointingHandCursor);
    btnArtistName->setStyleSheet(
        "QPushButton {"
        " border: none;"
        " color: #1E90FF;"
        " font-size: 16px;"
        " font-weight: bold;"
        " text-align: left;"
        " padding: 0px;"
        "}"
        "QPushButton:hover {"
        " color: #0b72d0;"
        " text-decoration: underline;"
        "}"
        );

    topLayout->addWidget(btnArtistName);
    topLayout->addStretch();

    btnSingles = new QPushButton("Singles", artistDashboardPage);
    btnSingles->setMinimumHeight(45);
    btnSingles->setStyleSheet(
        "QPushButton { text-align: left; padding-left: 12px; font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
        "QPushButton:hover { background-color: #f2f2f2; }"
        );

    albumsContainer = new QWidget(artistDashboardPage);
    albumsLayout = new QVBoxLayout(albumsContainer);
    albumsLayout->setSpacing(10);
    albumsLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();

    btnAddSong = new QPushButton("Add Song", artistDashboardPage);
    btnAddAlbum = new QPushButton("Add Album", artistDashboardPage);
    btnLogoutArtist = new QPushButton("Logout", artistDashboardPage);

    btnAddSong->setMinimumWidth(100);
    btnAddAlbum->setMinimumWidth(100);
    btnLogoutArtist->setMinimumWidth(100);

    bottomLayout->addWidget(btnAddSong);
    bottomLayout->addWidget(btnAddAlbum);
    bottomLayout->addWidget(btnLogoutArtist);
    bottomLayout->addStretch();

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(btnSingles);
    mainLayout->addWidget(albumsContainer);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    connect(btnArtistName, &QPushButton::clicked, this, &MainWindow::showArtistProfilePage);
    connect(btnLogoutArtist, &QPushButton::clicked, this, &MainWindow::showWelcomePage);
    connect(btnSingles, &QPushButton::clicked, this, &MainWindow::handleSinglesClicked);
    connect(btnAddAlbum, &QPushButton::clicked, this, &MainWindow::handleAddAlbum);
    connect(btnAddSong, &QPushButton::clicked, this, &MainWindow::handleAddSong);

    refreshArtistDashboard();
}

// --- Listener Dashboard Page ---
void MainWindow::createListenerDashboardPage() {
    listenerDashboardPage = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(listenerDashboardPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QHBoxLayout *topLayout = new QHBoxLayout();

    btnListenerName = new QPushButton("Listener Name", listenerDashboardPage);
    btnListenerName->setCursor(Qt::PointingHandCursor);
    btnListenerName->setStyleSheet(
        "QPushButton {"
        " border: none;"
        " color: #1E90FF;"
        " font-size: 16px;"
        " font-weight: bold;"
        " text-align: left;"
        " padding: 0px;"
        "}"
        "QPushButton:hover {"
        " color: #0b72d0;"
        " text-decoration: underline;"
        "}"
        );

    topLayout->addWidget(btnListenerName);
    topLayout->addStretch();

    QLabel *lblTitle = new QLabel("Listener Dashboard", listenerDashboardPage);
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size: 20px; font-weight: bold;");

    btnBrowseArtists = new QPushButton("Browse Artists", listenerDashboardPage);
    btnBrowseArtists->setMinimumHeight(45);
    btnBrowseArtists->setStyleSheet(
        "QPushButton { text-align: left; padding-left: 12px; font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
        "QPushButton:hover { background-color: #f2f2f2; }"
        );

    btnMyPlaylists = new QPushButton("My Playlists", listenerDashboardPage);
    btnMyPlaylists->setMinimumHeight(45);
    btnMyPlaylists->setStyleSheet(
        "QPushButton { text-align: left; padding-left: 12px; font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
        "QPushButton:hover { background-color: #f2f2f2; }"
        );

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();

    btnLogoutListener = new QPushButton("Logout", listenerDashboardPage);
    btnLogoutListener->setMinimumWidth(100);

    bottomLayout->addWidget(btnLogoutListener);
    bottomLayout->addStretch();

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(lblTitle);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(btnBrowseArtists);
    mainLayout->addWidget(btnMyPlaylists);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    connect(btnLogoutListener, &QPushButton::clicked, this, &MainWindow::showWelcomePage);
    connect(btnMyPlaylists, &QPushButton::clicked, this, &MainWindow::showPlaylistsPage);
    connect(btnBrowseArtists, &QPushButton::clicked, this, &MainWindow::showArtistBrowserPage);
    connect(btnListenerName, &QPushButton::clicked,this, &MainWindow::showListenerProfilePage);
}

void MainWindow::createListenerProfilePage()
{
    listenerProfilePage = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(listenerProfilePage);

    QLabel *title = new QLabel("Listener Profile");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 22px; font-weight: bold; margin-bottom: 15px;");

    QFormLayout *formLayout = new QFormLayout;

    listenerProfileFullNameEdit = new QLineEdit;
    listenerProfileUsernameEdit = new QLineEdit;
    listenerProfileBiographyEdit = new QTextEdit;
    listenerProfilePasswordEdit = new QLineEdit;

    listenerProfileBiographyEdit->setPlaceholderText("Enter biography...");
    listenerProfileBiographyEdit->setFixedHeight(100);

    listenerProfilePasswordEdit->setEchoMode(QLineEdit::Normal); // طبق ترجیح فعلی پروژه

    formLayout->addRow("Full Name:", listenerProfileFullNameEdit);
    formLayout->addRow("Username:", listenerProfileUsernameEdit);
    formLayout->addRow("Biography:", listenerProfileBiographyEdit);
    formLayout->addRow("Password:", listenerProfilePasswordEdit);

    QPushButton *saveBtn = new QPushButton("Save Changes");
    QPushButton *deleteBtn = new QPushButton("Delete Account");
    QPushButton *backBtn = new QPushButton("Back");

    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::handleEditListenerProfile);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteListenerProfile);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::showListenerDashboardPage);

    mainLayout->addWidget(title);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(deleteBtn);
    mainLayout->addWidget(backBtn);
}


// --- Artist Profile Page ---
void MainWindow::createArtistProfilePage() {
    artistProfilePage = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(artistProfilePage);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(15);

    QLabel *lblTitle = new QLabel("Artist Profile", artistProfilePage);
    lblTitle->setStyleSheet("font-size: 20px; font-weight: bold;");
    lblTitle->setAlignment(Qt::AlignCenter);

    QLabel *lblFullNameTitle = new QLabel("Full Name:", artistProfilePage);
    lblProfileFullNameValue = new QLabel("Artist", artistProfilePage);

    QLabel *lblUsernameTitle = new QLabel("Username:", artistProfilePage);
    lblProfileUsernameValue = new QLabel("artist123", artistProfilePage);

    QLabel *lblBioTitle = new QLabel("Biography:", artistProfilePage);
    lblProfileBioValue = new QLabel("Biography", artistProfilePage);
    lblProfileBioValue->setWordWrap(true);

    lblFullNameTitle->setStyleSheet("font-weight: bold;");
    lblUsernameTitle->setStyleSheet("font-weight: bold;");
    lblBioTitle->setStyleSheet("font-weight: bold;");

    btnEditProfile = new QPushButton("Edit Profile", artistProfilePage);
    btnDeleteProfile = new QPushButton("Delete Profile", artistProfilePage);
    btnBackToDashboard = new QPushButton("Back", artistProfilePage);

    btnEditProfile->setMinimumHeight(40);
    btnDeleteProfile->setMinimumHeight(40);
    btnBackToDashboard->setMinimumHeight(40);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(btnBackToDashboard);
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnEditProfile);
    bottomLayout->addWidget(btnDeleteProfile);

    mainLayout->addWidget(lblTitle);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(lblFullNameTitle);
    mainLayout->addWidget(lblProfileFullNameValue);
    mainLayout->addWidget(lblUsernameTitle);
    mainLayout->addWidget(lblProfileUsernameValue);
    mainLayout->addWidget(lblBioTitle);
    mainLayout->addWidget(lblProfileBioValue);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    connect(btnBackToDashboard, &QPushButton::clicked, this, &MainWindow::showArtistDashboardPage);
    connect(btnEditProfile, &QPushButton::clicked, this, &MainWindow::handleEditProfile);
    connect(btnDeleteProfile, &QPushButton::clicked, this, &MainWindow::handleDeleteProfile);
}


// --- Collection Page ---
void MainWindow::createCollectionPage() {
    collectionPage = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(collectionPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    lblCollectionTitle = new QLabel("Collection", collectionPage);
    lblCollectionTitle->setStyleSheet("font-size: 18px; font-weight: bold;");
    lblCollectionTitle->setAlignment(Qt::AlignLeft);

    songsContainer = new QWidget(collectionPage);
    songsLayout = new QVBoxLayout(songsContainer);
    songsLayout->setSpacing(10);
    songsLayout->setContentsMargins(0, 0, 0, 0);

    songsScrollArea = new QScrollArea(collectionPage);
    songsScrollArea->setWidgetResizable(true);
    songsScrollArea->setWidget(songsContainer);
    songsScrollArea->setFrameShape(QFrame::NoFrame);

    btnBackFromCollection = new QPushButton("Back", collectionPage);
    btnBackFromCollection->setMinimumHeight(40);
    btnBackFromCollection->setMinimumWidth(90);

    btnEditAlbum = new QPushButton("Edit Album", collectionPage);
    btnEditAlbum->setMinimumHeight(40);
    btnEditAlbum->setMinimumWidth(90);

    btnDeleteAlbum = new QPushButton("Delete Album", collectionPage);
    btnDeleteAlbum->setMinimumHeight(40);
    btnDeleteAlbum->setMinimumWidth(90);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(btnBackFromCollection);
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnEditAlbum);
    bottomLayout->addWidget(btnDeleteAlbum);

    mainLayout->addWidget(lblCollectionTitle);
    mainLayout->addWidget(songsScrollArea);
    mainLayout->addLayout(bottomLayout);

    connect(btnBackFromCollection, &QPushButton::clicked, this, &MainWindow::showArtistDashboardPage);
    connect(btnDeleteAlbum, &QPushButton::clicked, this, &MainWindow::handleDeleteAlbum);
    connect(btnEditAlbum, &QPushButton::clicked, this, &MainWindow::handleEditAlbum);
}


// --- Playlists Page ---
void MainWindow::createPlaylistsPage() {
    playlistsPage = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(playlistsPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QLabel *lblTitle = new QLabel("My Playlists", playlistsPage);
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size: 20px; font-weight: bold;");

    playlistsListWidget = new QListWidget(playlistsPage);
    playlistsListWidget->setStyleSheet(
        "QListWidget { font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
        "QListWidget::item { padding: 10px; }"
        "QListWidget::item:selected { background-color: #dbeafe; color: black; }"
        );

    btnBackFromPlaylists = new QPushButton("Back", playlistsPage);
    btnAddPlaylist = new QPushButton("Add Playlist", playlistsPage);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(btnBackFromPlaylists);
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnAddPlaylist);

    mainLayout->addWidget(lblTitle);
    mainLayout->addWidget(playlistsListWidget);
    mainLayout->addLayout(bottomLayout);

    connect(btnBackFromPlaylists, &QPushButton::clicked, this, &MainWindow::showListenerDashboardPage);

    connect(btnAddPlaylist, &QPushButton::clicked, this, [this]() {
        bool ok;
        QString playlistName = QInputDialog::getText(
            this,
            "Add Playlist",
            "Enter playlist name:",
            QLineEdit::Normal,
            "",
            &ok
            );

        playlistName = playlistName.trimmed();

        if (!ok) return;

        if (playlistName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Playlist name cannot be empty.");
            return;
        }

        if (Controller::getInstance().addMyPlaylist(playlistName.toStdString())) {
            QMessageBox::information(this, "Success", "Playlist created successfully.");
            loadPlaylists();
        } else {
            QMessageBox::warning(this, "Error", "Failed to create playlist.");
        }
    });

    connect(playlistsListWidget, &QListWidget::itemClicked, this, &MainWindow::onPlaylistItemClicked);
}


// --- Playlist Songs Page ---
void MainWindow::createPlaylistSongsPage() {
    playlistSongsPage = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(playlistSongsPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    lblPlaylistSongsTitle = new QLabel("Playlist", playlistSongsPage);
    lblPlaylistSongsTitle->setAlignment(Qt::AlignLeft);
    lblPlaylistSongsTitle->setStyleSheet("font-size: 18px; font-weight: bold;");

    playlistSongsContainer = new QWidget(playlistSongsPage);
    playlistSongsLayout = new QVBoxLayout(playlistSongsContainer);
    playlistSongsLayout->setSpacing(10);
    playlistSongsLayout->setContentsMargins(0, 0, 0, 0);

    playlistSongsScrollArea = new QScrollArea(playlistSongsPage);
    playlistSongsScrollArea->setWidgetResizable(true);
    playlistSongsScrollArea->setWidget(playlistSongsContainer);
    playlistSongsScrollArea->setFrameShape(QFrame::NoFrame);

    btnBackFromPlaylistSongs = new QPushButton("Back", playlistSongsPage);
    btnEditPlaylist = new QPushButton("Edit Playlist", playlistSongsPage);
    btnDeletePlaylist = new QPushButton("Delete Playlist", playlistSongsPage);

    btnBackFromPlaylistSongs->setMinimumHeight(40);
    btnEditPlaylist->setMinimumHeight(40);
    btnDeletePlaylist->setMinimumHeight(40);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(btnBackFromPlaylistSongs);
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnEditPlaylist);
    bottomLayout->addWidget(btnDeletePlaylist);

    mainLayout->addWidget(lblPlaylistSongsTitle);
    mainLayout->addWidget(playlistSongsScrollArea);
    mainLayout->addLayout(bottomLayout);

    connect(btnBackFromPlaylistSongs, &QPushButton::clicked, this, &MainWindow::showPlaylistsPage);

    connect(btnDeletePlaylist, &QPushButton::clicked, this, [this]() {
        if (currentPlaylistIsFavorite || currentPlaylistId == -1)
            return;

        auto reply = QMessageBox::question(
            this,
            "Delete Playlist",
            "Are you sure you want to delete this playlist?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            if (Controller::getInstance().removePlaylist(currentPlaylistId)) {
                QMessageBox::information(this, "Success", "Playlist deleted successfully.");
                showPlaylistsPage();
            } else {
                QMessageBox::warning(this, "Error", "Failed to delete playlist.");
            }
        }
    });

    connect(btnEditPlaylist, &QPushButton::clicked, this, [this]() {
        if (currentPlaylistIsFavorite || currentPlaylistId == -1)
            return;

        bool ok;
        QString newName = QInputDialog::getText(
            this,
            "Edit Playlist",
            "Enter new playlist name:",
            QLineEdit::Normal,
            lblPlaylistSongsTitle->text(),
            &ok
            );

        newName = newName.trimmed();

        if (!ok || newName.isEmpty())
            return;

        if (Controller::getInstance().editPlaylist(currentPlaylistId, newName.toStdString())) {
            QMessageBox::information(this, "Success", "Playlist updated successfully.");
            currentPlaylistName = newName;
            loadPlaylistSongsPage(currentPlaylistId, currentPlaylistName, false);
        } else {
            QMessageBox::warning(this, "Error", "Failed to update playlist.");
        }
    });
}


// --- Navigation ---
void MainWindow::showWelcomePage() {
    stackedWidget->setCurrentWidget(welcomePage);
}

void MainWindow::showLoginPage() {
    stackedWidget->setCurrentWidget(loginPage);
}

void MainWindow::showSignUpPage() {
    stackedWidget->setCurrentWidget(signUpPage);
}

void MainWindow::showArtistDashboardPage() {
    refreshArtistDashboard();
    stackedWidget->setCurrentWidget(artistDashboardPage);
}

void MainWindow::showListenerDashboardPage() {
    Listener* currentListener = Controller::getInstance().getCurrentListener();
    if (currentListener != nullptr) {
        btnListenerName->setText(QString::fromStdString(currentListener->getFullName()));
    }
    stackedWidget->setCurrentWidget(listenerDashboardPage);
}

void MainWindow::showListenerProfilePage()
{
    Listener *currentListener = Controller::getInstance().getCurrentListener();
    if (currentListener == nullptr) {
        QMessageBox::warning(this, "Error", "No listener is currently logged in.");
        return;
    }

    listenerProfileFullNameEdit->setText(QString::fromStdString(currentListener->getFullName()));
    listenerProfileUsernameEdit->setText(QString::fromStdString(currentListener->getUserName()));
    listenerProfileBiographyEdit->setPlainText(QString::fromStdString(currentListener->getBiography()));
    listenerProfilePasswordEdit->setText(QString::fromStdString(currentListener->getPassword()));

    stackedWidget->setCurrentWidget(listenerProfilePage);
}



void MainWindow::showArtistProfilePage() {
    Artist* currentArtist = Controller::getInstance().getCurrentAccount();
    if (currentArtist != nullptr) {
        lblProfileFullNameValue->setText(QString::fromStdString(currentArtist->getFullName()));
        lblProfileUsernameValue->setText(QString::fromStdString(currentArtist->getUserName()));
        lblProfileBioValue->setText(QString::fromStdString(currentArtist->getBiography()));

        btnArtistName->setText(QString::fromStdString(currentArtist->getFullName()));
    }

    stackedWidget->setCurrentWidget(artistProfilePage);
}

void MainWindow::showCollectionPage() {
    stackedWidget->setCurrentWidget(collectionPage);
}

void MainWindow::showPlaylistsPage() {
    loadPlaylists();
    stackedWidget->setCurrentWidget(playlistsPage);
}

void MainWindow::showPlaylistSongsPage() {
    stackedWidget->setCurrentWidget(playlistSongsPage);
}


// --- Collection Helpers ---
void MainWindow::clearSongsList() {
    QLayoutItem *item;
    while ((item = songsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }
}

QPushButton* MainWindow::createSongItemButton(const QString &songTitle, int songID) {
    QPushButton *btnSong = new QPushButton(songTitle, collectionPage);
    btnSong->setMinimumHeight(45);
    btnSong->setProperty("songID", songID);
    btnSong->setStyleSheet(
        "QPushButton { text-align: left; padding-left: 12px; font-size: 14px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
        "QPushButton:hover { background-color: #f2f2f2; }"
        );
    connect(btnSong, &QPushButton::clicked, this, &MainWindow::onSongButtonClicked);
    return btnSong;
}

void MainWindow::loadCollectionPage(const QString &title, const std::vector<Song> &songs) {
    lblCollectionTitle->setText(title);
    clearSongsList();

    if (songs.empty()) {
        QLabel *lblEmpty = new QLabel("No songs found.", collectionPage);
        lblEmpty->setStyleSheet("color: gray; font-style: italic;");
        songsLayout->addWidget(lblEmpty);
    } else {
        for (const Song &song : songs) {
            songsLayout->addWidget(createSongItemButton(
                QString::fromStdString(song.getName()),
                song.getSongID()
                ));
        }
    }

    songsLayout->addStretch();
    showCollectionPage();
}


// --- Playlist Helpers ---
void MainWindow::clearPlaylistSongsList() {
    QLayoutItem *item;
    while ((item = playlistSongsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }
}

QPushButton* MainWindow::createPlaylistSongItemButton(const QString &songTitle, int songID) {
    QPushButton *btnSong = new QPushButton(songTitle, playlistSongsPage);
    btnSong->setMinimumHeight(45);
    btnSong->setProperty("songID", songID);
    btnSong->setStyleSheet(
        "QPushButton { text-align: left; padding-left: 12px; font-size: 14px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
        "QPushButton:hover { background-color: #f2f2f2; }"
        );
    // Listeners can click songs to see details dialog
    connect(btnSong, &QPushButton::clicked, this, [this, songID]() {
        handleListenerSongClicked(songID);
    });
    return btnSong;
}

void MainWindow::loadPlaylists() {
    playlistsListWidget->clear();

    QListWidgetItem *favoriteItem = new QListWidgetItem("Favorite");
    favoriteItem->setData(Qt::UserRole, -1);
    playlistsListWidget->addItem(favoriteItem);

    auto playlistsOpt = Controller::getInstance().myPlaylist();
    if (!playlistsOpt.has_value())
        return;

    const std::vector<Playlist> &playlists = playlistsOpt.value();

    for (const Playlist &playlist : playlists) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(playlist.getName()));
        item->setData(Qt::UserRole, playlist.getListID());
        playlistsListWidget->addItem(item);
    }
}

void MainWindow::loadPlaylistSongsPage(int playlistId, const QString &playlistName, bool isFavorite) {
    currentPlaylistId = playlistId;
    currentPlaylistName = playlistName;
    currentPlaylistIsFavorite = isFavorite;

    lblPlaylistSongsTitle->setText(playlistName);

    btnEditPlaylist->setVisible(!isFavorite);
    btnDeletePlaylist->setVisible(!isFavorite);

    clearPlaylistSongsList();

    std::optional<std::vector<Song>> songsOpt;

    if (isFavorite)
        songsOpt = Controller::getInstance().myLikeSong();
    else
        songsOpt = Controller::getInstance().showSongsInPlaylist(playlistId);

    if (!songsOpt.has_value()) {
        QLabel *lblEmpty = new QLabel("No songs found.", playlistSongsPage);
        lblEmpty->setStyleSheet("color: gray; font-style: italic;");
        playlistSongsLayout->addWidget(lblEmpty);
        playlistSongsLayout->addStretch();
        showPlaylistSongsPage();
        return;
    }

    const std::vector<Song> &songs = songsOpt.value();

    if (songs.empty()) {
        QLabel *lblEmpty = new QLabel("No songs found.", playlistSongsPage);
        lblEmpty->setStyleSheet("color: gray; font-style: italic;");
        playlistSongsLayout->addWidget(lblEmpty);
    } else {
        for (const Song &song : songs) {
            playlistSongsLayout->addWidget(
                createPlaylistSongItemButton(
                    QString::fromStdString(song.getName()),
                    song.getSongID()
                    )
                );
        }
    }

    playlistSongsLayout->addStretch();
    showPlaylistSongsPage();
}

void MainWindow::onPlaylistItemClicked(QListWidgetItem *item) {
    if (!item) return;

    int playlistId = item->data(Qt::UserRole).toInt();
    QString playlistName = item->text();

    if (playlistId == -1)
        loadPlaylistSongsPage(-1, "Favorite", true);
    else
        loadPlaylistSongsPage(playlistId, playlistName, false);
}


// --- Dashboard Helpers ---
void MainWindow::clearAlbumsList() {
    QLayoutItem *item;
    while ((item = albumsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }
}

QPushButton* MainWindow::createAlbumItemButton(const QString &albumTitle, int albumId) {
    QPushButton *btnAlbum = new QPushButton(albumTitle, artistDashboardPage);
    btnAlbum->setMinimumHeight(45);
    btnAlbum->setProperty("albumId", albumId);
    btnAlbum->setProperty("albumTitle", albumTitle);
    btnAlbum->setStyleSheet(
        "QPushButton { text-align: left; padding-left: 12px; font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
        "QPushButton:hover { background-color: #f2f2f2; }"
        );

    connect(btnAlbum, &QPushButton::clicked, this, &MainWindow::onAlbumButtonClicked);
    return btnAlbum;
}

void MainWindow::refreshArtistDashboard() {
    clearAlbumsList();

    Artist* currentArtist = Controller::getInstance().getCurrentAccount();
    if (currentArtist != nullptr) {
        btnArtistName->setText(QString::fromStdString(currentArtist->getFullName()));
    } else {
        btnArtistName->setText("Artist Name");
    }

    auto albumsOpt = Controller::getInstance().myAlbums();

    if (!albumsOpt.has_value()) {
        albumsLayout->addStretch();
        return;
    }

    const std::vector<Album> &albums = albumsOpt.value();

    for (const Album &album : albums) {
        albumsLayout->addWidget(createAlbumItemButton(
            QString::fromStdString(album.getName()),
            album.getAlbumID()
            ));
    }

    albumsLayout->addStretch();
}

void MainWindow::onAlbumButtonClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int id = btn->property("albumId").toInt();
        QString title = btn->property("albumTitle").toString();
        handleAlbumClicked(id, title);
    }
}

void MainWindow::handleAlbumClicked(int albumId, const QString &albumTitle) {
    currentAlbumId = albumId;

    btnEditAlbum->setVisible(true);
    btnDeleteAlbum->setVisible(true);

    auto songsOpt = Controller::getInstance().showSongsInAlbum(albumId);
    std::vector<Song> songsList;
    if (songsOpt.has_value()) {
        songsList = songsOpt.value();
    }

    loadCollectionPage(albumTitle, songsList);
}

void MainWindow::handleSinglesClicked() {
    currentAlbumId = -1;

    btnEditAlbum->setVisible(false);
    btnDeleteAlbum->setVisible(false);

    auto songsOpt = Controller::getInstance().mySingleSong();
    std::vector<Song> songsList;
    if (songsOpt.has_value()) {
        songsList = songsOpt.value();
    }

    loadCollectionPage("Singles", songsList);
}


// --- Song Details, Edit & Delete Handlers ---
void MainWindow::onSongButtonClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int songID = btn->property("songID").toInt();
        handleSongClicked(songID);
    }
}

void MainWindow::handleSongClicked(int songID) {
    auto songOpt = Controller::getInstance().getSong(songID);
    if (!songOpt.has_value()) return;

    Song song = songOpt.value();

    QDialog dialog(this);
    dialog.setWindowTitle("Song Details");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    layout->addWidget(new QLabel("Name: " + QString::fromStdString(song.getName())));
    layout->addWidget(new QLabel("Year: " + QString::number(song.getReleaseYear())));
    layout->addWidget(new QLabel("Genre: " + QString::fromStdString(song.getGenre())));

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnEdit = new QPushButton("Edit");
    QPushButton *btnDelete = new QPushButton("Delete");
    QPushButton *btnClose = new QPushButton("Close");

    btnLayout->addWidget(btnEdit);
    btnLayout->addWidget(btnDelete);
    btnLayout->addWidget(btnClose);
    layout->addLayout(btnLayout);

    connect(btnClose, &QPushButton::clicked, &dialog, &QDialog::accept);

    connect(btnDelete, &QPushButton::clicked, [&]() {
        if (QMessageBox::question(this, "Delete", "Are you sure you want to delete this song?") == QMessageBox::Yes) {
            if (Controller::getInstance().removeSong(songID)) {
                QMessageBox::information(this, "Success", "Song deleted successfully.");
                dialog.accept();

                if (currentAlbumId == -1)
                    handleSinglesClicked();
                else
                    handleAlbumClicked(currentAlbumId, lblCollectionTitle->text());
            }
        }
    });

    connect(btnEdit, &QPushButton::clicked, [&]() {
        dialog.hide();
        handleEditSong(song);
        dialog.accept();
    });

    dialog.exec();
}

void MainWindow::handleEditSong(const Song& song) {
    QDialog dialog(this);
    dialog.setWindowTitle("Edit Song");

    QFormLayout *form = new QFormLayout(&dialog);

    QLineEdit *nameEdit = new QLineEdit(QString::fromStdString(song.getName()), &dialog);

    QSpinBox *yearEdit = new QSpinBox(&dialog);
    yearEdit->setRange(1900, 2100);
    yearEdit->setValue(song.getReleaseYear());

    QLineEdit *genreEdit = new QLineEdit(QString::fromStdString(song.getGenre()), &dialog);

    QComboBox *albumCombo = new QComboBox(&dialog);
    albumCombo->addItem("None (Single)", 0);

    auto albumsOpt = Controller::getInstance().myAlbums();
    if (albumsOpt.has_value()) {
        for (const auto &album : albumsOpt.value()) {
            albumCombo->addItem(QString::fromStdString(album.getName()), album.getAlbumID());
        }
    }

    int index = albumCombo->findData(song.getAlbumID());
    if (index != -1) albumCombo->setCurrentIndex(index);

    form->addRow("Song Name:", nameEdit);
    form->addRow("Release Year:", yearEdit);
    form->addRow("Genre:", genreEdit);
    form->addRow("Album:", albumCombo);

    QDialogButtonBox *buttonBox =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form->addRow(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        std::string newName = nameEdit->text().trimmed().toStdString();
        int newYear = yearEdit->value();
        std::string newGenre = genreEdit->text().trimmed().toStdString();
        int newAlbumID = albumCombo->currentData().toInt();

        if (newName.empty()) {
            QMessageBox::warning(this, "Error", "Song name cannot be empty.");
            return;
        }

        if (Controller::getInstance().editSong(song.getSongID(), newName, newYear, newGenre, newAlbumID)) {
            QMessageBox::information(this, "Success", "Song updated successfully.");

            if (currentAlbumId == -1)
                handleSinglesClicked();
            else
                handleAlbumClicked(currentAlbumId, lblCollectionTitle->text());
        }
    }
}


// --- Profile Handlers ---
void MainWindow::handleEditProfile()
{
    Artist* currentArtist = Controller::getInstance().getCurrentAccount();
    if (currentArtist == nullptr) {
        QMessageBox::warning(this, "Error", "No artist is currently logged in.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Edit Profile");

    QFormLayout *formLayout = new QFormLayout(&dialog);

    QLineEdit *fullNameEdit = new QLineEdit(
        QString::fromStdString(currentArtist->getFullName()), &dialog);

    QLineEdit *usernameEdit = new QLineEdit(
        QString::fromStdString(currentArtist->getUserName()), &dialog);

    QLineEdit *bioEdit = new QLineEdit(
        QString::fromStdString(currentArtist->getBiography()), &dialog);

    QLineEdit *passwordEdit = new QLineEdit(
        QString::fromStdString(currentArtist->getPassword()), &dialog);

    formLayout->addRow("Full Name:", fullNameEdit);
    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Biography:", bioEdit);
    formLayout->addRow("Password:", passwordEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    formLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString newFullName = fullNameEdit->text().trimmed();
        QString newUsername = usernameEdit->text().trimmed();
        QString newBio = bioEdit->text().trimmed();
        QString newPassword = passwordEdit->text().trimmed();

        if (newFullName.isEmpty() || newUsername.isEmpty() || newPassword.isEmpty()) {
            QMessageBox::warning(this, "Error", "Full Name, Username, and Password cannot be empty.");
            return;
        }

        bool result = Controller::getInstance().updateProfile(
            newFullName.toStdString(),
            newUsername.toStdString(),
            newBio.toStdString(),
            newPassword.toStdString()
            );

        if (result) {
            QMessageBox::information(this, "Success", "Profile updated successfully.");
            showArtistProfilePage();
        } else {
            QMessageBox::warning(this, "Error", "Profile update failed. Username may already exist.");
        }
    }
}

void MainWindow::handleEditListenerProfile()
{
    Listener *currentListener = Controller::getInstance().getCurrentListener();
    if (currentListener == nullptr) {
        QMessageBox::warning(this, "Error", "No listener is currently logged in.");
        return;
    }

    QString fullName = listenerProfileFullNameEdit->text().trimmed();
    QString username = listenerProfileUsernameEdit->text().trimmed();
    QString biography = listenerProfileBiographyEdit->toPlainText().trimmed();
    QString password = listenerProfilePasswordEdit->text();

    if (fullName.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Full name, username, and password are required.");
        return;
    }

    bool ok = Controller::getInstance().updateListenerProfile(
        fullName.toStdString(),
        username.toStdString(),
        biography.toStdString(),
        password.toStdString()
        );

    if (ok) {
        QMessageBox::information(this, "Success", "Listener profile updated successfully.");
        showListenerDashboardPage();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update listener profile.");
    }
}


void MainWindow::handleDeleteListenerProfile()
{
    Listener *currentListener = Controller::getInstance().getCurrentListener();
    if (currentListener == nullptr) {
        QMessageBox::warning(this, "Error", "No listener is currently logged in.");
        return;
    }

    auto reply = QMessageBox::question(
        this,
        "Delete Profile",
        "Are you sure you want to delete your listener profile?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes)
        return;

   bool ok = Controller::getInstance().removeListener();

    if (ok) {
        QMessageBox::information(this, "Deleted", "Listener profile deleted successfully.");
        txtLoginUser->clear();
        txtLoginPass->clear();
        showWelcomePage();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete listener profile.");
    }
}


// --- Other Handlers ---
void MainWindow::handleDeleteAlbum() {
    if (currentAlbumId == -1) return;

    auto reply = QMessageBox::question(
        this,
        "Delete Album",
        "Are you sure you want to delete this album?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        if (Controller::getInstance().removeAlbum(currentAlbumId)) {
            QMessageBox::information(this, "Success", "Album deleted successfully.");
            showArtistDashboardPage();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete album.");
        }
    }
}

void MainWindow::handleEditAlbum() {
    if (currentAlbumId == -1)
        return;

    bool ok;
    QString newTitle = QInputDialog::getText(
        this,
        "Edit Album",
        "Enter new Album Name:",
        QLineEdit::Normal,
        lblCollectionTitle->text(),
        &ok
        );

    newTitle = newTitle.trimmed();

    if (!ok || newTitle.isEmpty())
        return;

    bool result = Controller::getInstance().editAlbum(
        currentAlbumId,
        newTitle.toStdString()
        );

    if (result) {
        QMessageBox::information(this, "Success", "Album updated successfully.");
        lblCollectionTitle->setText(newTitle);
        refreshArtistDashboard();
        handleAlbumClicked(currentAlbumId, newTitle);
    } else {
        QMessageBox::warning(this, "Error", "Failed to update album.");
    }
}

void MainWindow::handleLogin() {
    QString user = txtLoginUser->text().trimmed();
    QString pass = txtLoginPass->text();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    if (Controller::getInstance().login(user.toStdString(), pass.toStdString())) {
        QMessageBox::information(this, "Success", "Welcome back!");

        if (Controller::getInstance().getCurrentListener() != nullptr) {
            showListenerDashboardPage();
        } else {
            showArtistDashboardPage();
        }
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid credentials.");
    }
}

void MainWindow::handleSignUp() {
    if (Controller::getInstance().signUp(
            txtSignFull->text().trimmed().toStdString(),
            txtSignUser->text().trimmed().toStdString(),
            txtSignPass->text().toStdString(),
            txtSignBio->text().trimmed().toStdString(),
            rbSignArtist->isChecked()
            )) {
        QMessageBox::information(this, "Success", "Account created successfully!");
        showLoginPage();
    } else {
        QMessageBox::critical(this, "Failed", "Username already exists.");
    }
}

void MainWindow::handleDeleteProfile() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Profile",
        "Are you sure you want to delete your profile?\nThis action cannot be undone.",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        bool result = Controller::getInstance().removeArtist();

        if (result) {
            QMessageBox::information(this, "Success", "Profile deleted successfully.");

            txtLoginUser->clear();
            txtLoginPass->clear();

            showWelcomePage();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete profile.");
        }
    }
}

void MainWindow::handleAddAlbum() {
    bool ok;
    QString albumName = QInputDialog::getText(
        this,
        "New Album",
        "Enter Album Name:",
        QLineEdit::Normal,
        "",
        &ok
        );

    albumName = albumName.trimmed();

    if (ok && !albumName.isEmpty()) {
        if (Controller::getInstance().addMyAlbum(albumName.toStdString())) {
            QMessageBox::information(this, "Success", "Album created successfully!");
            refreshArtistDashboard();
        } else {
            QMessageBox::warning(this, "Error", "Failed to create album.");
        }
    }
}

void MainWindow::handleAddSong() {
    QDialog dialog(this);
    dialog.setWindowTitle("Add New Song");

    QFormLayout *form = new QFormLayout(&dialog);

    QLineEdit *nameEdit = new QLineEdit(&dialog);

    QSpinBox *yearEdit = new QSpinBox(&dialog);
    yearEdit->setRange(1900, 2100);
    yearEdit->setValue(QDate::currentDate().year());

    QLineEdit *genreEdit = new QLineEdit(&dialog);

    QComboBox *albumCombo = new QComboBox(&dialog);
    albumCombo->addItem("None (Single)", 0);

    auto albumsOpt = Controller::getInstance().myAlbums();
    if (albumsOpt.has_value()) {
        for (const auto &album : albumsOpt.value()) {
            albumCombo->addItem(QString::fromStdString(album.getName()), album.getAlbumID());
        }
    }

    form->addRow("Song Name:", nameEdit);
    form->addRow("Release Year:", yearEdit);
    form->addRow("Genre:", genreEdit);
    form->addRow("Album:", albumCombo);

    QDialogButtonBox *buttonBox =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);

    form->addRow(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        const QString songName = nameEdit->text().trimmed();
        const QString genre = genreEdit->text().trimmed();
        const int year = yearEdit->value();
        const int albumId = albumCombo->currentData().toInt();

        if (songName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Song name cannot be empty.");
            return;
        }

        bool ok = Controller::getInstance().addmySong(
            songName.toStdString(),
            year,
            genre.toStdString(),
            albumId
            );

        if (ok) {
            QMessageBox::information(this, "Success", "Song added successfully.");
            refreshArtistDashboard();
        } else {
            QMessageBox::warning(this, "Error", "Failed to add song.");
        }
    }
}


// ============================================================================
// --- Artist Browser & Navigation Implementations (NEW SECTIONS) ------------
// ============================================================================

// --- 1. Artist Browser Page Creation ---
void MainWindow::createArtistBrowserPage() {
    artistBrowserPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(artistBrowserPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QLabel *lblTitle = new QLabel("Browse Artists", artistBrowserPage);
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size: 20px; font-weight: bold;");

    artistBrowserContainer = new QWidget(artistBrowserPage);
    artistBrowserLayout = new QVBoxLayout(artistBrowserContainer);
    artistBrowserLayout->setSpacing(10);
    artistBrowserLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scrollArea = new QScrollArea(artistBrowserPage);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(artistBrowserContainer);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    btnBackFromArtistBrowser = new QPushButton("Back", artistBrowserPage);
    btnBackFromArtistBrowser->setMinimumHeight(40);
    btnBackFromArtistBrowser->setMinimumWidth(100);
    bottomLayout->addWidget(btnBackFromArtistBrowser);
    bottomLayout->addStretch();

    mainLayout->addWidget(lblTitle);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(bottomLayout);

    connect(btnBackFromArtistBrowser, &QPushButton::clicked, this, &MainWindow::showListenerDashboardPage);
}

void MainWindow::showArtistBrowserPage() {
    // Clear layout
    QLayoutItem *item;
    while ((item = artistBrowserLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    auto artistsOpt = Controller::getInstance().showAllArtist();
    if (artistsOpt.has_value()) {
        const auto &artists = artistsOpt.value();
        if (artists.empty()) {
            QLabel *lblEmpty = new QLabel("No artists found.", artistBrowserPage);
            lblEmpty->setStyleSheet("color: gray; font-style: italic;");
            artistBrowserLayout->addWidget(lblEmpty);
        } else {
            for (const Artist &artist : artists) {
                QPushButton *btnArtist = new QPushButton(QString::fromStdString(artist.getFullName()), artistBrowserPage);
                btnArtist->setMinimumHeight(45);
                btnArtist->setStyleSheet(
                    "QPushButton { text-align: left; padding-left: 12px; font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
                    "QPushButton:hover { background-color: #f2f2f2; }"
                    );

                int artistID = artist.getID();
                QString artistName = QString::fromStdString(artist.getFullName());
                connect(btnArtist, &QPushButton::clicked, this, [this, artistID, artistName]() {
                    showArtistAlbumsPage(artistID, artistName);
                });

                artistBrowserLayout->addWidget(btnArtist);
            }
        }
    } else {
        QLabel *lblError = new QLabel("Failed to load artists.", artistBrowserPage);
        lblError->setStyleSheet("color: red;");
        artistBrowserLayout->addWidget(lblError);
    }

    artistBrowserLayout->addStretch();
    stackedWidget->setCurrentWidget(artistBrowserPage);
}


// --- 2. Artist Albums Page Creation ---
void MainWindow::createArtistAlbumsPage() {
    artistAlbumsPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(artistAlbumsPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    lblArtistAlbumsTitle = new QLabel("Artist's Albums", artistAlbumsPage);
    lblArtistAlbumsTitle->setAlignment(Qt::AlignCenter);
    lblArtistAlbumsTitle->setStyleSheet("font-size: 20px; font-weight: bold;");

    artistAlbumsContainer = new QWidget(artistAlbumsPage);
    artistAlbumsLayout = new QVBoxLayout(artistAlbumsContainer);
    artistAlbumsLayout->setSpacing(10);
    artistAlbumsLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scrollArea = new QScrollArea(artistAlbumsPage);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(artistAlbumsContainer);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    btnBackFromArtistAlbums = new QPushButton("Back", artistAlbumsPage);
    btnBackFromArtistAlbums->setMinimumHeight(40);
    btnBackFromArtistAlbums->setMinimumWidth(100);
    bottomLayout->addWidget(btnBackFromArtistAlbums);
    bottomLayout->addStretch();

    mainLayout->addWidget(lblArtistAlbumsTitle);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(bottomLayout);

    connect(btnBackFromArtistAlbums, &QPushButton::clicked, this, &MainWindow::showArtistBrowserPage);
}

void MainWindow::showArtistAlbumsPage(int artistID, const QString &artistName) {
    currentSelectedArtistId = artistID;
    currentSelectedArtistName = artistName;

    lblArtistAlbumsTitle->setText(artistName + "'s Collection");

    // Clear layout
    QLayoutItem *item;
    while ((item = artistAlbumsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    // 1. First button must be "Singles"
    QPushButton *btnSinglesAlbum = new QPushButton("Singles", artistAlbumsPage);
    btnSinglesAlbum->setMinimumHeight(45);
    btnSinglesAlbum->setStyleSheet(
        "QPushButton { text-align: left; padding-left: 12px; font-weight: bold; font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: #f8fafc; }"
        "QPushButton:hover { background-color: #f1f5f9; }"
        );
    connect(btnSinglesAlbum, &QPushButton::clicked, this, [this, artistID]() {
        showArtistSongsPage(-1, "Singles", artistID);
    });
    artistAlbumsLayout->addWidget(btnSinglesAlbum);

    // 2. Fetch and display normal albums
    auto albumsOpt = Controller::getInstance().AlbumsOfArtist(artistID);
    if (albumsOpt.has_value()) {
        const auto &albums = albumsOpt.value();
        for (const Album &album : albums) {
            QPushButton *btnAlbum = new QPushButton(QString::fromStdString(album.getName()), artistAlbumsPage);
            btnAlbum->setMinimumHeight(45);
            btnAlbum->setStyleSheet(
                "QPushButton { text-align: left; padding-left: 12px; font-size: 15px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
                "QPushButton:hover { background-color: #f2f2f2; }"
                );

            int albumID = album.getAlbumID();
            QString albumName = QString::fromStdString(album.getName());
            connect(btnAlbum, &QPushButton::clicked, this, [this, albumID, albumName, artistID]() {
                showArtistSongsPage(albumID, albumName, artistID);
            });

            artistAlbumsLayout->addWidget(btnAlbum);
        }
    }

    artistAlbumsLayout->addStretch();
    stackedWidget->setCurrentWidget(artistAlbumsPage);
}


// --- 3. Artist Songs Page Creation ---
void MainWindow::createArtistSongsPage() {
    artistSongsPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(artistSongsPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    lblArtistSongsTitle = new QLabel("Songs", artistSongsPage);
    lblArtistSongsTitle->setAlignment(Qt::AlignLeft);
    lblArtistSongsTitle->setStyleSheet("font-size: 18px; font-weight: bold;");

    artistSongsContainer = new QWidget(artistSongsPage);
    artistSongsLayout = new QVBoxLayout(artistSongsContainer);
    artistSongsLayout->setSpacing(10);
    artistSongsLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scrollArea = new QScrollArea(artistSongsPage);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(artistSongsContainer);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    btnBackFromArtistSongs = new QPushButton("Back", artistSongsPage);
    btnBackFromArtistSongs->setMinimumHeight(40);
    btnBackFromArtistSongs->setMinimumWidth(100);
    bottomLayout->addWidget(btnBackFromArtistSongs);
    bottomLayout->addStretch();

    mainLayout->addWidget(lblArtistSongsTitle);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(bottomLayout);

    connect(btnBackFromArtistSongs, &QPushButton::clicked, this, [this]() {
        showArtistAlbumsPage(currentSelectedArtistId, currentSelectedArtistName);
    });
}

void MainWindow::showArtistSongsPage(int albumID, const QString &albumTitle, int artistID) {
    currentSelectedAlbumId = albumID;
    currentSelectedAlbumTitle = albumTitle;

    lblArtistSongsTitle->setText(albumTitle);

    // Clear layout
    QLayoutItem *item;
    while ((item = artistSongsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    std::optional<std::vector<Song>> songsOpt;
    if (albumID == -1) {
        // Fetch Singles
        songsOpt = Controller::getInstance().artistSingleSong(artistID);
    } else {
        // Fetch Album songs
        songsOpt = Controller::getInstance().showSongsInAlbum(albumID);
    }

    if (songsOpt.has_value()) {
        const auto &songs = songsOpt.value();
        if (songs.empty()) {
            QLabel *lblEmpty = new QLabel("No songs found in this selection.", artistSongsPage);
            lblEmpty->setStyleSheet("color: gray; font-style: italic;");
            artistSongsLayout->addWidget(lblEmpty);
        } else {
            for (const Song &song : songs) {
                QPushButton *btnSong = new QPushButton(QString::fromStdString(song.getName()), artistSongsPage);
                btnSong->setMinimumHeight(45);
                btnSong->setStyleSheet(
                    "QPushButton { text-align: left; padding-left: 12px; font-size: 14px; border: 1px solid gray; border-radius: 8px; background-color: white; }"
                    "QPushButton:hover { background-color: #f2f2f2; }"
                    );

                int songID = song.getSongID();
                connect(btnSong, &QPushButton::clicked, this, [this, songID]() {
                    handleListenerSongClicked(songID);
                });

                artistSongsLayout->addWidget(btnSong);
            }
        }
    } else {
        QLabel *lblError = new QLabel("Failed to retrieve songs.", artistSongsPage);
        lblError->setStyleSheet("color: red;");
        artistSongsLayout->addWidget(lblError);
    }

    artistSongsLayout->addStretch();
    stackedWidget->setCurrentWidget(artistSongsPage);
}


// --- 4. Listener Detailed Song Pop-up / Dialog Logic ---
// --- 4. Listener Detailed Song Pop-up / Dialog Logic ---
void MainWindow::handleListenerSongClicked(int songID) {
    auto songOpt = Controller::getInstance().getSong(songID);
    if (!songOpt.has_value()) return;

    Song song = songOpt.value();

    QDialog dialog(this);
    dialog.setWindowTitle("Song Information");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    layout->addWidget(new QLabel("Title: " + QString::fromStdString(song.getName())));
    layout->addWidget(new QLabel("Artist: " + currentSelectedArtistName));
    layout->addWidget(new QLabel("Year: " + QString::number(song.getReleaseYear())));
    layout->addWidget(new QLabel("Genre: " + QString::fromStdString(song.getGenre())));

    QHBoxLayout *btnLayout = new QHBoxLayout();

    // LIKE BUTTON STATE SETUP
    QPushButton *btnLike = new QPushButton("Like", &dialog);
    btnLike->setCheckable(true);
    bool initialLiked = Controller::getInstance().islikeSong(songID);
    btnLike->setChecked(initialLiked);

    auto updateLikeStyle = [](QPushButton* btn) {
        if (btn->isChecked()) {
            btn->setText("Liked ❤️");
            btn->setStyleSheet("background-color: #fecdd3; color: #e11d48; font-weight: bold;");
        } else {
            btn->setText("Like ♡");
            btn->setStyleSheet("");
        }
    };
    updateLikeStyle(btnLike);

    QPushButton *btnPlaylist = new QPushButton("Add to Playlist", &dialog);
    QPushButton *btnClose = new QPushButton("Close", &dialog);

    btnLayout->addWidget(btnLike);
    btnLayout->addWidget(btnPlaylist);
    btnLayout->addWidget(btnClose);
    layout->addLayout(btnLayout);

    // Live feedback on click
    connect(btnLike, &QPushButton::clicked, this, [this, songID, btnLike, updateLikeStyle]() {
        bool newState = btnLike->isChecked();
        if (Controller::getInstance().likeSong(songID, newState)) {
            updateLikeStyle(btnLike);
        } else {
            // Revert state if operation fails
            btnLike->setChecked(!newState);
            updateLikeStyle(btnLike);
            QMessageBox::warning(this, "Error", "Could not complete the request.");
        }
    });

    // PLAYLIST COMBO LOGIC
    connect(btnPlaylist, &QPushButton::clicked, this, [this, songID]() {
        auto playlistsOpt = Controller::getInstance().myPlaylist();
        if (!playlistsOpt.has_value()) {
            QMessageBox::warning(this, "Error", "No playlists found.");
            return;
        }

        const auto &playlists = playlistsOpt.value();

        QDialog playlistDialog(this);
        playlistDialog.setWindowTitle("Select Playlist");
        QVBoxLayout *pLayout = new QVBoxLayout(&playlistDialog);

        pLayout->addWidget(new QLabel("Choose a playlist for this song:"));

        QComboBox *combo = new QComboBox(&playlistDialog);
        combo->addItem("None (No Playlist)", -1); // Default initial choice

        int currentPlaylistAssignedId = -1;

        // Find which normal playlist currently contains the song
        for (const Playlist &p : playlists) {
            combo->addItem(QString::fromStdString(p.getName()), p.getListID());

            // Check if song is in this playlist
            auto songsInPOpt = Controller::getInstance().showSongsInPlaylist(p.getListID());
            if (songsInPOpt.has_value()) {
                for (const Song &s : songsInPOpt.value()) {
                    if (s.getSongID() == songID) {
                        currentPlaylistAssignedId = p.getListID();
                        break;
                    }
                }
            }
        }

        // Set current selection to active playlist index if found
        if (currentPlaylistAssignedId != -1) {
            int targetIdx = combo->findData(currentPlaylistAssignedId);
            if (targetIdx != -1) {
                combo->setCurrentIndex(targetIdx);
            }
        }

        QDialogButtonBox *box =
            new QDialogButtonBox(
                QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                &playlistDialog
                );

        pLayout->addWidget(combo);
        pLayout->addWidget(box);

        connect(box, &QDialogButtonBox::accepted,
                &playlistDialog, &QDialog::accept);
        connect(box, &QDialogButtonBox::rejected,
                &playlistDialog, &QDialog::reject);

        if (playlistDialog.exec() == QDialog::Accepted) {
            int selectedPlaylistId = combo->currentData().toInt();

            // If selected playlist is the same, do nothing
            if (selectedPlaylistId == currentPlaylistAssignedId) {
                return;
            }

            // Step 1: Remove from old playlist if it existed
            if (currentPlaylistAssignedId != -1) {
                Controller::getInstance().removeSongFromPlaylist(
                    songID,
                    currentPlaylistAssignedId
                    );
            }

            // Step 2: Add to new playlist if not "None"
            if (selectedPlaylistId != -1) {
                if (Controller::getInstance().insertSongtoPlaylist(
                        songID,
                        selectedPlaylistId
                        )) {
                    QMessageBox::information(
                        this,
                        "Success",
                        "Song added to playlist."
                        );
                } else {
                    QMessageBox::warning(
                        this,
                        "Error",
                        "Failed to add song to playlist."
                        );
                }
            } else {
                QMessageBox::information(
                    this,
                    "Success",
                    "Song removed from all normal playlists."
                    );
            }
        }
    });

    connect(btnClose, &QPushButton::clicked,
            &dialog, &QDialog::accept);

    dialog.exec();
}