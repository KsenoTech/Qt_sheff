QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activerequestswindow.cpp \
    createrequestwindow.cpp \
    historyrequestswindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    profilewindow.cpp

HEADERS += \
    User.h \
    activerequestswindow.h \
    createrequestwindow.h \
    historyrequestswindow.h \
    loginwindow.h \
    mainwidget.h \
    mainwindow.h \
    profilewindow.h \
    requestlistitem.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Icons/ExitIcon.png \
    Icons/HistoryIcon.png \
    Icons/InProgresIcon.png \
    Icons/MenuIcon.png \
    Icons/OrderIcon.png \
    Icons/ProfileIcon.png \
    Icons/logo.ico \
    Icons/logo.png \
    Images/Own_Logo.png \
    Images/client.png \
    Images/execu.png \
    Images/fon.png

RESOURCES += \
    Images.qrc
