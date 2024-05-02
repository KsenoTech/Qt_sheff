#ifndef ACTIVEREQUESTSWINDOW_H
#define ACTIVEREQUESTSWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>

#include "User.h"
#include "RequestListItem.h"

class ActiveRequestsWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ActiveRequestsWindow(const User& user, QWidget *parent = nullptr, QMainWindow *mainWindow = nullptr);

private:
    const User& user;
    QMainWindow *mainWindow;
    QVBoxLayout *mainLayout;
    QListWidget *activeListWidget;
    QPushButton *returnButton;
    QByteArray photoData;

private slots:
    // Слот для обработки нажатия кнопки "Вернуться"
    void closeAndReturn();
    void loadActiveRequests(int userId);
};

#endif // ACTIVEREQUESTSWINDOW_H
