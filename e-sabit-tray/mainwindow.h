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
#include<QProcess>
#include<QTime>
#include<QThread>
#include<QTimer>
#include<QEventLoop>
#include<QLabel>
#include<filecrud.h>
#include<QSize>
#include<QScreen>
#include<QTableWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
virtual void closeEvent ( QCloseEvent * event );

public slots:
   // QWidget ayar();
    void listToFile(QStringList list, QString filename);
    QStringList fileToList(QString filename);
    QString listGetLine(QStringList list,QString data);
    QStringList listRemove(QStringList list,QString data);
    QStringList listReplace(QStringList list,QString oldData,QString newData,int index);
    QStringList listMerge(QStringList list1, QStringList list2,int dataIndex);
    QStringList listGetList(QStringList list, QString data,int index);

    void iconActivated(QSystemTrayIcon::ActivationReason);
    void gizle();
    void WidgetClosed();
      void  widgetShow();
         void resetStatus()
          {
          task1State=false;
          task2State=false;
          task3State=false;
          task4State=false;
          task5State=false;
          };
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
      bool task1State=false;
      bool task2State=false;
      bool task3State=false;
      bool task4State=false;
      bool task5State=false;

     QTableWidget *twl;
     QString localDir;
     QStringList ayarlist;

     QString trn;
     QString gun;
     QString currentsaat;
     QString tempCurrentsaat;

    Ui::MainWindow *ui;
     QTabWidget *tw;
     QString currentsaatState;

    QTimer *timerGorevBaslama;

    QEventLoop loop;
    QTimer timer1;

    QTimer *timergizle;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    bool tenefusYayin;
    QMenu* createMenu();
    int en,boy;
};

#endif // MAINWINDOW_H
