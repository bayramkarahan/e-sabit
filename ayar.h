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
#include<QCheckBox>
#include<QProcess>
#include<QProgressDialog>
#include<QToolButton>

#ifndef AYAR_H
#define AYAR_H

QWidget *MainWindow::ayar()
{

    QWidget *ayarPage=new QWidget();
     QFont f2( "Arial", 8, QFont::Normal);
    /*******************************************************/
    QStringList ayarlst=fileToList("/usr/local/share/","e-sabit.conf");
    /*******************************************/

               /*************************************************/
    if(listGetLine(ayarlst,"copyState")!="")
    {
       QString strcopyState=listGetLine(ayarlst,"copyState").split("|")[1];
        //qDebug()<<strcopyState;
     copyState=strcopyState.toInt();
    }
     /********************************************************/

    QToolButton *kullaniciYedekleButton= new QToolButton;
    kullaniciYedekleButton->setFixedSize(QSize(boy*3,boy*3));
    kullaniciYedekleButton->setIconSize(QSize(boy*2,boy*2));
    kullaniciYedekleButton->setStyleSheet("Text-align:center");
    kullaniciYedekleButton->setIcon(QIcon(":/icons/backup.svg"));
    kullaniciYedekleButton->setAutoRaise(true);
    kullaniciYedekleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    kullaniciYedekleButton->setFont(f2);
    kullaniciYedekleButton->setText("Kullanıcı Yedekle");

    QLineEdit *kullaniciDizinLineEdit=new QLineEdit(ayarPage);
    kullaniciDizinLineEdit->resize(150,25);
    if(listGetLine(ayarlst,"kullaniciDizin")!="")
        kullaniciDizinLineEdit->setText(listGetLine(ayarlst,"kullaniciDizin").split("|")[1]);

    QLineEdit *kullaniciSifreLineEdit=new QLineEdit;
    kullaniciSifreLineEdit->setEchoMode(QLineEdit::Password);

         if(listGetLine(ayarlst,"kullaniciSifre")!="")
            kullaniciSifreLineEdit->setText(listGetLine(ayarlst,"kullaniciSifre").split("|")[1]);
             QCheckBox *checkboxps = new QCheckBox("Şifre Göster",ayarPage);
         QFont ff( "Arial", 8, QFont::Normal);
         checkboxps->setFont(ff);
         checkboxps->setChecked(false);
         connect(checkboxps, &QCheckBox::clicked, [=]() {
             if(checkboxps->checkState()==Qt::Checked)
             {
                 kullaniciSifreLineEdit->setEchoMode(QLineEdit::Normal);
              // qDebug()<<"check yapıldı";
             }
             if(checkboxps->checkState()==Qt::Unchecked)
             {
                kullaniciSifreLineEdit->setEchoMode(QLineEdit::Password);
                //qDebug()<<"check kaldırıldı";
             }

     });


    connect(kullaniciYedekleButton, &QPushButton::clicked, [=]() {

        //Kullanıcı Yedekle
       kontrol();
       if (status==false) return;

      bool backup= QFile::exists("/usr/local/bin/backup.sh");
      bool restore=QFile::exists("/usr/local/bin/restore.sh");
      bool esabit=QFile::exists("/usr/local/share/e-sabit.conf");
      bool drm=false;
                if(!(backup&&restore&&esabit))
                {
                    QString sonuc=myMessageBox("E-Sabit", "\n"
                                                    "\nKullanıcı Ayarları Kaydedilmemiş..\n"
                                                     "Lütfen Sabitlemek İstenen Kullanıcı Ayarlarını Giriniz.."
                                                    "\n","","","tamam",QMessageBox::Warning);
                         drm=true;
                }
                if (drm) return;
                /**************************************************************/
                       bool kullanicidizin=false;
                        bool kullanicisifre=false;
                        bool drmm=false;
                        if(kullaniciDizinLineEdit->text()!="") kullanicidizin=true;
                        if(kullaniciSifreLineEdit->text()!="") kullanicisifre=true;
                         if(!(kullanicisifre&&kullanicidizin))
                         {
                               QString sonuc=myMessageBox("E-Sabit", "\n"
                                                                   "\nKullanıcı Ayarları Seçilmemiş..\n"
                                                                    "Lütfen Sabitlemek İstenen Kullanıcı Ayarlarını Giriniz.."
                                                                   "\n","","","tamam",QMessageBox::Warning);

                             drmm=true;
                         }
                         if (drmm) return;
                /**********************************************************/


        Qt::WindowFlags flags = 0;
        flags |= Qt::Dialog;
        flags |= Qt::X11BypassWindowManagerHint;

        QMessageBox messageBox(this);
        messageBox.setWindowFlags(flags);
        messageBox.setText("Uyarı\t\t\t");
        messageBox.setInformativeText("Seçili Kullanıcı Yedeklenecek! Emin misiniz?");
        QAbstractButton *evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
        QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
        messageBox.setIcon(QMessageBox::Question);
                messageBox.exec();
                if (messageBox.clickedButton() == evetButton)
                {
                    QStringList liste;
                    liste<<"#!/usr/bin/expect";
                    liste<<"spawn su - "+localUsername->text();
                    liste<<"expect \"Parola:\"";
                    liste<<"send \""+localPassword->text()+"\\n\"";
                    liste<<"send \"echo "+localPassword->text()+"|sudo -S /usr/local/bin/backup.sh\\n\"";
                    liste<<"send \"exit\\n\"";
                    liste<<"interact";
                    listToFile("/home/"+QDir::homePath().split("/")[2]+"/",liste,"run.sh");
                    QString kmt19="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/run.sh";
                    system(kmt19.toStdString().c_str());
                    ///QString kmt20="/home/"+localUsername->text()+"/run.sh";
                    ///system(kmt20.toStdString().c_str());
                    ///  QString result="";
                    QStringList arguments;
                            arguments << "-c" << QString("/home/"+QDir::homePath().split("/")[2]+"/run.sh");
                            QProcess process;
                            process.start("/bin/bash",arguments);
                             if(process.waitForFinished())
                    {
                       // version = process.readAll();
                       //   result.chop(3);
                    }
                    QString kmt21="rm -rf /home/"+QDir::homePath().split("/")[2]+"/run.sh";
                   system(kmt21.toStdString().c_str());

                   QString sonuc=myMessageBox("E-Sabit", "\n"
                                                       "\nKullanıcı Yedeklendi..\n"
                                                         "\n","","","tamam",QMessageBox::Information);


                }



    });
    QPushButton *kullaniciDizinSelectButton= new QPushButton;
    kullaniciDizinSelectButton->setFixedSize(20, 30);
    kullaniciDizinSelectButton->setText("...");
    kullaniciDizinSelectButton->setStyleSheet("Text-align:center");
    //ogrenciZilFileSelectButton->setFlat(true);


    connect(kullaniciDizinSelectButton, &QPushButton::clicked, [=]() {
        QFileDialog dialog(this);
          dialog.setFileMode(QFileDialog::Directory);
    QString dir = QFileDialog::getExistingDirectory(this, tr("Klasör Aç"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
        kullaniciDizinLineEdit->setText(dir);
 });

/************************************************************************/
    QToolButton *yedekKullaniciYukleButton= new QToolButton;
    yedekKullaniciYukleButton->setFixedSize(QSize(boy*3,boy*3));
    yedekKullaniciYukleButton->setIconSize(QSize(boy*2,boy*2));
    yedekKullaniciYukleButton->setStyleSheet("Text-align:center");
    yedekKullaniciYukleButton->setIcon(QIcon(":/icons/restore.svg"));
    yedekKullaniciYukleButton->setAutoRaise(true);
    yedekKullaniciYukleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    yedekKullaniciYukleButton->setFont(f2);
    yedekKullaniciYukleButton->setText("Yedeği Geri Yükle");

     /************************************************************************/

     connect(yedekKullaniciYukleButton, &QPushButton::clicked, [=]() {

         //yedek kullanıcıyı geri yükle
         kontrol();
         if (status==false) return;
         bool backup= QFile::exists("/usr/local/bin/backup.sh");
         bool restore=QFile::exists("/usr/local/bin/restore.sh");
         bool esabit=QFile::exists("/usr/local/share/e-sabit.conf");
         bool drm=false;
                   if(!(backup&&restore&&esabit))
                   {
                             QString sonuc=myMessageBox("E-Sabit", "\n"
                                                             "\nKullanıcı Ayarları Kaydedilmemiş..\n"
                                                              "Lütfen Sabitlemek İstenen Kullanıcı Ayarlarını Giriniz.."
                                                             "\n","","","tamam",QMessageBox::Warning);

                       drm=true;
                   }
                   if (drm) return;
                   /**************************************************************/
                           bool kullanicidizin=false;
                           bool kullanicisifre=false;
                           bool drmm=false;
                           if(kullaniciDizinLineEdit->text()!="") kullanicidizin=true;
                           if(kullaniciSifreLineEdit->text()!="") kullanicisifre=true;
                            if(!(kullanicisifre&&kullanicidizin))
                            {
                                QString sonuc=myMessageBox("E-Sabit", "\n"
                                                                      "\nKullanıcı Ayarları Seçilmemiş..\n"
                                                                       "Lütfen Sabitlemek İstenen Kullanıcı Ayarlarını Giriniz.."
                                                                      "\n","","","tamam",QMessageBox::Warning);

                                      drmm=true;
                            }
                            if (drmm) return;
                   /**********************************************************/
         QString sonuc=myMessageBox("Uyarı","Yedeklenen Kullanıcı Geri Yüklenecek! Emin misiniz?","evet","hayir","",QMessageBox::Question);
         if (sonuc == "evet")
                 {
                     QStringList liste;
                     liste<<"#!/usr/bin/expect";
                     liste<<"spawn su - "+localUsername->text();
                     liste<<"expect \"Parola:\"";
                     liste<<"send \""+localPassword->text()+"\\n\"";
                     liste<<"send \"echo "+localPassword->text()+"|sudo -S /usr/local/bin/restore.sh\\n\"";
                     liste<<"send \"exit\\n\"";
                     liste<<"interact";
                     listToFile("/home/"+QDir::homePath().split("/")[2]+"/",liste,"run.sh");
                     QString kmt19="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/run.sh";
                     system(kmt19.toStdString().c_str());
                       QStringList arguments;
                             arguments << "-c" << QString("/home/"+QDir::homePath().split("/")[2]+"/run.sh");
                             QProcess process;
                             process.start("/bin/bash",arguments);
                              if(process.waitForFinished())
                     {
                        // version = process.readAll();
                        //   result.chop(3);
                     }
                    QString kmt21="rm -rf /home/"+QDir::homePath().split("/")[2]+"/run.sh";
                    system(kmt21.toStdString().c_str());

                           QString sonuc=myMessageBox("E-Sabit", "\n"
                                                               "\nKullanıcı Ayarları Geri Yedeklendi..\n"
                                                                 "\n","","","tamam",QMessageBox::Information);

                 }



     });


    QToolButton *ayarKaydetButton= new QToolButton;
    ayarKaydetButton->setFixedSize(QSize(boy*3,boy*3));
    ayarKaydetButton->setIconSize(QSize(boy*2,boy*2));
    ayarKaydetButton->setStyleSheet("Text-align:center");
    ayarKaydetButton->setIcon(QIcon(":/icons/save.svg"));
    ayarKaydetButton->setAutoRaise(true);
    ayarKaydetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ayarKaydetButton->setFont(f2);
    ayarKaydetButton->setText("Ayarları Kaydet");

    connect(ayarKaydetButton, &QPushButton::clicked, [=]() {
        kontrol();
        if (status==false) return;
/**************************************************************/
        bool kullanicidizin1=false;
        bool kullanicisifre1=false;
        bool drmm1=false;
        if(kullaniciDizinLineEdit->text()!="") kullanicidizin1=true;
        if(kullaniciSifreLineEdit->text()!="") kullanicisifre1=true;
         if(!(kullanicisifre1&&kullanicidizin1))
         {
             QMessageBox::information(this,"E-Sabit",
                                     "\n"
                                     "\nKullanıcı Ayarları Seçilmemiş..\n"
                                      "Lütfen Sabitlemek İstenen Kullanıcı Ayarlarını Giriniz.."
                                     "\n");
             drmm1=true;
         }
         if (drmm1) return;

         kullaniciSifreLineEdit->setEchoMode(QLineEdit::Password);///şifre gizleniyor
         checkboxps->setChecked(false);

/***********************e-sabit.conf oluşturuluyor***********************************/
         QStringList ayarlist;
        ayarlist.append("kullaniciDizin|"+kullaniciDizinLineEdit->text());
        ayarlist.append("copyState|"+QString::number(copyState));
        ayarlist.append("kullaniciSifre|"+kullaniciSifreLineEdit->text());
        listToFile("/home/"+QDir::homePath().split("/")[2]+"/",ayarlist,"e-sabit.conf");
        QString kmt18="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/e-sabit.conf";
        system(kmt18.toStdString().c_str());
        QString yedekuser=kullaniciDizinLineEdit->text().split("/")[2];
/*******************************restore.sh oluştuluyor**************/
        QStringList restore;
        restore<<"#!/bin/bash";
        ///restore<<"rm -rf /home/"+yedekuser;
        restore<<"rsync -apoglr --delete /var/backups/"+yedekuser+"/ /home/"+yedekuser+"/";
        //restore<<"chown -R "+yedekuser+":"+yedekuser+" /home/"+yedekuser+"/";
        restore<<"echo "+yedekuser+":"+kullaniciSifreLineEdit->text()+"|chpasswd";
        listToFile("/home/"+QDir::homePath().split("/")[2]+"/",restore,"restore.sh");
        QString kmt19="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/restore.sh";
        system(kmt19.toStdString().c_str());
/***************************backup.sh oluşturuldu******************************************/
        QStringList backup;
        backup<<"#!/bin/bash";
        ///backup<<"rm -rf /var/backups/"+yedekuser;
        backup<<"rsync -apoglr --delete /home/"+yedekuser +" /var/backups/";
        listToFile("/home/"+QDir::homePath().split("/")[2]+"/",backup,"backup.sh");
        QString kmt20="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/backup.sh";
        system(kmt20.toStdString().c_str());

/*****************************E-Sabit.service********************************/
        if(QString::number(copyState)=="1")
        {
            QStringList liste;
            liste<<"#!/usr/bin/expect";
            liste<<"spawn su - "+localUsername->text();
            liste<<"expect \"Parola:\"";
            liste<<"send \""+localPassword->text()+"\\n\"";
            liste<<"send \""+localPassword->text()+"\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S cp /home/"+QDir::homePath().split("/")[2]+"/restore.sh /usr/local/bin/\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S cp /home/"+QDir::homePath().split("/")[2]+"/backup.sh /usr/local/bin/\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S chmod 777 /usr/local/bin/restore.sh\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S chmod 777 /usr/local/bin/backup.sh\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S /bin/bash /usr/local/bin/backup.sh\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S cp /home/"+QDir::homePath().split("/")[2]+"/e-sabit.conf /usr/local/share/\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S chmod 777 /usr/local/share/e-sabit.conf\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S systemctl enable E-Sabit.service\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S systemctl start E-Sabit.service\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S systemctl daemon-reload\\n\"";
            liste<<"send \"exit\\n\"";
            liste<<"interact";
            listToFile("/home/"+QDir::homePath().split("/")[2]+"/",liste,"run.sh");

        }else{
            QStringList liste;
            liste<<"#!/usr/bin/expect";
            liste<<"spawn su - "+localUsername->text();
            liste<<"expect \"Parola:\"";
            liste<<"send \""+localPassword->text()+"\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S cp /home/"+QDir::homePath().split("/")[2]+"/restore.sh /usr/local/bin/\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S cp /home/"+QDir::homePath().split("/")[2]+"/backup.sh /usr/local/bin/\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S chmod 777 /usr/local/bin/restore.sh\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S chmod 777 /usr/local/bin/backup.sh\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S /bin/bash /usr/local/bin/backup.sh\\n\"";

            liste<<"send \"echo "+localPassword->text()+"|sudo -S cp /home/"+QDir::homePath().split("/")[2]+"/e-sabit.conf /usr/local/share/\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S chmod 777 /usr/local/share/e-sabit.conf\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S systemctl stop E-Sabit.service\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S systemctl disable E-Sabit.service\\n\"";
            liste<<"send \"echo "+localPassword->text()+"|sudo -S systemctl daemon-reload\\n\"";

             liste<<"send \"exit\\n\"";
            liste<<"interact";
            listToFile("/home/"+QDir::homePath().split("/")[2]+"/",liste,"run.sh");


        }
        QString kmt22="chmod 777 /home/"+QDir::homePath().split("/")[2]+"/run.sh";
        system(kmt22.toStdString().c_str());
       /* QStringList arguments1;
              arguments1 << "-c" << QString("/home/"+QDir::homePath().split("/")[2]+"/backup.sh");
              QProcess process1;
              process1.start("/bin/bash",arguments1);
               if(process1.waitForFinished())
      {
         // version = process.readAll();
         //   result.chop(3);
      }*/
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

        QString kmt24="rm -rf /home/"+QDir::homePath().split("/")[2]+"/run.sh";
        system(kmt24.toStdString().c_str());

        QString kmt25="rm -rf /home/"+QDir::homePath().split("/")[2]+"/restore.sh";
        system(kmt25.toStdString().c_str());

        QString kmt26="rm -rf /home/"+QDir::homePath().split("/")[2]+"/backup.sh";
        system(kmt26.toStdString().c_str());

        QString kmt27="rm -rf /home/"+QDir::homePath().split("/")[2]+"/e-sabit.conf";
        system(kmt27.toStdString().c_str());


      /***************************************************************************/
        QString sonuc=myMessageBox("E-Sabit", "\n"
                                            "\nAyarlar Kaydedildi..\n"
                                              "\n","","","tamam",QMessageBox::Information);

    });



    QCheckBox *checkbox = new QCheckBox("Her Açılışta Kullanıcı Bilgileri Yedekten Yüklensin.",ayarPage);
    QFont f1( "Arial", 8, QFont::Normal);
    checkbox->setFont(f1);
    checkbox->setChecked(copyState);
   /// qDebug()<<"copystate1"<<copyState;
    connect(checkbox, &QCheckBox::clicked, [=]() {
        copyState=checkbox->checkState();
       // qDebug()<<copyState;
});


    auto layout = new QGridLayout(ayarPage);
    layout->setContentsMargins(0, 0, 0,0);
   /// layout->setVerticalSpacing(5);
   /// layout->setColumnMinimumWidth(0, 37);
    //layout->addWidget(adLabel, 2,0,1,2);

    layout->addWidget(new QLabel("<font size=2>Yedeklenecek Kullanıcı Dizini</font>"), 10,0,1,1);
    layout->addWidget(kullaniciDizinLineEdit, 10,1,1,1);
    layout->addWidget(kullaniciDizinSelectButton, 10,2,1,1);

    layout->addWidget(new QLabel("<font size=2>Kullanıcı Şifresi</font>"), 15,0,1,1);
    layout->addWidget(kullaniciSifreLineEdit, 15,1,1,1);
    layout->addWidget(checkboxps, 16,1,1,1);

    layout->addWidget(checkbox,20,0,1,3);
    QHBoxLayout *layout1 = new QHBoxLayout;
         layout1->addWidget(kullaniciYedekleButton);
         layout1->addWidget(yedekKullaniciYukleButton);
         layout1->addWidget(ayarKaydetButton);
         layout->addLayout(layout1, 30, 0,1,3,Qt::AlignHCenter);


///layout->setColumnStretch(6, 255);

    return ayarPage;
}
#endif // AYAR_H
