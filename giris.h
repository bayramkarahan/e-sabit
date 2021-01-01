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
QWidget *MainWindow::giris()
{
    QWidget *girisPage=new QWidget();
    /*******************************************************/
    QLabel *localuserLabel=new QLabel(girisPage);
    localuserLabel->setText("Yetkili Kullanıcı Adı");
    localuserLabel->setStyleSheet("background-color: #acacac");

    user=QDir::homePath().split("/")[2];
    localUsername=new QLineEdit(girisPage);
    localUsername->setFixedSize(en*6-3,boy);
    localUsername->setText(user);
    localUsername->setStyleSheet("background-color: #ffffff");

    QLabel *localpasswordLabel=new QLabel(girisPage);
    localpasswordLabel->setText("Yetkili Kullanıcı Şifresi");
    localpasswordLabel->setStyleSheet("background-color: #acacac");

    localPassword=new QLineEdit(girisPage);
    localPassword->setFixedSize(en*6-3,boy);
    localPassword->setEchoMode(QLineEdit::Password);
    localPassword->setStyleSheet("background-color: #ffffff");
   auto  screenbtn = new QPushButton(girisPage);
    screenbtn->setFixedSize(QSize(boy*3,boy*3));
    screenbtn->setIconSize(QSize(boy*3,boy*3));
    screenbtn->setAutoFillBackground(true);
    screenbtn->setIcon(QIcon(":/icons/sabit.svg"));
    screenbtn->setFlat(true);

    QPushButton *girisButton= new QPushButton;
girisButton->setFixedSize(boy*3, 30);
///ayarKaydetButton->setIconSize(QSize(150,30));
girisButton->setText("Giriş");
girisButton->setStyleSheet("Text-align:center");

connect(girisButton, &QPushButton::clicked, [=]() {
   kontrol();
    if (status==false) return;
 ///   qDebug()<<"Giriş Başarılı";
   // localPassword->setText("");
    aw->setEnabled(true);
    tw->setCurrentIndex(1);
/**************************************************************/

});

    auto *sat1=new QLabel(girisPage);
    sat1->setText("Linux'da Kullanıcı Bilgilerini Değişmez Hale Getiren Uygulamadır.");
    auto *sat2=new QLabel(girisPage);
    sat2->setText("Sistemdeki Bir Kullanıcı Değişmez Hale Getirilebilir.");
    auto *sat3=new QLabel(girisPage);
    sat3->setText("Kullanıcının Şifresi Dahil Tüm Bilgileri Değişmez Hale Getirilir.");

    QFont ff( "Arial", 8, QFont::Normal);
    sat1->setFont(ff);
    sat2->setFont(ff);
    sat3->setFont(ff);

    auto layout = new QGridLayout(girisPage);
    layout->setContentsMargins(0, 0, 0,0);
   // layout->setVerticalSpacing(5);
    //layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(new QLabel("<font size=2>E-Sabit</font>"),0,0,1,2,Qt::AlignHCenter);
    layout->addWidget(screenbtn, 5,0,1,2,Qt::AlignHCenter);
    layout->addWidget(localuserLabel, 7,0,1,1);
    layout->addWidget(localUsername, 7,1,1,1);
    layout->addWidget(localpasswordLabel, 8,0,1,1);
    layout->addWidget(localPassword, 8,1,1,1);
    layout->addWidget(girisButton,9,1,1,1);

    layout->addWidget(sat1,10,0,1,2);
    layout->addWidget(sat2,15,0,1,2);
    layout->addWidget(sat3,20,0,1,2);

   // layout->setColumnStretch(6, 255);


    return girisPage;
}
#ifndef GIRIS_H
#define GIRIS_H

#endif // GIRIS_H
