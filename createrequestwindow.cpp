#include "createrequestwindow.h"
#include "User.h"

#include <QGuiApplication>
#include <QMessageBox>
#include <QScreen>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QBuffer>
#include <QSqlQuery>
#include <QSqlError>
#include <QPalette>

CreateRequestWindow::CreateRequestWindow(const User& user, QWidget *parent, QMainWindow *mainWindow) :
    user(user), QMainWindow(parent), mainWindow(mainWindow)
{
    // Установка фонового цвета
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#ccb3e6"));
    setAutoFillBackground(true);
    setPalette(pal);
    // Основной layout для размещения элементов управления
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // Поле ввода описания проблемы
    descriptionTextEdit = new QTextEdit(this);
    descriptionTextEdit->setPlaceholderText("Описание проблемы");

    // Метка для отображения выбранного фото
    photoLabel = new QLabel("Выберите фото", this);

    // Кнопка для выбора фото
    browseButton = new QPushButton("Выбрать фото", this);
    connect(browseButton, &QPushButton::clicked, this, &CreateRequestWindow::browsePhoto);

    // Кнопка подачи заявки
    submitButton = new QPushButton("Подать заявку", this);
    connect(submitButton, &QPushButton::clicked, this, &CreateRequestWindow::submitRequest);

    // // Добавляем элементы управления в layout
    mainLayout->addWidget(descriptionTextEdit);
    mainLayout->addWidget(photoLabel);
    mainLayout->addWidget(browseButton);
    mainLayout->addWidget(submitButton);

    QPushButton *returnButton = new QPushButton("Вернуться");
    connect(returnButton, &QPushButton::clicked, this, &CreateRequestWindow::closeAndReturn);
    mainLayout->addWidget(returnButton);

    // Устанавливаем layout для центрального виджета окна
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Устанавливаем заголовок окна
    setWindowTitle("Подача заявки");


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

void CreateRequestWindow::browsePhoto() {
    // Открываем диалоговое окно для выбора файла
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать фото", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        // Отображаем выбранное фото
        QPixmap pixmap(fileName);
        photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    }
}

void CreateRequestWindow::submitRequest() {
    // Получаем данные из полей ввода
    QString description = descriptionTextEdit->toPlainText();
    QString status = "В процессе";

    QPixmap photoPixmap = qvariant_cast<QPixmap>(photoLabel->pixmap().scaled(200, 200)); // Получаем изображение из QLabel
    if (description.isEmpty()) {
        qDebug() << "Error: Description cannot be empty!";
        return;
    }
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
        QString queryString = QString("INSERT INTO Requests (RequesterId, RoomNumber, Description, Photo, Status)"
                                      " VALUES ('%1', '%2', '%3', '%4', '%5')")
                                    .arg(user.Id())
                                    .arg(user.roomNumber())
                                    .arg(description)
                                    .arg(base64Photo)
                                    .arg(status);

        if (query.exec(queryString)) {
            QMessageBox::information(this, "Успех", "Заявка отправлена успешно!");
        } else {
            QMessageBox::critical(this, "Ошибка", "Ошибка при отправке заявки: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Фотография не выбрана!");
    }

    // Очищаем поля ввода
    descriptionTextEdit->clear();
    photoLabel->clear(); // Очищаем отображенное фото
}


void CreateRequestWindow::closeAndReturn() {
    mainWindow->showNormal();
    mainWindow->activateWindow();
    close(); // Скрыть текущее окно профиля
}
