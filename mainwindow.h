/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include<QLineEdit>
#include<QSystemTrayIcon>
#include<QPushButton>
#include<QMessageBox>
#include <QGuiApplication>
#include<QTextDocument>
#include<QPrinter>
#include<QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
virtual void closeEvent ( QCloseEvent * event );

public slots:

    void  WidgetClosed();
    void listToFile(QString path, QStringList list, QString filename);
    QStringList fileToList(QString path,QString filename);
    QString listGetLine(QStringList list, QString data);
    QStringList listRemove(QStringList list, QString data);
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void gizle();
    void kontrol();
    bool passwordKontrolSlot();
    void versionKontrolSlot();
    QString myMessageBox(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, QMessageBox::Icon icon);
    void  widgetShow();
    void ayarKaydetButtonSlot();
    void yedekStatus();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    QWidget *wid;
    Ui::MainWindow *ui;
    QWidget *ayar();
    QWidget *aw;
     QTabWidget *tw;
    QWidget *giris();
    QWidget *hakkinda();
    QWidget *qww;
    int boy=30;

     bool copyState;
     QString version;
     QString user;
     QString passwordstatus;
     bool status;

    QStringList ayarlst;
    QTimer *timergizle;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    QMenu* createMenu();

    QLineEdit *kullaniciDizinLineEdit;
    QCheckBox *checkbox;
    int fnt=10;
    QLabel *labelYedekStatus;
};

#endif // MAINWINDOW_H
