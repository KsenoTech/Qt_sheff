#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

signals:

private slots:
    void attemptLogin();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
};

#endif // LOGINWINDOW_H
