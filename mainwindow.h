#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwidget.h"
#include "User.h"
#include <QEvent>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(const User& user, QWidget *paren = nullptr);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    MainWidget *mainWidget;
};

#endif // MAINWINDOW_H
