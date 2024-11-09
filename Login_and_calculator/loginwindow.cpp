#include "loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    usernameEdit = new QLineEdit(centralWidget);
    usernameEdit->setPlaceholderText("Username");

    passwordEdit = new QLineEdit(centralWidget);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Login", centralWidget);
    registerButton = new QPushButton("Register", centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegister);
}

void LoginWindow::onLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // Check correctness of password/login
    QFile file("users.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList credentials = line.split(",");
            if (credentials.size() == 2 && credentials[0] == username && credentials[1] == password) {
                QMessageBox::information(this, "Login", "Login successful!");
                emit loginSuccessful();
                file.close();
                return;
            }
        }
        file.close();
    }

    QMessageBox::warning(this, "Login", "Invalid credentials.");
}

void LoginWindow::onRegister() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // Check if the user already exists
    QFile file("users.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList credentials = line.split(",");
            if (credentials.size() > 0 && credentials[0] == username) {
                QMessageBox::warning(this, "Registration", "Username already exists.");
                file.close();
                return;
            }
        }
        file.close();
    }

    // Save the new user
    saveUser(username, password);
    QMessageBox::information(this, "Registration", "Registration successful!");
}

void LoginWindow::saveUser(const QString &username, const QString &password) {
    QFile file("users.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << "," << password << "\n";
        file.close();
    }
}
