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

#include "mainwindow.h"
#include<QTabWidget>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<QFile>
#include<QFileDialog>
#include<QRegularExpression>

#include<QTimeEdit>
#include<QDate>
#include<QTimer>
#include<QTime>
#include<QMessageBox>
#include<ayar.h>
#include<giris.h>
#include<hakkinda.h>
#include<QApplication>
#include<QDesktopWidget>
#include<QMenu>
#include<QCloseEvent>
#include<QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
#ifdef Q_OS_LINUX
    // qDebug()<< "Linux version";
     localDir="/usr/share/e-sabit/";
#endif

#ifdef Q_OS_WIN
    // qDebug()<< "Windows version";
    localDir = QCoreApplication::applicationDirPath() + "/";
#endif



    QRect screenGeometry = QApplication::desktop()->screenGeometry();
   // qDebug()<<"boy:"<<screenGeometry.width()/34;
    boy=screenGeometry.height()/25;
    fnt=(boy/5)*2;
   // qDebug()<<"fnt:"<<fnt;
    setFixedWidth(boy*15);
    setFixedHeight(boy*10);
    int x = (screenGeometry.width()/2 - this->width()/2);
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->setStyleSheet("background-color: #dfdfdf;");

      // App icon
      auto appIcon = QIcon(":/icons/e-sabit.svg");
      this->setWindowIcon(appIcon);

      QProcess process;
      process.start("/bin/bash", {"-c", "dpkg -s e-sabit | grep -i '^Version:' | awk '{print $2}'"});
      process.waitForFinished();

      QString version = QString::fromUtf8(process.readAll()).trimmed();
      setWindowTitle("e-sabit " + version);


      labelYedekStatus=new QLabel();///ayar nesnesinden önce olmalıdır
      labelYedekStatus->setFixedSize(this->width(),boy);
       rb0=new QRadioButton();
       rb1=new QRadioButton();
      aw=ayar();

      /************************************************************/
        tw=new QTabWidget(this);
        tw->resize(this->width(),this->height());

        tw->addTab(giris(),QIcon(":/icons/about.svg"),"Bilgilendirme");
        tw->addTab(aw,QIcon(":/icons/settings.svg"),"Ayarlar");
        tw->addTab(hakkinda(),QIcon(":/icons/lisans.svg"),"Lisans");

      tw->setStyleSheet("Text-align:left; font-size:"+QString::number(fnt-2)+"px;");

}



QString MainWindow::myMessageBox(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, QMessageBox::Icon icon)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
   flags |= Qt::X11BypassWindowManagerHint;

    QMessageBox messageBox(this);
   //messageBox.setWindowFlags(flags);
    messageBox.setText(baslik+"\t\t\t");
    messageBox.setInformativeText(mesaj);
    QAbstractButton *evetButton;
    QAbstractButton *hayirButton;
    QAbstractButton *tamamButton;

    if(evet=="evet") evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
    if(hayir=="hayir") hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
    if(tamam=="tamam") tamamButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);

    messageBox.setIcon(icon);
    messageBox.exec();
    if(messageBox.clickedButton()==evetButton) return "evet";
    if(messageBox.clickedButton()==hayirButton) return "hayir";
    if(messageBox.clickedButton()==tamamButton) return "tamam";
    return "";
}



MainWindow::~MainWindow()
{
  //  delete ui;
}

