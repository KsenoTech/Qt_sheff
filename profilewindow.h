#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "User.h"
#include "RequestListItem.h"

class ProfileWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ProfileWindow(const User& user, QWidget *parent = nullptr, QMainWindow *mainWindow = nullptr);

private:
    const User& user;
    QMainWindow *mainWindow;
    QVBoxLayout *mainLayout;
    QListWidget *progileListWidget;
    QPushButton *returnButton;
    QPushButton *browseButton;
    QByteArray photoData;
    QLabel *photoLabel;
    QPushButton *submitButton;

private slots:

    void submitPhoto(int userId);
    void browsePhoto();
    void closeAndReturn();
    void loadProfileData(int userId);
};

#endif // PROFILEWINDOW_H
