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

    stackedWidget->addWidget(welcomePage);
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(signUpPage);

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
