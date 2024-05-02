#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "User.h"

class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(const User& user = User(), QWidget *parent = nullptr, QMainWindow *mainWindow = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    User user; // Добавляем член данных для пользователя
    QMainWindow *mainWindow;
    int buttonsWidth = 0; // Теперь buttonsWidth является членом класса MainWidget
    int buttonsHeight = 0; // Теперь buttonsHeight является членом класса MainWidget
    // Добавляем private-член для кнопки профиля
    QPushButton *profileButton;
    QPushButton *activeRequestsButton;
    QPushButton *createRequestButton;
    QPushButton *historyButton;


private slots:
    void showProfile();
    void showCreateRequest();
    void showActiveRequests();
    void showHistory();
};

#endif // MAINWIDGET_H
