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


    void handleLogin();
    void handleSignUp();

private:
    QStackedWidget *stackedWidget;

    // UI Elements - Welcome Page
    QWidget *welcomePage;
    QRadioButton *rbWelcomeLogin, *rbWelcomeSignUp;

    // UI Elements - Login Page
    QWidget *loginPage;
    QLineEdit *txtLoginUser, *txtLoginPass;
    QRadioButton *rbLoginListener, *rbLoginArtist;

    // UI Elements - Sign Up Page
    QWidget *signUpPage;
    QLineEdit *txtSignFull, *txtSignUser, *txtSignPass, *txtSignBio;
    QRadioButton *rbSignListener, *rbSignArtist;

    // Helper functions to create pages
    void createWelcomePage();
    void createLoginPage();
    void createSignUpPage();
};

#endif // MAINWINDOW_H

