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
#include<filecrud.h>
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
#include<QAuthenticator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
    trayIcon=new QSystemTrayIcon(this);
    this->resize(340,300);
   setFixedWidth(340);
   setFixedHeight(300);
    setWindowTitle("E-Sabit 1.0");
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()/2 - this->width()/2);
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->setStyleSheet("background-color: #dfdfdf;");


      //*******************tray***********************************/
      // Tray icon menu
      auto menu = this->createMenu();
      this->trayIcon->setContextMenu(menu);

      // App icon
      auto appIcon = QIcon(":/icons/sabit.svg");
      this->trayIcon->setIcon(appIcon);
      this->setWindowIcon(appIcon);

      // Displaying the tray icon
      this->trayIcon->show();     // Note: without explicitly calling show(), QSystemTrayIcon::activated signal will never be emitted!

      // Interaction
      connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
     // gizle();

      timergizle = new QTimer(this);
      connect(timergizle, SIGNAL(timeout()), this, SLOT(gizle()));
      timergizle->start(1);

      /************************************************************/
        QTabWidget *tw=new QTabWidget(this);
        tw->resize(this->width(),this->height());
        tw->addTab(giris(),"");
        tw->addTab(ayar(),"Ayarlar");
        tw->addTab(hakkinda(),"Hakkında");




      //


}

void MainWindow::kontrol()
{
    status=true;
    /********************password null text kontrol********************************/
     if(localPassword->text()=="")
    {
          QString sonuc=myMessageBox("E-Sabit", "\n"
                                                     "\nLütfen Şifre Giriniz..\n"
                                                       "\n","","","tamam",QMessageBox::Critical);

        status=false;
        return;
    }
    /*********************sudo yetki kontrol*************************/
   sudoYetkiKontolSlot();
     if(sudoyetki=="0")
    { QString sonuc=myMessageBox("E-Sabit", "\n"
                                            "\nLütfen Yetkili Bir Kullanıcı ile Kurulum Yapınız...\n"
                                              "\n","","","tamam",QMessageBox::Critical);

         status=false;
        return;
    }

    /*************************şifre kontrol***********************/
   passwordKontrolSlot();
   if(passwordstatus=="0")
    {
       QString sonuc=myMessageBox("E-Sabit", "\n"
                                           "\nLütfen Şifrenizi Doğru Giriniz..\n"
                                             "\n","","","tamam",QMessageBox::Critical);

        status=false;
        return;
    }


}
void MainWindow::sudoYetkiKontolSlot()
{
    user=localUsername->text();///Burası Önemli
    /*******************sudo yetki kontrol**************************/
    QStringList arguments1;
    arguments1 << "-c" << QString("id "+user+"|grep 'sudo'");
    QProcess process1;
    process1.start("/bin/bash",arguments1);
    if(process1.waitForFinished())
    {
        sudoyetki = process1.readAll();
        if (sudoyetki=="") sudoyetki="0";else sudoyetki="1";
        //   result.chop(3);
    }
    //qDebug()<<"sudoyetki:"<<sudoyetki;
}
void MainWindow::passwordKontrolSlot()
{
    /***************password kontrol***************************/

QStringList liste;
liste<<"#!/usr/bin/expect";
liste<<"spawn su - "+localUsername->text();
liste<<"expect \"Parola:\"";
liste<<"send \""+localPassword->text()+"\\n\"";
liste<<"send \"echo "+localPassword->text()+"|sudo -S touch /home/"+QDir::homePath().split("/")[2]+"/sabit\\n\"";
liste<<"send \"echo "+localPassword->text()+"|sudo -S chmod 777 /home/"+QDir::homePath().split("/")[2]+"/sabit\\n\"";
liste<<"send \"echo "+localPassword->text()+"|sudo -S chown "+QDir::homePath().split("/")[2]+" /home/"+QDir::homePath().split("/")[2]+"/sabit\\n\"";
liste<<"send \"exit\\n\"";
liste<<"interact";
listToFile("/home/"+QDir::homePath().split("/")[2]+"/",liste,"run.sh");
QString kmt19="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/run.sh";
system(kmt19.toStdString().c_str());
QString result="";
QStringList arguments;
        arguments << "-c" << QString("/home/"+QDir::homePath().split("/")[2]+"/run.sh");
        QProcess process;
        process.start("/bin/bash",arguments);
         if(process.waitForFinished())
{
   // version = process.readAll();
   //   result.chop(3);
}


         if(QFile::exists("/home/"+QDir::homePath().split("/")[2]+"/sabit")==true)
                 {
                  passwordstatus="1";

                  ///qDebug()<<"Şifre: doğru "<<passwordstatus;

                 }else
                 {
                     passwordstatus="0";
                    /// qDebug()<<"Şifre: yanlış "<<passwordstatus;
                 }
         QString kmt21="rm -rf /home/"+QDir::homePath().split("/")[2]+"/run.sh";
         system(kmt21.toStdString().c_str());

         QString kmt22="rm -rf /home/"+QDir::homePath().split("/")[2]+"/sabit";
         system(kmt22.toStdString().c_str());
       //  qDebug()<<"Şifre:"<<passwordstatus;

}
QString MainWindow::myMessageBox(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, QMessageBox::Icon icon)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
    flags |= Qt::X11BypassWindowManagerHint;

    QMessageBox messageBox(this);
    messageBox.setWindowFlags(flags);
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
    if(messageBox.clickedButton()==hayirButton) return "hayır";
    if(messageBox.clickedButton()==tamamButton) return "tamam";
    return "";
}

void MainWindow::versionKontrolSlot()
{
    /*********************version kontrol*****************************/
    QString result="";
    QStringList arguments;
            arguments << "-c" << QString("uname -a|awk '{print $3}'");
            QProcess process;
            process.start("/bin/bash",arguments);
             if(process.waitForFinished())
    {
        version = process.readAll();
       //   result.chop(3);
    }

version=version.left(1);
//qDebug()<<"version:"<<version;
}

MainWindow::~MainWindow()
{
  //  delete ui;
}


QStringList MainWindow::listRemove(QStringList list,QString data)
 {
       QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(re)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString MainWindow::listGetLine(QStringList list,QString data)
{
    QRegularExpression re(data);
   for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
   //qDebug()<<list;
   return "";
}
QStringList MainWindow::fileToList(QString path, QString filename)
{
  FileCrud *fcc=new FileCrud();
  fcc->dosya=path+filename;
 // qDebug()<<fcc->dosya;
  QStringList list;
  for(int i=1;i<=fcc->fileCount();i++)
  {
       QString line=fcc->fileGetLine(i);
      // qDebug()<<line;
       if(line!="")
       {
           line.chop(1);
           QStringList lst=line.split("|");
           QString ln="";
           if(lst.count()>0)ln.append(lst[0]);
           if(lst.count()>1)ln.append("|").append(lst[1]);
           if(lst.count()>2)ln.append("|").append(lst[2]);
           if(lst.count()>3)ln.append("|").append(lst[3]);
           if(lst.count()>4)ln.append("|").append(lst[4]);
           if(lst.count()>5)ln.append("|").append(lst[5]);

           list <<ln;
           //qDebug()<<ln;
           // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

       }
  }
     return list;
}
void MainWindow::listToFile(QString path,QStringList list, QString filename)
{
  FileCrud *fcc=new FileCrud();
  fcc->dosya=path+filename;
  fcc->fileRemove();
  for(int i=0;i<list.count();i++)
  {
       QString line=list[i];
       if(line!="")
       {
           //line.chop(1);
           QStringList lst=line.split("|");
           //qDebug()<<line;
           QString ln="";
           if(lst.count()>0)ln.append(lst[0]);
           if(lst.count()>1)ln.append("|").append(lst[1]);
           if(lst.count()>2)ln.append("|").append(lst[2]);
           if(lst.count()>3)ln.append("|").append(lst[3]);
           if(lst.count()>4)ln.append("|").append(lst[4]);
           if(lst.count()>5)ln.append("|").append(lst[5]);

           //qDebug()<<ln;
           fcc->fileWrite(ln);

       }

  }
}


void  MainWindow::gizle()
{
    //hide();
   // qDebug()<<"deded";
    QWidget::hide();
    timergizle->stop();
  }

QMenu* MainWindow::createMenu()
{
  // App can exit via Quit menu
 /* auto quitAction = new QAction("&Kapat", this);
  connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
  auto ayarAction = new QAction("&Ayarlar", this);
  connect(ayarAction, &QAction::triggered, qApp, gizle());
*/


    auto minimizeAction = new QAction(tr("Gi&zle"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

   /* auto maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);
*/
    auto restoreAction = new QAction(tr("&Ayarlar"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

   /// auto quitAction = new QAction(tr("&Kapat"), this);
   /// connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    auto menu = new QMenu(this);
    //menu->addAction(quitAction)


    menu->addAction(minimizeAction);
    //menu->addAction(maximizeAction);
    menu->addAction(restoreAction);
    menu->addSeparator();
    //menu->addAction(quitAction);

   // trayIcon = new QSystemTrayIcon(this);
    //trayIcon->setContextMenu(trayIconMenu);

    //;

  return menu;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
    this->trayIcon->showMessage("E-Sabit", "Kalıcı Kullanıcı Sistemi!");
    break;
  default:
    ;
  }
}

void MainWindow::WidgetClosed()
{
    QWidget::hide();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
     emit WidgetClosed();
     //QWidget::hide();
     event->ignore();

}
