#include "activerequestswindow.h"
#include "User.h"

#include <QGuiApplication>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QPalette>


ActiveRequestsWindow::ActiveRequestsWindow(const User& user, QWidget *parent, QMainWindow *mainWindow) :
    user(user), QMainWindow(parent), mainWindow(mainWindow)
{
    // Установка фонового цвета
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#ccb3e6"));
    setAutoFillBackground(true);
    setPalette(pal);
    // Основной layout для размещения элементов управления
    QVBoxLayout *mainLayout = new QVBoxLayout();

    activeListWidget = new QListWidget(this);

    returnButton = new QPushButton("Вернуться", this);
    connect(returnButton, &QPushButton::clicked, this, &ActiveRequestsWindow::closeAndReturn);

    // Добавляем элементы управления в layout
    mainLayout->addWidget(activeListWidget);
    mainLayout->addWidget(returnButton);

    // Устанавливаем layout для центрального виджета окна
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Устанавливаем заголовок окна
    setWindowTitle("Активные заявки");

    // Загрузка активных заявок из базы данных
    loadActiveRequests(user.Id());

    // Выполняем операцию после отображения окна
    QTimer::singleShot(0, this, [=]() {
        // Получаем геометрию рабочего стола
        QRect desktopGeometry = QGuiApplication::primaryScreen()->availableGeometry();

        // Вычисляем центральную позицию для окна
        int x = (desktopGeometry.width() - width()) / 2;
        int y = (desktopGeometry.height() - height()) / 2;

        // Устанавливаем позицию окна по центру
        move(x, y);
        // Делаем окно активным
        activateWindow();
    });

}

void ActiveRequestsWindow::loadActiveRequests(int userId) {
    // Создаем объект запроса
    QSqlQuery query;
    QString queryString = QString("SELECT * FROM Requests WHERE Status = 'В процессе' AND RequesterId = '%1'").arg(userId);
    if (query.exec(queryString)) {
        // Если запрос выполнен успешно, добавляем каждую заявку в список
        while (query.next()) {
            RequestListItem *item = new RequestListItem();
            item->setRoom(query.value("RoomNumber").toString());
            item->setDescription(query.value("Description").toString());
            item->setStatus(query.value("Status").toString());

            // Получаем данные изображения в виде QByteArray из запроса
            QByteArray imageData = QByteArray::fromBase64(query.value("Photo").toByteArray());

            // Создаем QPixmap из QByteArray
            QPixmap photoPixmap;
            photoPixmap.loadFromData(imageData);

            // Устанавливаем изображение в элемент списка
            item->setPhoto(photoPixmap);

            //qDebug() << "imageData data size:" << imageData.size();
            //qDebug() << "photoPixmap data size:" << photoPixmap.size();

            QListWidgetItem *listItem = new QListWidgetItem();
            listItem->setSizeHint(item->sizeHint());
            activeListWidget->addItem(listItem);
            activeListWidget->setItemWidget(listItem, item);
        }
    } else {
        // Если запрос не выполнен успешно, выводим сообщение об ошибке
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

void ActiveRequestsWindow::closeAndReturn() {
    mainWindow->showNormal();
    mainWindow->activateWindow();
    close(); // Скрыть текущее окно
}
