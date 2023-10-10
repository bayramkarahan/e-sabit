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
    QPixmap pic(":/icons/e-sabit.svg");
    auto Logo = new QLabel(girisPage);
    Logo->setFixedSize(QSize(boy*3,boy*3));
    Logo->setPixmap(pic);
    Logo->setScaledContents(true);

    auto *sat1=new QLabel(girisPage);
    sat1->setText("1- Kullanıcı Bilgilerini Değişmez Hale Getiren Uygulamadır.");

    auto *sat2=new QLabel(girisPage);
    sat2->setText("2- Uygulama Debian(Pardus) tabanlı dağıtımlar için yazılmıştır.");

    auto *sat3=new QLabel(girisPage);
    sat3->setWordWrap(true);
    sat3->setFixedSize(this->width(),boy*1.5);
    sat3->setText("3- Uygulama; Bilişim sınıf, internet kafe, kütüphane vb. halka açık alanlar"
                  " için  kullanılan bilgisayarların ayarlarını sabitlemek için yazılmıştır.");

    auto *sat4=new QLabel(girisPage);
    sat4->setText("4- Kişisel bilgisayarlar için tavsiye edilmemektedir.");

    auto *sat5=new QLabel(girisPage);
    sat5->setText("5- Bu Uygulamayı kullanmaktan oluşabilecek zarar veya veri kayıplarından"
                  "   geliştirici sorumlu tutlamayacağını, yazılımı kuran ve kullanan kabul eder.");
    sat5->setWordWrap(true);
    sat5->setFixedSize(this->width(),boy*1.5);

 //   QLabel *lbl=new QLabel(girisPage);
//lbl->setFixedSize(boy,boy*5);
   QFont ff( "Arial", fnt-4, QFont::Normal);
    sat1->setFont(ff);
    sat2->setFont(ff);
    sat3->setFont(ff);
    sat4->setFont(ff);
    sat5->setFont(ff);

    auto layout = new QGridLayout(girisPage);
    layout->setContentsMargins(0, 0, 0,0);
   // layout->setVerticalSpacing(5);
    //layout->setColumnMinimumWidth(0, 37);
     layout->addWidget(Logo, 1,0,1,2,Qt::AlignHCenter);

    layout->addWidget(sat1,5,0,1,2);
     layout->addWidget(sat2,10,0,1,2);
     layout->addWidget(sat3,15,0,1,2);
     layout->addWidget(sat4,20,0,1,2);
     layout->addWidget(sat5,25,0,1,2);

   // layout->addWidget(lbl,30,0,1,2);

    // layout->setColumnStretch(6, 255);


    return girisPage;
}
#ifndef GIRIS_H
#define GIRIS_H

#endif // GIRIS_H
