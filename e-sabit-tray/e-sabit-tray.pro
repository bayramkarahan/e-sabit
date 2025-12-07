#-------------------------------------------------
#
# Project created by QtCreator 2023
#-------------------------------------------------

QT += widgets network core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = e-sabit-tray
TEMPLATE = app


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    singleinstance.cpp

HEADERS += \
        mainwindow.h \
    singleinstance.h


RESOURCES += \
    resources.qrc


DEFINES += QT_DEPRECATED_WARNINGS

target.path = /usr/bin

icon.files = icons/e-sabit.svg
icon.path = /usr/share/icons

auto_start.files = autostartesabittray.desktop
auto_start.path = /etc/xdg/autostart/

INSTALLS += target icon  auto_start

DISTFILES += \
    autostartesabittray.desktop
