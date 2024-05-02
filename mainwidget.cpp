#include "mainwidget.h"
#include "mainwindow.h"
#include "profilewindow.h"
#include "createrequestwindow.h"
#include "activerequestswindow.h"
#include "historyrequestswindow.h"
#include "User.h"

#include <QtWidgets>
#include <QMainWindow>
#include <QResizeEvent>

MainWidget::MainWidget(const User& user, QWidget *parent, QMainWindow *mainWindow) :
    QWidget(parent), mainWindow(mainWindow), user(user)
{
    // Устанавливаем минимальный размер виджета
    setMinimumSize(mainWindow->width(), mainWindow->height()); // Например, ширина будет равна половине ширины окна

    // Создание вертикального layout для всего виджета
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создание горизонтального layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->setAlignment(Qt::AlignCenter);

    // Кнопка "Профиль"
    profileButton = new QPushButton("Профиль", this);
    profileButton->setFont(QFont("Playfair Display", 12, QFont::Bold)); // Установка шрифта и размера текста
    profileButton->setFixedSize(200, 90); // Устанавливаем фиксированный размер
    profileButton->setStyleSheet("QPushButton { border-radius: 20px; background-color: #b38dd9; }" // Стиль кнопки
                                 "QPushButton:hover { background-color: #7366bd; }" // Эффект наведения
                                 "QPushButton:pressed { background-color: #660099; }"); // Эффект при нажатии
    connect(profileButton, &QPushButton::clicked, this, &MainWidget::showProfile);
    buttonLayout->addWidget(profileButton);

    // Кнопка "Создать заявку"
    createRequestButton = new QPushButton("Создать заявку", this);
    createRequestButton->setFont(QFont("Playfair Display", 12, QFont::Bold)); // Установка шрифта и размера текста
    createRequestButton->setFixedSize(200, 90); // Устанавливаем фиксированный размер
    createRequestButton->setStyleSheet("QPushButton { border-radius: 20px; background-color: #b38dd9; }" // Стиль кнопки
                                       "QPushButton:hover { background-color: #7366bd; }" // Эффект наведения
                                       "QPushButton:pressed { background-color: #660099; }"); // Эффект при нажатии
    connect(createRequestButton, &QPushButton::clicked, this, &MainWidget::showCreateRequest);
    buttonLayout->addWidget(createRequestButton);

    // Кнопка "Активные заявки"
    activeRequestsButton = new QPushButton("Активные заявки", this);
    activeRequestsButton->setFont(QFont("Playfair Display", 12, QFont::Bold)); // Установка шрифта и размера текста
    activeRequestsButton->setFixedSize(200, 90); // Устанавливаем фиксированный размер
    activeRequestsButton->setStyleSheet("QPushButton { border-radius: 20px; background-color: #b38dd9; }" // Стиль кнопки
                    "QPushButton:hover { background-color: #7366bd; }" // Эффект наведения
                    "QPushButton:pressed { background-color: #660099; }"); // Эффект при нажатии
    connect(activeRequestsButton, &QPushButton::clicked, this, &MainWidget::showActiveRequests);
    buttonLayout->addWidget(activeRequestsButton);

    // Кнопка "История заявок"
    historyButton = new QPushButton("История заявок", this);
    historyButton->setFont(QFont("Playfair Display", 12, QFont::Bold)); // Установка шрифта и размера текста
    historyButton->setFixedSize(200, 90); // Устанавливаем фиксированный размер
    historyButton->setStyleSheet("QPushButton { border-radius: 20px; background-color: #b38dd9; }" // Стиль кнопки
                    "QPushButton:hover { background-color: #7366bd; }" // Эффект наведения
                    "QPushButton:pressed { background-color: #660099; }"); // Эффект при нажатии
    connect(historyButton, &QPushButton::clicked, this, &MainWidget::showHistory);
    buttonLayout->addWidget(historyButton);

    // Добавляем горизонтальный layout с кнопками в вертикальный layout
    mainLayout->addLayout(buttonLayout);

    // Устанавливаем выравнивание всего содержимого по центру
    mainLayout->setAlignment(Qt::AlignTop);
    // Установка layout для окна
    setLayout(mainLayout);


}

void MainWidget::showProfile() {
    ProfileWindow *profileWindow = new ProfileWindow(user, nullptr, dynamic_cast<MainWindow*>(this->window()));
    //mainWindow->showMinimized(); // Сворачиваем главное окно
    profileWindow->show(); // Открываем окно профиля
    profileWindow->activateWindow();

    profileWindow->setFixedSize(260,380);// Установка размеров окна
    profileWindow->move(QGuiApplication::primaryScreen()->availableGeometry().center() - profileWindow->rect().center()); // Открытие по центру экрана
}

void MainWidget::showCreateRequest()
{
    // Создаем экземпляр окна для создания заявки
    CreateRequestWindow *createRequestWindow = new CreateRequestWindow(user, nullptr, dynamic_cast<MainWindow*>(this->window()));
    //mainWindow->showMinimized();
    createRequestWindow->show();
    createRequestWindow->activateWindow();
}


void MainWidget::showActiveRequests()
{
    ActiveRequestsWindow *activeRequestsWindow = new ActiveRequestsWindow(user, nullptr, dynamic_cast<MainWindow*>(this->window()));
    activeRequestsWindow->show();
    activeRequestsWindow->setFixedSize(800,450); // Установка размеров окна
    activeRequestsWindow->move(QGuiApplication::primaryScreen()->availableGeometry().center() - activeRequestsWindow->rect().center()); // Открытие по центру экрана
}

void MainWidget::showHistory()
{
    // Создаем окно истории заявок
    HistoryRequestsWindow *historyWindow = new HistoryRequestsWindow(user, nullptr, dynamic_cast<MainWindow*>(this->window()));
    // Показываем окно истории заявок
    historyWindow->show();
    historyWindow->setFixedSize(800,450); // Установка размеров окна
    historyWindow->move(QGuiApplication::primaryScreen()->availableGeometry().center() - historyWindow->rect().center()); // Открытие по центру экрана
}

// Ваш обработчик события изменения размера окна
void MainWidget ::resizeEvent(QResizeEvent *event)
{
    // Вызываем базовый метод для выполнения стандартного поведения
    QWidget::resizeEvent(event);

    // Вычисляем новый размер кнопки относительно размеров окна
    buttonsWidth = mainWindow->width() / 4.5; // Например, устанавливаем ширину кнопки как 1/5 ширины окна
    buttonsHeight = mainWindow->height() / 8; // Например, устанавливаем ширину кнопки как 1/5 ширины окна

    // Устанавливаем новый размер кнопки
    profileButton->setFixedSize(buttonsWidth, buttonsHeight); // Устанавливаем размер кнопки
    historyButton->setFixedSize(buttonsWidth, buttonsHeight); // Устанавливаем размер кнопки
    createRequestButton->setFixedSize(buttonsWidth, buttonsHeight); // Устанавливаем размер кнопки
    activeRequestsButton->setFixedSize(buttonsWidth, buttonsHeight); // Устанавливаем размер кнопки
}

