#-------------------------------------------------
#
# Project created by QtCreator 2019-07-02T00:29:01
#
#-------------------------------------------------

QT       += widgets  xml network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = e-sabit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    singleinstance.cpp

HEADERS += \
        mainwindow.h \
    filecrud.h \
    ayar.h \
    singleinstance.h \
    giris.h \
    hakkinda.h

FORMS +=

RESOURCES += \
    resources.qrc


target.path = /usr/bin

desktop_file.files = e-sabit.desktop
desktop_file.path = /usr/share/applications/

icon.files = icons/sabit.svg
icon.path = /usr/share/e-sabit

auto_start.files = e-sabit.desktop
auto_start.path = /etc/xdg/autostart/

INSTALLS += target desktop_file icon auto_start
