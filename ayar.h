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
#include<QFileInfo>

#ifndef AYAR_H
#define AYAR_H
void MainWindow::yedekStatus()
{
    if(kullaniciDizinLineEdit->text()!=""&&QFile::exists("/var/backups/"+kullaniciDizinLineEdit->text().split("/")[2])==true){
        QDateTime local(QFileInfo("/var/backups/"+kullaniciDizinLineEdit->text().split("/")[2]).lastRead());
       // qDebug() << "Local time is:" << local.toString("yyyy-MM-dd HH:mm:ss");
       labelYedekStatus->setText("Kullanıcı Yedeği Var\tYedeklenme Zamanı: "+local.toString("yyyy-MM-dd HH:mm:ss"));
       labelYedekStatus->setStyleSheet("Text-align:center; background-color:rgba(0, 255, 0, 100); font-size:"+QString::number(fnt-2)+"px;");

    }
   else{
       labelYedekStatus->setText("Kullanıcı Yedeği Yok! --> Kullanıcı Yedekle Seçeneği İle Yedek Alın..");
       labelYedekStatus->setStyleSheet("Text-align:center; background-color:rgba(255, 0, 0, 100); font-size:"+QString::number(fnt-2)+"px;");

   }

}

void MainWindow::ayarKaydetButtonSlot()
{
    /**************************************************************/
        bool drmm1=false;
         if(kullaniciDizinLineEdit->text()=="")
       {
           QMessageBox::information(this,"E-Sabit",
                                   "\n"
                                   "\nKullanıcı Ayarları Seçilmemiş..\n"
                                    "Lütfen Sabitlemek İstenen Kullanıcı Ayarlarını Giriniz.."
                                   "\n");
           drmm1=true;
       }
       if (drmm1) return;

/***********************e-sabit.conf oluşturuluyor***********************************/
       system("mv /usr/share/e-sabit/e-sabit.conf /usr/share/e-sabit/e-sabit.conf.old");
       QStringList ayarlist;
      ayarlist.append("kullaniciDizin|"+kullaniciDizinLineEdit->text());
      ayarlist.append("copyState|"+QString::number(copyState));
    //  ayarlist.append("kullaniciSifre|"+kullaniciSifreLineEdit->text());
      listToFile("/usr/share/e-sabit/",ayarlist,"e-sabit.conf");
      /********************file permission*************************/

          QString yuser=kullaniciDizinLineEdit->text().split("/")[2];

 /*******************************restore.sh oluştuluyor**************/
           system("mv /usr/share/e-sabit/restore.sh /usr/share/e-sabit/restore.sh.old");
          QStringList restorelist;
          restorelist.append("#!/bin/bash");
          restorelist.append("rsync -apoglr --delete /var/backups/"+yuser+"/ /home/"+yuser+"/");
          restorelist.append("chown -R "+yuser+":"+yuser+" /home/"+yuser+"/");
          restorelist.append("chmod -R 744 /home/"+yuser+"/");
          listToFile("/usr/share/e-sabit/",restorelist,"restore.sh");


/***************************backup.sh oluşturuldu******************************************/
         system("mv /usr/share/e-sabit/backup.sh /usr/share/e-sabit/backup.sh.old");
          QStringList backuplist;
          backuplist.append("#!/bin/bash");
           backuplist.append("mkdir /var/backups");
          backuplist.append("rsync -apoglr --delete /home/"+yuser+"/ /var/backups/"+yuser+"/");
          listToFile("/usr/share/e-sabit/",backuplist,"backup.sh");
         /******************************************************************/
          system("pkexec sh -c 'touch /usr/share/e-sabit/sabit&&chown root /usr/share/e-sabit/restore.sh&&chown root /usr/share/e-sabit/backup.sh&&chmod 744 /usr/share/e-sabit/restore.sh&&chmod 744 /usr/share/e-sabit/backup.sh'");
           if(QFile::exists("/usr/share/e-sabit/sabit")==true)
           {

               system("rm -rf /usr/share/e-sabit/sabit");
               //qDebug()<<"Şifre: doğru-kaydet "
           }else
           {
                //qDebug()<<"Şifre: yanlış-kaydet "
               system("rm -rf /usr/share/e-sabit/restore.sh");
               system("rm -rf /usr/share/e-sabit/backup.sh");
               system("rm -rf /usr/share/e-sabit/e-sabit.conf");
               system("rm -rf /usr/share/e-sabit/sabit");

               system("mv /usr/share/e-sabit/e-sabit.conf.old /usr/share/e-sabit/e-sabit.conf");
               system("mv /usr/share/e-sabit/restore.sh.old /usr/share/e-sabit/restore.sh");
               system("mv /usr/share/e-sabit/backup.sh.old /usr/share/e-sabit/backup.sh");
               QStringList ayarlstcopy=fileToList("/usr/share/e-sabit/","e-sabit.conf");

               if(listGetLine(ayarlstcopy,"copyState")!="")
               {
                  QString strcopyState=listGetLine(ayarlstcopy,"copyState").split("|")[1];
                   //qDebug()<<strcopyState;
                copyState=strcopyState.toInt();
                checkbox->setChecked(copyState);
               }

               if(listGetLine(ayarlstcopy,"kullaniciDizin")!="")
                   kullaniciDizinLineEdit->setText(listGetLine(ayarlst,"kullaniciDizin").split("|")[1]);
                   else
                   kullaniciDizinLineEdit->setText("");

           }
          /******************************************************************/
      QString sonuc=myMessageBox("E-Sabit", "\n"
                                          "\nAyarlar Kaydedildi..\n"
                                            "\n","","","tamam",QMessageBox::Information);

yedekStatus();///yedek durumunu tespit alanı
}
QWidget *MainWindow::ayar()
{
    

    QWidget *ayarPage=new QWidget();
  checkbox = new QCheckBox("Her Açılışta Kullanıcı Bilgileri Yedekten Yüklensin.",ayarPage);

     QFont f2( "Arial", fnt-4, QFont::Normal);
    /*******************************************************/
    QStringList ayarlst=fileToList("/usr/share/e-sabit/","e-sabit.conf");
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
    kullaniciYedekleButton->setFixedSize(QSize(boy*3,boy*2));
    kullaniciYedekleButton->setIconSize(QSize(boy*2,boy*1));
    kullaniciYedekleButton->setStyleSheet("Text-align:center");
    kullaniciYedekleButton->setIcon(QIcon(":/icons/backup.svg"));
    kullaniciYedekleButton->setAutoRaise(true);
    kullaniciYedekleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    kullaniciYedekleButton->setFont(f2);
    kullaniciYedekleButton->setText("Kullanıcı Yedekle");

    kullaniciDizinLineEdit=new QLineEdit(ayarPage);
    kullaniciDizinLineEdit->setFixedSize(boy*6,boy);
    if(listGetLine(ayarlst,"kullaniciDizin")!="")
        kullaniciDizinLineEdit->setText(listGetLine(ayarlst,"kullaniciDizin").split("|")[1]);



    connect(kullaniciYedekleButton, &QPushButton::clicked, [=]() {
        bool backup= QFile::exists("/usr/share/e-sabit/backup.sh");
        bool restore=QFile::exists("/usr/share/e-sabit/restore.sh");
        bool esabit=QFile::exists("/usr/share/e-sabit/e-sabit.conf");
        bool kullanicidizin=false;
        if(kullaniciDizinLineEdit->text()!="") kullanicidizin=true;
        if(!(backup&&restore&&esabit&&kullanicidizin))
        {
            QMessageBox messageBox(this);
            messageBox.setText("Uyarı");

            messageBox.setInformativeText("Kullanıcı Ayarları Kaydedilmemiş..\n"
                                          "Lütfen Ayarları Tamamlayınız..");
            QAbstractButton *evetButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
            // QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.exec();
            return;
        }

        QMessageBox messageBox(this);
        messageBox.setText("Uyarı\t\t\t");
        messageBox.setInformativeText("Seçili Kullanıcı Bilgileri Yedeklenecek! Emin misiniz?\n"
                                      "Bu işlem Seçilli Kullanıcının Dizininin Boyutuna ve Bilgisayarınızın Performansına Bağlı Olarak Bir Zaman Alacaktır.\n"
                                      "\nİşlemler Tamamlana Kadar Bekleyiniz!");
        QAbstractButton *evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
        QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
        messageBox.setIcon(QMessageBox::Question);
        messageBox.exec();
        if (messageBox.clickedButton() == evetButton)
        {

            system("pkexec sh -c 'touch /usr/share/e-sabit/sabit&&/usr/share/e-sabit/backup.sh'");
            if(QFile::exists("/usr/share/e-sabit/sabit")==true)
            {
                system("rm -rf /usr/share/e-sabit/sabit");
                //qDebug()<<"Şifre: doğru-kaydet "
                QMessageBox messageBox1(this);
                messageBox1.setInformativeText("\n\nKullanıcı Bilgileri Yedeklendi..\n");
                QAbstractButton *evetButton1 =messageBox1.addButton(tr("Tamam"), QMessageBox::ActionRole);
                // QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
                messageBox1.setIcon(QMessageBox::Information);
                messageBox1.exec();

                yedekStatus();///yedek durumunu tespit alanı

            }
        }



    });
    /*********************************************************************/

    yedekStatus();///yedek durumunu tespit alanı

    QPushButton *kullaniciDizinSelectButton= new QPushButton;
    kullaniciDizinSelectButton->setFixedSize(boy/3*2, boy);
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
/***************************önemli bölüm*************************************************/
        if(!dir.contains("/home/", Qt::CaseInsensitive))
            return;
        if(dir.contains("/home/", Qt::CaseInsensitive)&&dir.split("/")[2]!="")
           kullaniciDizinLineEdit->setText("/home/"+dir.split("/")[2]);
        else return;

        //kullaniciDizinLineEdit->setText(dir);


/****************************************************************************************/

        QMessageBox messageBox(this);
        messageBox.setText("Uyarı");

        messageBox.setInformativeText("Seçtiğiniz Kullanıcı Dizinine Göre Ayarlar Yapılandırılacak. \n İşlemden  Emin Misiniz?");
        QAbstractButton *evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
        QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
        messageBox.setIcon(QMessageBox::Question);
        messageBox.exec();
        if (messageBox.clickedButton() == evetButton) {
            ayarKaydetButtonSlot();
        }
        if (messageBox.clickedButton() == hayirButton) {
            QStringList ayarlstcopy=fileToList("/usr/share/e-sabit/","e-sabit.conf");
            if(listGetLine(ayarlstcopy,"copyState")!="")
            {
                QString strcopyState=listGetLine(ayarlstcopy,"copyState").split("|")[1];
                //qDebug()<<strcopyState;
                copyState=strcopyState.toInt();
                checkbox->setChecked(copyState);
            }
             if(listGetLine(ayarlstcopy,"kullaniciDizin")!="")
                kullaniciDizinLineEdit->setText(listGetLine(ayarlstcopy,"kullaniciDizin").split("|")[1]);
            else
                kullaniciDizinLineEdit->setText("");
        }

     });

/************************************************************************/
    QToolButton *yedekKullaniciYukleButton= new QToolButton;
    yedekKullaniciYukleButton->setFixedSize(QSize(boy*3,boy*2));
    yedekKullaniciYukleButton->setIconSize(QSize(boy*2,boy*1));
    yedekKullaniciYukleButton->setStyleSheet("Text-align:center");
    yedekKullaniciYukleButton->setIcon(QIcon(":/icons/restore.svg"));
    yedekKullaniciYukleButton->setAutoRaise(true);
    yedekKullaniciYukleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    yedekKullaniciYukleButton->setFont(f2);
    yedekKullaniciYukleButton->setText("Yedeği Geri Yükle");

     /************************************************************************/

     connect(yedekKullaniciYukleButton, &QPushButton::clicked, [=]() {
         bool backup= QFile::exists("/usr/share/e-sabit/backup.sh");
         bool restore=QFile::exists("/usr/share/e-sabit/restore.sh");
         bool esabit=QFile::exists("/usr/share/e-sabit/e-sabit.conf");
         bool kullanicidizin=false;
         if(kullaniciDizinLineEdit->text()!="") kullanicidizin=true;
         if(!(backup&&restore&&esabit&&kullanicidizin))
         {
             QMessageBox messageBox(this);
             messageBox.setText("Uyarı");

             messageBox.setInformativeText("Kullanıcı Ayarları Kaydedilmemiş..\n"
                                           "Lütfen Ayarları Tamamlayınız..");
             QAbstractButton *evetButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
             // QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
             messageBox.setIcon(QMessageBox::Warning);
             messageBox.exec();
             return;
         }

         QMessageBox messageBox(this);
         messageBox.setText("Uyarı\t\t\t");
         messageBox.setInformativeText("Seçili Kullanıcı Bilgileri Yedekten Yüklenecek! Emin misiniz?\n"
                                       "Bu işlem Seçilli Kullanıcının Dizininin Boyutuna ve Bilgisayarınızın Performansına Bağlı Olarak Bir Zaman Alacaktır.\n"
                                       "\nİşlemler Tamamlana Kadar Bekleyiniz!");
         QAbstractButton *evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
         QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
         messageBox.setIcon(QMessageBox::Question);
         messageBox.exec();
         if (messageBox.clickedButton() == evetButton)
         {

             system("pkexec sh -c 'touch /usr/share/e-sabit/sabit&&/usr/share/e-sabit/restore.sh'");
             if(QFile::exists("/usr/share/e-sabit/sabit")==true)
             {
                 system("rm -rf /usr/share/e-sabit/sabit");
                 //qDebug()<<"Şifre: doğru-kaydet "
                 QMessageBox messageBox1(this);
                 messageBox1.setInformativeText("\n\nKullanıcı Bilgileri Geri Yüklendi..\n");
                 QAbstractButton *evetButton1 =messageBox1.addButton(tr("Tamam"), QMessageBox::ActionRole);
                 // QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
                 messageBox1.setIcon(QMessageBox::Information);
                 messageBox1.exec();
             }
         }




     });


     QFont f1( "Arial", 8, QFont::Normal);
    checkbox->setFont(f1);
    checkbox->setChecked(copyState);
   /// qDebug()<<"copystate1"<<copyState;
    connect(checkbox, &QCheckBox::clicked, [=]() {
        copyState=checkbox->checkState();
        if(kullaniciDizinLineEdit->text()=="")
        {
           // qDebug()<<"kullanıcı seçilmemiş";
            QMessageBox messageBox(this);
            messageBox.setText("Uyarı");

            messageBox.setInformativeText("Sabitlenecek Kullanıcı Seçilmemiş\n");
            QAbstractButton *evetButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
           // QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.exec();
            copyState=!copyState;
             checkbox->setChecked(copyState);

 return;
        }


        if(copyState)
        {
            QMessageBox messageBox(this);
            messageBox.setText("Uyarı");

            messageBox.setInformativeText("Her Açılışta kullanıcı Yedeklenecek Şekilde Yapılandırılacaktır. \n İşlemden  Emin Misiniz?");
            QAbstractButton *evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
            QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
            messageBox.setIcon(QMessageBox::Question);
            messageBox.exec();
            if (messageBox.clickedButton() == evetButton) {
                system("pkexec sh -c 'touch /usr/share/e-sabit/sabit&&systemctl enable e-sabit.service&&systemctl start e-sabit.service&&systemctl daemon-reload'");
                if(QFile::exists("/usr/share/e-sabit/sabit")==true)
                {
                    system("rm -rf /usr/share/e-sabit/sabit");
                    //qDebug()<<"Şifre: doğru-kaydet "
                    /***********************e-sabit.conf oluşturuluyor***********************************/
                    system("mv /usr/share/e-sabit/e-sabit.conf /usr/share/e-sabit/e-sabit.conf.old");
                    QStringList ayarlist;
                    ayarlist.append("kullaniciDizin|"+kullaniciDizinLineEdit->text());
                    ayarlist.append("copyState|"+QString::number(copyState));
                     listToFile("/usr/share/e-sabit/",ayarlist,"e-sabit.conf");
                    /********************file permission*************************/
                    QFile file("/user/share/e-sabit/e-sabit.conf");
                    if (file.open(QFile::ReadWrite)){
                        if(!file.setPermissions(QFileDevice::WriteUser | QFileDevice::ReadUser|QFileDevice::ExeUser|
                                                QFileDevice::WriteOwner | QFileDevice::ReadOwner|QFileDevice::ExeOwner|
                                                QFileDevice::WriteGroup | QFileDevice::ReadGroup|QFileDevice::ExeGroup|
                                                QFileDevice::WriteOther | QFileDevice::ReadOther|QFileDevice::ExeOther)){
                            qDebug()<< "Error in permissions";
                        }
                        file.close();
                    }


                }
                else
                {
                    copyState=!(copyState);
                     checkbox->setChecked(copyState);
                }
            }
             if (messageBox.clickedButton() == hayirButton) {
                 copyState=!(copyState);
                  checkbox->setChecked(copyState);
             }

        }
       else
        {
            QMessageBox messageBox(this);
            messageBox.setText("Uyarı");
            messageBox.setInformativeText("Her Açılışta kullanıcı Yedeklenmeyecek Şekilde Yapılandırılacaktır. \n İşlemden  Emin Misiniz?");
            QAbstractButton *evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
            QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
            messageBox.setIcon(QMessageBox::Question);
            messageBox.exec();
            if (messageBox.clickedButton() == evetButton) {
                system("pkexec sh -c 'touch /usr/share/e-sabit/sabit&&systemctl stop e-sabit.service&&systemctl disable e-sabit.service&&systemctl daemon-reload'");
                if(QFile::exists("/usr/share/e-sabit/sabit")==true)
                {
                    system("rm -rf /usr/share/e-sabit/sabit");
                    //qDebug()<<"Şifre: doğru-kaydet "
                }
                else
                {
                    copyState=!(copyState);
                     checkbox->setChecked(copyState);
                }
            }
            if (messageBox.clickedButton() == hayirButton) {
                copyState=!(copyState);
                 checkbox->setChecked(copyState);
            }

        }

        // qDebug()<<copyState;
});


    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(boy*3, boy*2);
    helpButton->setIconSize(QSize(boy*2,boy*1));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    //int fnt=boy/2.5;
 //   qDebug()<<fnt;
    QString font=QString::number(fnt);
    helpButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");

    helpButton->setText("Yardım");
    helpButton->setAutoRaise(true);

     helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {

        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><img  src=\":/icons/use.png\" /></center> "
                       "<br/><b>1-</b> <img src=\":/icons/selectdirectory.png\" />."
                      "<br/>Sabitlemek istediğiniz kullanıcının ev dizinini seçileceğimiz bölüm."
                     " Bu kullanıcı ev dizini seçildiğinde sizden yetkili kullanıcı şifresi istenecektir."
                      "<br/><br/><b>2-</b> <img src=\":/icons/selectcheckbox.png\" />"
                      "<br/>Sistem her açıldığında daha önceden yedeklenmiş kullanıcı dizinini kullanıcı "
                     "ayarlarıyla değiştirilmesini sağlayan seçenektir. İlk kurulumda pasif durumdadır. "
                     "Bilişim sınıfı, internet kafe vb. ortamlarda bu seçenek seçilerek her açılışta kullanıcı ayarları sıfırlanabilir."
                     "<br/><b>Kişisel kulladığımız bilgisayarda bu seçeneğin seçilmesi tavsiye edilmemektedir.</b>"
                      "<br/><br/><b>3-</b> <img src=\":/icons/backup.png\" />"
                      "<br/>Seçilmiş kullanıcı dizini /var/backups/ altında yedekleyen seçenektir."
                     "Sistemde değişiklik yapıldığında mutlaka bu seçenekle yedek güncellenmelidir."
                     "Kullanıcı yedeklenirken bilgisayarın performansı ve kullanıcı dizin boyutuna göre bir zaman alacaktır."
                     "Yedekleme tamamlandı mesajına kadar bilgisayarda hiç bir işlem yapılmadan beklenmelidir."
                      "<br/><br/><b>4-</b> <img src=\":/icons/restore.png\" />"
                      "<br/>Yedeklenmişkullanıcı dizini isteğe kullanıcı ayarlarıyla değiştiren seçenektir."
                     "Bu işlem yedeklenen son yedeği yükleyecektir. "
                     "Sistemde bozulmalar vb. durumda isteğe bağlı olarak yapılması tavsiye edilir."
                     "<br/><br/><b>Not:</b> Yazılımı kullanmadan önce <b>Bilgilendirme ve Lisans </b> bölümlerini mutlaka inceleyiniz."
                     "<br/><b>Bilişim sınıfı ve internet kafe vb. yerlerde kullanmak için aşağıda anlatılan <i>1. , 2. , 3.</i>adımlar mutlaka seçilerek ayarlanmalıdır..</b>"

                     );
        QPrinter pdf;
            pdf.setOutputFileName("/tmp/temelislem.pdf");
            pdf.setOutputFormat(QPrinter::PdfFormat);
            doc->print(&pdf);

        QTextEdit *document = new QTextEdit();
        document->setReadOnly(true);
        //  document->show();
         document->setDocument(doc);
        QVBoxLayout * vbox = new QVBoxLayout();
         QHBoxLayout * hbox1= new QHBoxLayout();

        // hbox1->addWidget(commandFileLabel);
         hbox1->addWidget(document);

         vbox->addLayout(hbox1);
         QDialog * d1 = new QDialog();
         d1->setWindowTitle("Yardım Penceresi");
         d1->setFixedSize(QSize(boy*27,boy*20.5));
         auto appIcon = QIcon(":/icons/e-sabit.svg");
         d1->setWindowIcon(appIcon);

         d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

         d1->setLayout(vbox);
          d1->exec();

 });
  //  QLabel *lbl=new QLabel(ayarPage);
//lbl->setFixedSize(this->width(),75);
    auto layout = new QGridLayout(ayarPage);
    layout->setContentsMargins(0, 0, 0,0);
   /// layout->setVerticalSpacing(5);
   /// layout->setColumnMinimumWidth(0, 37);
    //layout->addWidget(adLabel, 2,0,1,2);
   auto *lblDizin=new QLabel("Yedeklenecek Kullanıcı Dizini");
    lblDizin->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    layout->addWidget(lblDizin, 10,0,1,1);

    layout->addWidget(kullaniciDizinLineEdit, 10,1,1,1);
    layout->addWidget(kullaniciDizinSelectButton, 10,2,1,1);

     layout->addWidget(checkbox,20,0,1,3);
    QHBoxLayout *layout1 = new QHBoxLayout;
         layout1->addWidget(kullaniciYedekleButton);
         layout1->addWidget(yedekKullaniciYukleButton);
         layout1->addWidget(helpButton);
         layout->addLayout(layout1, 30, 0,1,3,Qt::AlignHCenter);

        layout->addWidget(labelYedekStatus, 35, 0,1,3,Qt::AlignHCenter);


///layout->setColumnStretch(6, 255);

    return ayarPage;
}
#endif // AYAR_H
