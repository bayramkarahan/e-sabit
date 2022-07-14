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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
    trayIcon=new QSystemTrayIcon(this);
    //   this->resize(360,300);
    setWindowTitle("e-sabit 2.1");
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
   // qDebug()<<"boy:"<<screenGeometry.width()/34;
    boy=screenGeometry.width()/34;
    fnt=(boy/5)*2;
   // qDebug()<<"fnt:"<<fnt;
    setFixedWidth(boy*12.3);
    setFixedHeight(boy*10);
    int x = (screenGeometry.width()/2 - this->width()/2);
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->setStyleSheet("background-color: #dfdfdf;");

      //*******************tray***********************************/
      // Tray icon menu
      auto menu = this->createMenu();
      this->trayIcon->setContextMenu(menu);

      // App icon
      auto appIcon = QIcon(":/icons/e-sabit.svg");
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
      labelYedekStatus=new QLabel();///ayar nesnesinden önce olmalıdır
      labelYedekStatus->setFixedSize(this->width(),boy);
       rb0=new QRadioButton();
       rb1=new QRadioButton();
      aw=ayar();

      aw->setEnabled(false);

      /************************************************************/
        tw=new QTabWidget(this);
        tw->resize(this->width(),this->height());

        tw->addTab(giris(),QIcon(":/icons/about.svg"),"Bilgilendirme");
        tw->addTab(aw,QIcon(":/icons/settings.svg"),"Ayarlar");
        tw->addTab(hakkinda(),QIcon(":/icons/lisans.svg"),"Lisans");

      tw->setStyleSheet("Text-align:left; font-size:"+QString::number(fnt-2)+"px;");

}


bool MainWindow::passwordKontrolSlot(QString kmt)
{
    system(kmt.toStdString().c_str());
    if(QFile::exists("/usr/share/e-sabit/sabit")==true)
    {  
        system("rm -rf /usr/share/e-sabit/sabit");
       // qDebug()<<"Şifre: doğru ";
        return true;
    }else
    {
      // qDebug()<<"Şifre: yanlış ";
        return false;
    }
return false;
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

  /********************file permission*************************/
     QFile file(path+filename);
      if (file.open(QFile::ReadWrite)){
              if(!file.setPermissions(QFileDevice::WriteUser | QFileDevice::ReadUser|QFileDevice::ExeUser|
                                      QFileDevice::WriteOwner | QFileDevice::ReadOwner|QFileDevice::ExeOwner|
                                      QFileDevice::WriteGroup | QFileDevice::ReadGroup|QFileDevice::ExeGroup|
                                      QFileDevice::WriteOther | QFileDevice::ReadOther|QFileDevice::ExeOther)){
                  qDebug()<< "Error in permissions";
               }
              file.close();
      }
  /***********************************************/
}


void  MainWindow::gizle()
{
    aw->setEnabled(false);
    tw->setCurrentIndex(0);
    QWidget::hide();
    timergizle->stop();

}
void  MainWindow::widgetShow()
{
    if(passwordKontrolSlot("pkexec sh -c 'touch /usr/share/e-sabit/sabit'"))
    {
        aw->setEnabled(true);
        tw->setCurrentIndex(1);
        this->showNormal();
    }
}

QMenu* MainWindow::createMenu()
{
    auto closeAction = new QAction(tr("Ka&pat"), this);
    connect( closeAction, SIGNAL(triggered()), this, SLOT(widgetClose()));

    auto minimizeAction = new QAction(tr("Gi&zle"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    auto restoreAction = new QAction(tr("&Ayarlar"), this);
    connect( restoreAction, SIGNAL(triggered()), this, SLOT(widgetShow()));

    auto menu = new QMenu(this);
    menu->addAction(closeAction);
    menu->addAction(minimizeAction);
    menu->addAction(restoreAction);
    menu->addSeparator();

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

void MainWindow::widgetClose()
{
         if(passwordKontrolSlot("pkexec sh -c 'touch /usr/share/e-sabit/sabit'"))
        {
QCoreApplication::exit(0);
        }

}

void MainWindow::WidgetClosed()
{
        tw->setCurrentIndex(0);
        QWidget::hide();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
     emit WidgetClosed();
     event->ignore();

}



