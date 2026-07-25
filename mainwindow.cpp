#include "mainwindow.h"
#include "Controller.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"

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

// --- Constructor ---
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentAlbumId(-1) {
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

    stackedWidget->addWidget(welcomePage);
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(signUpPage);
    stackedWidget->addWidget(artistDashboardPage);
    stackedWidget->addWidget(artistProfilePage);
    stackedWidget->addWidget(collectionPage);

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
        showArtistDashboardPage();
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



