#include "profilewindow.h"
#include "User.h"

#include <QGuiApplication>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <QPalette>


ProfileWindow::ProfileWindow(const User& user, QWidget *parent, QMainWindow *mainWindow) :
    user(user), QMainWindow(parent), mainWindow(mainWindow)
{
    // Установка фонового цвета
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#ccb3e6"));
    setAutoFillBackground(true);
    setPalette(pal);

    // Основной layout для размещения элементов управлени
    QVBoxLayout *profileLayout = new QVBoxLayout();

    //progileListWidget = new QListWidget(this);

    // // Метка для отображения ФИО
    // QLabel *nameLabel = new QLabel("ФИО: " + user.fullName(), this);
    // // Метка для отображения комнаты
    // QLabel *roomLabel = new QLabel("Комната: " + QString::number(user.roomNumber()), this);
    // // Метка для отображения рейтинга
    // QLabel *ratingLabel = new QLabel("Рейтинг: " + QString::number(user.rating()), this);

    // Метка для отображения выбранного фото
    photoLabel = new QLabel("", this);

    // Кнопка для выбора фото
    browseButton = new QPushButton("Обновить фото", this);
    connect(browseButton, &QPushButton::clicked, this, &ProfileWindow::browsePhoto);

    // Кнопка обновления фото
    submitButton = new QPushButton("Сохранить фоточку", this);
    connect(submitButton, &QPushButton::clicked, this, [=]() {
        this->submitPhoto(user.Id());
    });


    returnButton = new QPushButton("Вернуться");
    connect(returnButton, &QPushButton::clicked, this, &ProfileWindow::closeAndReturn);

    // profileLayout->addWidget(nameLabel);
    // profileLayout->addWidget(roomLabel);
    // profileLayout->addWidget(ratingLabel);
    //profileLayout->addWidget(photoLabel);
    //profileLayout->addWidget(progileListWidget);


    profileLayout->addWidget(browseButton);
    profileLayout->addWidget(submitButton);
    profileLayout->addWidget(returnButton);


    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(profileLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Профиль студента");

    // Загрузка данных профиля из базы данных
    loadProfileData(user.Id());

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

void ProfileWindow::browsePhoto()
{
    // Открываем диалоговое окно для выбора файла
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать фото", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        // Отображаем выбранное фото
        QPixmap pixmap(fileName);
        photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    }
}

// void ProfileWindow::browsePhoto()
// {
//     // Открываем диалоговое окно для выбора файла
//     QString fileName = QFileDialog::getOpenFileName(this, "Выбрать фото", "", "Images (*.png *.jpg *.jpeg)");
//     if (!fileName.isEmpty()) {
//         // Отображаем выбранное фото
//         QPixmap pixmap(fileName);
//         if (!pixmap.isNull()) {
//             photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
//         } else {
//             QMessageBox::warning(this, "Ошибка", "Невозможно загрузить фотографию");
//         }
//     }
// }


void ProfileWindow::submitPhoto(int userId)
{
    QPixmap photoPixmap = qvariant_cast<QPixmap>(photoLabel->pixmap().scaled(200, 200)); // Получаем изображение из QLabel
    // Проверяем, загружено ли изображение
    if (!photoPixmap.isNull()) {
        // Преобразуем изображение в массив байтов
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        photoPixmap.save(&buffer, "PNG"); // Сохраняем изображение в формате PNG
        QString base64Photo = byteArray.toBase64(); // Кодируем изображение в base64

        //qDebug() << "base64Photo data size:" << base64Photo.size();
        // Создаем объект запроса
        QSqlQuery query;

        // Выполняем запрос к базе данных для вставки данных заявки
        QString queryString = QString("UPDATE Users SET UserPhoto = '%1' WHERE Id = %2")
                                  .arg(base64Photo)
                                  .arg(userId);

        if (query.exec(queryString)) {
            QMessageBox::information(this, "Успех", "Фотография обновлена!");
        } else {
            QMessageBox::critical(this, "Ошибка", "Ошибка при отправке фотографии: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Фотография не выбрана!");
    }

    // Очищаем поля ввода
    photoLabel->clear(); // Очищаем отображенное фото
}

void ProfileWindow::loadProfileData(int userId) {

    QSqlQuery query;

    // Выполняем запрос к базе данных для получения информации о пользователе с указанным ID
    query.prepare("SELECT * FROM Users WHERE Id = :userId");
    query.bindValue(":userId", userId);

    // if (query.exec()) {
    //     if (query.next()) {
    //         RequestListItem *item = new RequestListItem();
    //         item->setFIO("ФИО: "+query.value("UserFIO").toString());
    //         item->setRoom("Номер комнаты: "+query.value("RoomNumber").toString());
    //         item->setRating("Рейтинг: "+query.value("Rating").toString());

    //         // Получаем данные изображения в виде QByteArray из запроса
    //         QByteArray imageData = QByteArray::fromBase64(query.value("UserPhoto").toByteArray());

    //         // Создаем QPixmap из QByteArray
    //         QPixmap photoPixmap;
    //         photoPixmap.loadFromData(imageData);

    //         // Устанавливаем изображение в элемент списка
    //         item->setPhoto(photoPixmap);

    //         //qDebug() << "imageData data size:" << imageData.size();
    //         //qDebug() << "photoPixmap data size:" << photoPixmap.size();

    //         QListWidgetItem *listItem = new QListWidgetItem();
    //         listItem->setSizeHint(item->sizeHint());
    //         progileListWidget->addItem(listItem);
    //         progileListWidget->setItemWidget(listItem, item);
    //     } else {
    //         qDebug() << "Error: User not found for ID:" << userId;
    //     }
    // } else {
    //     qDebug() << "Error executing query:" << query.lastError().text();
    // }
    if (query.exec()) {
        if (query.next()) {
            // Получаем данные из запроса
            QString fio = "ФИО: " + query.value("UserFIO").toString();
            QString room = "Номер комнаты: " + query.value("RoomNumber").toString();
            QString rating = "Рейтинг: " + query.value("Rating").toString();

            // Создаем QLabel'ы для каждого элемента
            QLabel *fioLabel = new QLabel(fio, this);
            QLabel *roomLabel = new QLabel(room, this);
            QLabel *ratingLabel = new QLabel(rating, this);

            // Получаем данные изображения в виде QByteArray из запроса
            QByteArray imageData = QByteArray::fromBase64(query.value("UserPhoto").toByteArray());

            // Создаем QPixmap из QByteArray
            QPixmap photoPixmap;
            photoPixmap.loadFromData(imageData);

            // Создаем QLabel для отображения фото
            QLabel *photonewLabel = new QLabel(this);
            photonewLabel->setPixmap(photoPixmap.scaled(200, 200, Qt::KeepAspectRatio));

            // Добавляем QLabel'ы в макет
            QVBoxLayout *mainLayout = new QVBoxLayout();
            mainLayout->addWidget(fioLabel);
            mainLayout->addWidget(roomLabel);
            mainLayout->addWidget(ratingLabel);
            mainLayout->addWidget(photonewLabel);
            mainLayout->addWidget(browseButton);
            mainLayout->addWidget(submitButton);
            mainLayout->addWidget(returnButton);

            // Устанавливаем макет в центральный виджет
            QWidget *centralWidget = new QWidget();
            centralWidget->setLayout(mainLayout);
            setCentralWidget(centralWidget);
        } else {
            qDebug() << "Error: User not found for ID:" << userId;
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

}

void ProfileWindow::closeAndReturn() {
    mainWindow->showNormal();
    mainWindow->activateWindow();
    close(); // Скрыть текущее окно профиля
}
