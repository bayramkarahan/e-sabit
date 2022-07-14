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
#include<QButtonGroup>
#include<QRadioButton>

#ifndef AYAR_H
#define AYAR_H
void MainWindow::kullaniciYedekleButtonSlot()
{
    bool kullanicidizin=false;
    if(kullaniciDizinLineEdit->text()!="") kullanicidizin=true;
    if(!(kullanicidizin)){
        myMessageBox("Uyarı", "\n\nKullanıcı Ayarları Kaydedilmemiş..\n\n","","","tamam",QMessageBox::Warning);
        return;
    }
    QString sonuc=myMessageBox("Uyarı", "\n\nSeçili "
             +kullaniciDizinLineEdit->text().split("/")[2]
             +" Kullanıcı Bilgileri Yedeklenecek! Emin misiniz?"
            "\n\nBu işlem Seçilli Kullanıcının Dizininin Boyutuna ve Bilgisayarınızın Performansına Bağlı Olarak Bir Zaman Alacaktır.\n"
            "\nİşlemler Tamamlana Kadar Bekleyiniz!","evet","hayir","",QMessageBox::Question);
    if (sonuc == "evet"){
        if(passwordKontrolSlot("pkexec sh -c 'touch /usr/share/e-sabit/sabit&&/usr/share/e-sabit/backup.sh'"))
        {
            myMessageBox("", "\n\nKullanıcı Bilgileri Yedeklendi..\n","","","tamam",QMessageBox::Information);
            yedekStatus();///yedek durumunu tespit alanı
        }
    }
}

void MainWindow::yedekStatus()
{
    if(kullaniciDizinLineEdit->text()!=""&&kullaniciDizinLineEdit->text().split("/").count()>1)
    {
        if(kullaniciDizinLineEdit->text()!=""&&QFile::exists("/var/backups/e-sabit/"+kullaniciDizinLineEdit->text().split("/")[2])==true){
            QDateTime local(QFileInfo("/var/backups/e-sabit/"+kullaniciDizinLineEdit->text().split("/")[2]).lastRead());
            // qDebug() << "Local time is:" << local.toString("yyyy-MM-dd HH:mm:ss");
            labelYedekStatus->setText("Kullanıcı Yedeği Var\tYedeklenme Zamanı: "+local.toString("yyyy-MM-dd HH:mm:ss"));
            labelYedekStatus->setStyleSheet("Text-align:center; background-color:rgba(0, 255, 0, 100); font-size:"+QString::number(fnt-2)+"px;");

        }
        else{
            labelYedekStatus->setText("Kullanıcı Yedeği Yok! --> Kullanıcı Yedekle Seçeneği İle Yedek Alın..");
            labelYedekStatus->setStyleSheet("Text-align:center; background-color:rgba(255, 0, 0, 100); font-size:"+QString::number(fnt-2)+"px;");

        }
    }

}

QWidget *MainWindow::ayar()
{
    QWidget *ayarPage=new QWidget();
    QButtonGroup *buttonGroup = new QButtonGroup(ayarPage);
    rb0->setText("Her Açılışta Kullanıcı Bilgilerini Yedekten Yükle");
    rb1->setText("İşlem Yapma");
    rb1->setChecked(true);

    buttonGroup->addButton(rb0, 0);
    buttonGroup->addButton(rb1, 1);
    connect(rb0, &QRadioButton::clicked, [=]() {
      //  QString sonuc=myMessageBox("E-Sabit", "\n\nAyarlar Kaydedildi..\n\n","evet","hayir","tamam",QMessageBox::Information);
       //qDebug()<<"rb1 click";
        yedekState="1";
        system("rm -rf /usr/share/e-sabit/e-sabit.conf");
        QStringList ayar_lst;
        ayar_lst=listRemove(ayar_lst,"yedekState");
        ayar_lst.append("kullaniciDizin|"+kullaniciDizinLineEdit->text());
        ayar_lst.append("yedekState|"+yedekState);
        listToFile("/usr/share/e-sabit/",ayar_lst,"e-sabit.conf");
        if(kullaniciDizinLineEdit->text()!=""&&kullaniciDizinLineEdit->text().split("/").count()>1)
        {
            if(kullaniciDizinLineEdit->text()!=""&&QFile::exists("/var/backups/e-sabit/"+kullaniciDizinLineEdit->text().split("/")[2])!=true){
                kullaniciYedekleButtonSlot();///Kullanıcı seçildiği için yedekleme soruluyor
            }
        }
        yedekStatus();///yedek durumunu test eder
    });
    connect(rb1, &QRadioButton::clicked, [=]() {
        //qDebug()<<"rb2 click";
        yedekState="0";
        system("rm -rf /usr/share/e-sabit/e-sabit.conf");
        QStringList ayar_lst;
        ayar_lst=listRemove(ayar_lst,"yedekState");
        ayar_lst.append("kullaniciDizin|"+kullaniciDizinLineEdit->text());
        ayar_lst.append("yedekState|"+yedekState);
        listToFile("/usr/share/e-sabit/",ayar_lst,"e-sabit.conf");
         yedekStatus();///yedek durumunu test eder
     });

     QFont f2( "Arial", fnt-4, QFont::Normal);
    /*******************************************************/
    QStringList ayarlst=fileToList("/usr/share/e-sabit/","e-sabit.conf");
    /*******************************************/

    if(listGetLine(ayarlst,"yedekState")!="")
    {
        yedekState=listGetLine(ayarlst,"yedekState").split("|")[1];
        if(yedekState=="1")
            rb0->setChecked(true);
        else
            rb1->setChecked(true);

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
kullaniciYedekleButtonSlot();
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
        /****************************************************************************************/
        QString sonuc=myMessageBox("Uyarı", "\nSeçtiğiniz "+kullaniciDizinLineEdit->text().split("/")[2]
                                   +" Kullanıcı Dizinine Göre Ayarlar Yapılandırılacak."
                                            "\n\n İşlemden  Emin Misiniz?","evet","hayir","",QMessageBox::Question);
        if (sonuc == "evet") {
            /*****************************************************************/
            system("rm -rf /usr/share/e-sabit/e-sabit.conf");
            QStringList ayarlist;
            ayarlist.append("kullaniciDizin|"+kullaniciDizinLineEdit->text());
            ayarlist.append("yedekState|1");
            listToFile("/usr/share/e-sabit/",ayarlist,"e-sabit.conf");
            QString yuser=kullaniciDizinLineEdit->text().split("/")[2];
            rb0->setChecked(true);
            QString sonuc=myMessageBox("E-Sabit", "\n"
                                                  "\nAyarlar Kaydedildi..\n"
                                                  "\n","","","tamam",QMessageBox::Information);


            if(kullaniciDizinLineEdit->text()!=""&&kullaniciDizinLineEdit->text().split("/").count()>1)
            {
                if(kullaniciDizinLineEdit->text()!=""&&QFile::exists("/var/backups/e-sabit/"+kullaniciDizinLineEdit->text().split("/")[2])!=true){
                    kullaniciYedekleButtonSlot();///Kullanıcı seçildiği için yedekleme soruluyor
                }
            }
            yedekStatus();///yedek durumunu tespit alanı
            /*************************************************************/


        }
        if (sonuc=="hayir") {
            QStringList ayarlstcopy=fileToList("/usr/share/e-sabit/","e-sabit.conf");
            if(listGetLine(ayarlst,"yedekState")!="")
            {
                yedekState=listGetLine(ayarlst,"yedekState").split("|")[1];
                if(yedekState=="1")
                    rb0->setChecked(true);
                else
                    rb1->setChecked(true);

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
           bool kullanicidizin=false;
         if(kullaniciDizinLineEdit->text()!="") kullanicidizin=true;
         if(!(kullanicidizin)){
             myMessageBox("Uyarı", "\n\nKullanıcı Ayarları Kaydedilmemiş..\n\n","","","tamam",QMessageBox::Warning);
             return;
         }
         QString sonuc=myMessageBox("Uyarı", "\n\nSeçili "
                                    +kullaniciDizinLineEdit->text().split("/")[2]
                                    +" Kullanıcı Bilgileri Yedekten Yüklenecek! Emin misiniz?\n"
                                             "\n\nBu işlem Seçilli Kullanıcının Dizininin Boyutuna ve Bilgisayarınızın Performansına Bağlı Olarak Bir Zaman Alacaktır.\n"
                                             "\nİşlemler Tamamlana Kadar Bekleyiniz!","evet","hayir","",QMessageBox::Question);
         if (sonuc == "evet"){
             if(passwordKontrolSlot("pkexec sh -c 'touch /usr/share/e-sabit/sabit&&/usr/share/e-sabit/restorebutton.sh'"))
             {
                 myMessageBox("", "\n\nKullanıcı Bilgileri Geri Yüklendi..\n","","","tamam",QMessageBox::Information);
                 yedekStatus();///yedek durumunu tespit alanı
             }
         }

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
                     "Kullanıcı dizini seçilgiğinde <b>2.</b> adım otomatik seçilir ve kullanıcı yedeklemesi için size öneride bulunacaktır."
                      "<br/><br/><b>2-</b> <img src=\":/icons/selectcheckbox.png\" />"
                      "<br/>Sistem her açıldığında daha önceden yedeklenmiş kullanıcı dizinini kullanıcı "
                     "ayarlarıyla değiştirilmesini sağlayan seçenektir. <b>İşlem Yapma</b> seçeneği seçilerek pasif duruma getirilebilir. "
                     "Bilişim sınıfı, internet kafe vb. ortamlarda bu seçenek seçilerek her açılışta kullanıcı ayarları sıfırlanabilir."
                     "<br/><b>Kişisel kulladığımız bilgisayarda bu seçeneğin seçilmesi tavsiye edilmemektedir.</b>"
                      "<br/><br/><b>3-</b> <img src=\":/icons/backup.png\" />"
                      "<br/>Seçilmiş kullanıcı dizini /var/backups/e-sabit/ altında yedekleyen seçenektir."
                     "Sistemde değişiklik yapıldığında mutlaka bu seçenekle yedek güncellenmelidir."
                     "Kullanıcı yedeklenirken bilgisayarın performansı ve kullanıcı dizin boyutuna göre bir zaman alacaktır."
                     "Yedekleme tamamlandı mesajına kadar bilgisayarda hiç bir işlem yapılmadan beklenmelidir."
                      "<br/><br/><b>4-</b> <img src=\":/icons/restore.png\" />"
                      "<br/>Yedeklenmişkullanıcı dizini isteğe kullanıcı ayarlarıyla değiştiren seçenektir."
                     "Bu işlem yedeklenen son yedeği yükleyecektir. "
                     "Sistemde bozulmalar vb. durumda isteğe bağlı olarak yapılması tavsiye edilir."
                     "<br/><br/><b>Not:</b> Yazılımı kullanmadan önce <b>Bilgilendirme ve Lisans </b> bölümlerini mutlaka inceleyiniz."
                     "<br/><b>Bilişim sınıfı ve internet kafe vb. yerlerde kullanmak için burada anlatılan <i>1. , 2. , 3.</i>adımları mutlaka seçilerek ayarlanmalıdır..</b>"

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
         d1->setFixedSize(QSize(boy*27,boy*21));
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
    layout->addWidget(rb0,15,0,1,3);
    layout->addWidget(rb1,16,0,1,3);
    QHBoxLayout *layout1 = new QHBoxLayout;


    layout1->addWidget(kullaniciYedekleButton);
    layout1->addWidget(yedekKullaniciYukleButton);
    layout1->addWidget(helpButton);
    layout->addLayout(layout1, 35, 0,1,3,Qt::AlignHCenter);

    layout->addWidget(labelYedekStatus, 30, 0,1,3,Qt::AlignHCenter);


///layout->setColumnStretch(6, 255);

    return ayarPage;
}
#endif // AYAR_H
