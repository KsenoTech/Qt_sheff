#include "loginwindow.h"
#include "User.h"
#include "mainwindow.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>
#include <QScreen>
#include <QPalette>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка фонового цвета
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#ccb3e6"));
    setAutoFillBackground(true);
    setPalette(pal);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Логин");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Пароль");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Вход", this);
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::attemptLogin);

    mainLayout->addWidget(usernameLineEdit);
    mainLayout->addWidget(passwordLineEdit);
    mainLayout->addWidget(loginButton);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Вход");
}
void LoginWindow::attemptLogin()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    // Проверяем правильность введенных данных
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }

    // Выполняем запрос к базе данных для проверки логина и пароля
    QSqlQuery query;
    QString queryString = QString("SELECT * FROM Users WHERE Login = '%1' AND Password = '%2'").arg(username).arg(password);
    //qDebug() << "Query text:" << queryString; // Выводим текст запроса в консоль
    if(query.exec(queryString)) {
        if (query.next()) {
            // Если есть соответствующая запись в базе данных, открываем главное окно приложения

            // Создаем объект пользователя на основе данных из базы данных
            User user;
            user.setUsername(query.value("Login").toString());
            user.setFullName(query.value("UserFIO").toString());
            user.setRoomNumber(query.value("RoomNumber").toInt());
            user.setId(query.value("Id").toInt());
            user.setRating(query.value("Rating").toDouble());

            MainWindow *mainWindow = new MainWindow(user);
            mainWindow->setWindowTitle("Сервис для подачи заявок на ремонт");
            mainWindow->setGeometry(100, 100, 800, 500); // Установка размеров окна
            mainWindow->show();
            mainWindow->move(QGuiApplication::primaryScreen()->availableGeometry().center() - mainWindow->rect().center());

            this->close(); // Закрываем окно входа
        } else {
            // Если нет записи с таким логином и паролем, выводим сообщение об ошибке
            QMessageBox::warning(this, "Login Error", "Incorrect username or password.");
        }
    } else {
        // Если запрос не выполнен успешно, выводим сообщение об ошибке
        //qDebug() << "Error executing query:" << query.lastError().text();
        QMessageBox::warning(this, "Database Error", "Error executing query. Please try again later.");
    }
}

