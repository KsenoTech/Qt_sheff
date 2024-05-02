#include <QApplication>
#include "loginwindow.h"
#include <QScreen>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlDatabase>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Создаем объект базы данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // Устанавливаем параметры подключения
    db.setHostName("DESKTOP-L4S7KET\\SQLEXPRESS"); // Имя сервера
    db.setDatabaseName("DRIVER={SQL Server};Server=DESKTOP-L4S7KET\\SQLEXPRESS;Database=QtCamp;"); // Название базы данных и драйвер

    // Пытаемся открыть базу данных
    if (!db.open()) {
        // Если не удалось открыть базу данных, выводим сообщение об ошибке
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        return 1;
    }

    LoginWindow loginWindow;
    loginWindow.setGeometry(100, 100, 200, 150); // Установка размеров окна
    loginWindow.show();
    loginWindow.move(QGuiApplication::primaryScreen()->availableGeometry().center() - loginWindow.rect().center()); // Открытие по центру экрана

    return app.exec();
}
