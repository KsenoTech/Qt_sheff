#ifndef CREATEREQUESTWINDOW_H
#define CREATEREQUESTWINDOW_H

#include "User.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

class CreateRequestWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit CreateRequestWindow(const User& user, QWidget *parent = nullptr, QMainWindow *mainWindow = nullptr);

private slots:
    void browsePhoto();
    void submitRequest();
    void closeAndReturn();

private:
    const User& user;
    QMainWindow *mainWindow;
    QTextEdit *descriptionTextEdit;
    QLabel *photoLabel;
    QPushButton *browseButton;
    QPushButton *submitButton;
};

#endif // CREATEREQUESTWINDOW_H
