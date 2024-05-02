#include "mainwindow.h"
#include "User.h"

#include <QApplication>
#include <QScreen>
#include <QResizeEvent>

MainWindow::MainWindow(const User& user, QWidget *parent ) : QMainWindow(parent)
{
    mainWidget = new MainWidget(user, this, this);
    setCentralWidget(mainWidget);
}


void MainWindow::resizeEvent(QResizeEvent *event) {
     // Вызываем базовый метод для выполнения стандартного поведения
    QMainWindow::resizeEvent(event);

    // Получаем размеры окна
    QSize newSize = event->size();

    // Устанавливаем фоновую кисть с новыми размерами
    QPixmap pixmap(":/Images/Images/fon.png");
    pixmap = pixmap.scaled(newSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    setPalette(palette);
}


