#include "mainwindow.h"
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

    stackedWidget->addWidget(welcomePage);
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(signUpPage);

    // welcom page
    showWelcomePage();
}

MainWindow::~MainWindow() {}

// --- صفحه اول (Welcome) ---
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
        if(rbWelcomeLogin->isChecked()) showLoginPage();
        else if(rbWelcomeSignUp->isChecked()) showSignUpPage();
        else QMessageBox::warning(this, "Wait", "Please select an option.");
    });
}

// ---  صفحه لاگین ---
void MainWindow::createLoginPage() {
    loginPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(loginPage);

    QLabel *lblHead = new QLabel("you are:", loginPage);
    rbLoginListener = new QRadioButton("listener", loginPage);
    rbLoginArtist = new QRadioButton("artist", loginPage);

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

    layout->addWidget(lblHead);
    layout->addWidget(rbLoginListener);
    layout->addWidget(rbLoginArtist);
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

// ---  صفحه ساین‌آپ ---
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

// ------
void MainWindow::showWelcomePage() { stackedWidget->setCurrentWidget(welcomePage); }
void MainWindow::showLoginPage() { stackedWidget->setCurrentWidget(loginPage); }
void MainWindow::showSignUpPage() { stackedWidget->setCurrentWidget(signUpPage); }

void MainWindow::handleLogin() {

    QMessageBox::information(this, "Login", "Trying to login as " + txtLoginUser->text());
}

void MainWindow::handleSignUp() {
    QMessageBox::information(this, "Sign Up", "Creating account for " + txtSignUser->text());
}
