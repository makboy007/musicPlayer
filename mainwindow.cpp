#include "mainwindow.h"
#include "Controller.h"

#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
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

    btnArtistName = new QPushButton("Eminem", artistDashboardPage);
    btnArtistName->setCursor(Qt::PointingHandCursor);
    btnArtistName->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "font-size: 16px;"
        "font-weight: bold;"
        "text-align: left;"
        "padding: 0px;"
        "}"
        );

    topLayout->addWidget(btnArtistName);
    topLayout->addStretch();

    QVBoxLayout *albumsLayout = new QVBoxLayout();
    albumsLayout->setSpacing(10);

    btnSingles = new QPushButton("Singles", artistDashboardPage);
    btnAlbum1 = new QPushButton("Recovery", artistDashboardPage);
    btnAlbum2 = new QPushButton("Relapse", artistDashboardPage);
    btnAlbum3 = new QPushButton("The Eminem Show", artistDashboardPage);

    QList<QPushButton*> albumButtons = {btnSingles, btnAlbum1, btnAlbum2, btnAlbum3};

    for (QPushButton *btn : albumButtons) {
        btn->setMinimumHeight(45);
        btn->setStyleSheet(
            "QPushButton {"
            "text-align: left;"
            "padding-left: 12px;"
            "font-size: 15px;"
            "border: 1px solid gray;"
            "border-radius: 8px;"
            "background-color: white;"
            "}"
            "QPushButton:hover {"
            "background-color: #f2f2f2;"
            "}"
            );
        albumsLayout->addWidget(btn);
    }

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
    mainLayout->addLayout(albumsLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    connect(btnArtistName, &QPushButton::clicked, this, &MainWindow::showArtistProfilePage);
    connect(btnLogoutArtist, &QPushButton::clicked, this, &MainWindow::showWelcomePage);

    connect(btnSingles, &QPushButton::clicked, this, &MainWindow::handleSinglesClicked);
    connect(btnAlbum1, &QPushButton::clicked, this, &MainWindow::handleAlbum1Clicked);
    connect(btnAlbum2, &QPushButton::clicked, this, &MainWindow::handleAlbum2Clicked);
    connect(btnAlbum3, &QPushButton::clicked, this, &MainWindow::handleAlbum3Clicked);
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
    lblProfileFullNameValue = new QLabel("Eminem", artistProfilePage);

    QLabel *lblUsernameTitle = new QLabel("Username:", artistProfilePage);
    lblProfileUsernameValue = new QLabel("eminem123", artistProfilePage);

    QLabel *lblBioTitle = new QLabel("Biography:", artistProfilePage);
    lblProfileBioValue = new QLabel("American rapper and songwriter.", artistProfilePage);
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
    connect(btnDeleteProfile, &QPushButton::clicked, this, &MainWindow::handleDeleteProfile);
}

// --- Collection Page ---
void MainWindow::createCollectionPage() {
    collectionPage = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(collectionPage);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    lblCollectionTitle = new QLabel("Singles", collectionPage);
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
    btnBackFromCollection->setMinimumWidth(100);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(btnBackFromCollection);
    bottomLayout->addStretch();

    mainLayout->addWidget(lblCollectionTitle);
    mainLayout->addWidget(songsScrollArea);
    mainLayout->addLayout(bottomLayout);

    connect(btnBackFromCollection, &QPushButton::clicked, this, &MainWindow::showArtistDashboardPage);
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
    stackedWidget->setCurrentWidget(artistDashboardPage);
}

void MainWindow::showArtistProfilePage() {
    stackedWidget->setCurrentWidget(artistProfilePage);
}

void MainWindow::showCollectionPage() {
    stackedWidget->setCurrentWidget(collectionPage);
}

// --- Collection Helpers ---
void MainWindow::clearSongsList() {
    QLayoutItem *item;
    while ((item = songsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

QPushButton* MainWindow::createSongItemButton(const QString &songTitle) {
    QPushButton *btnSong = new QPushButton(songTitle, collectionPage);
    btnSong->setMinimumHeight(45);
    btnSong->setStyleSheet(
        "QPushButton {"
        "text-align: left;"
        "padding-left: 12px;"
        "font-size: 14px;"
        "border: 1px solid gray;"
        "border-radius: 8px;"
        "background-color: white;"
        "}"
        "QPushButton:hover {"
        "background-color: #f2f2f2;"
        "}"
        );
    return btnSong;
}

void MainWindow::loadCollectionPage(const QString &title, const QStringList &songs) {
    lblCollectionTitle->setText(title);
    clearSongsList();

    for (const QString &song : songs) {
        songsLayout->addWidget(createSongItemButton(song));
    }

    songsLayout->addStretch();
    showCollectionPage();
}

// --- Dashboard Item Handlers ---
void MainWindow::handleSinglesClicked() {
    QStringList songs;
    songs << "Lose Yourself"
          << "Mockingbird"
          << "Without Me";

    loadCollectionPage("Singles", songs);
}

void MainWindow::handleAlbum1Clicked() {
    QStringList songs;
    songs << "Cold Wind Blows"
          << "Talkin 2 Myself"
          << "Not Afraid";

    loadCollectionPage("Recovery", songs);
}

void MainWindow::handleAlbum2Clicked() {
    QStringList songs;
    songs << "3 a.m."
          << "Beautiful"
          << "Crack a Bottle";

    loadCollectionPage("Relapse", songs);
}

void MainWindow::handleAlbum3Clicked() {
    QStringList songs;
    songs << "White America"
          << "Business"
          << "Cleanin' Out My Closet";

    loadCollectionPage("The Eminem Show", songs);
}

// --- Handlers ---
void MainWindow::handleLogin() {
    QString user = txtLoginUser->text();
    QString pass = txtLoginPass->text();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    bool success = Controller::getInstance().login(user.toStdString(), pass.toStdString());

    if (success) {
        QMessageBox::information(this, "Success", "Welcome back!");
        showArtistDashboardPage();
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::handleSignUp() {
    QString fullName = txtSignFull->text();
    QString user = txtSignUser->text();
    QString pass = txtSignPass->text();
    QString bio = txtSignBio->text();
    bool isArtist = rbSignArtist->isChecked();

    if (fullName.isEmpty() || user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill required fields.");
        return;
    }

    if (!rbSignArtist->isChecked() && !rbSignListener->isChecked()) {
        QMessageBox::warning(this, "Error", "Please select a role.");
        return;
    }

    bool success = Controller::getInstance().signUp(
        fullName.toStdString(),
        user.toStdString(),
        pass.toStdString(),
        bio.toStdString(),
        isArtist
        );

    if (success) {
        QMessageBox::information(this, "Success", "Account created successfully! Please login.");
        showLoginPage();
    } else {
        QMessageBox::critical(this, "Sign Up Failed", "Username already exists or an error occurred.");
    }
}

void MainWindow::handleDeleteProfile() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Delete Profile",
        "Are you sure you want to delete your profile?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QMessageBox::information(this, "Deleted", "Profile deleted successfully.");
        showWelcomePage();
    }
}

