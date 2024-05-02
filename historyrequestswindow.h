#ifndef HISTORYREQUESTSWINDOW_H
#define HISTORYREQUESTSWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>

#include "User.h"
#include "RequestListItem.h"

class HistoryRequestsWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HistoryRequestsWindow(const User& user, QWidget *parent = nullptr, QMainWindow *mainWindow = nullptr);

private:
    const User& user;
    QMainWindow *mainWindow;
    QListWidget *requestsListWidget;
    QPushButton *returnButton;
    QByteArray photoData;

private slots:
    void returnToMain();
    void loadRequestsHistory(int userId);
};

#endif // HISTORYREQUESTSWINDOW_H
