#-------------------------------------------------
#
# Project created by QtCreator 2019-07-02T00:29:01
#
#-------------------------------------------------

QT       += widgets core gui  printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = e-sabit-gui
TEMPLATE = app

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    filecrud.h \
    ayar.h \
    giris.h \
    hakkinda.h

FORMS +=

RESOURCES += \
    resources.qrc
target.path = /usr/bin

desktop_file.files = e-sabit.desktop
desktop_file.path = /usr/share/applications/

icon.files = icons/e-sabit.svg
icon.path = /usr/share/e-sabit

auto_start.files = e-sabit.desktop
auto_start.path = /etc/xdg/autostart/

service.files = e-sabit.service
service.path = /lib/systemd/system/

backup.files = backup.sh
backup.path = /usr/share/e-sabit

restoreservice.files = restoreservice.sh
restoreservice.path = /usr/share/e-sabit

restorebutton.files = restorebutton.sh
restorebutton.path = /usr/share/e-sabit

INSTALLS += target desktop_file icon auto_start service backup restoreservice restorebutton

DISTFILES += \
    e-sabit.service\
    e-sabit.desktop\
    icons/e-sabit.svg\
    backup.sh\
    restoreservice.sh\
    restorebutton.sh

