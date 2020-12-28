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

    QPalette palette;
    QPixmap pixmap(":/icons/sabit.svg");
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    auto  screenbtn = new QPushButton(girisPage);
    screenbtn->setFixedSize(QSize(boy*6,boy*6));
    screenbtn->setIconSize(QSize(boy*4,boy*4));
    screenbtn->setAutoFillBackground(true);
    screenbtn->setIcon(QIcon(pixmap));
    screenbtn->setFlat(true);

    auto layout = new QGridLayout(girisPage);
    layout->setContentsMargins(0, 0, 0,0);
   // layout->setVerticalSpacing(5);
    //layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(new QLabel("<font size=6>E-Sabit</font>"),0,0,1,1,Qt::AlignHCenter);
    layout->addWidget(screenbtn, 5,0,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=2>Linux'da Kullanıcı Bilgilerini Değişmez Hale Getiren Uygulamadır.</font>"),10,0,1,1);
    layout->addWidget(new QLabel("<font size=2>Sistemdeki Bir Kullanıcı Değişmez Hale Getirilebilir.</font>"),15,0,1,1);
    layout->addWidget(new QLabel("<font size=2>Kullanıcının Şifresi Dahil Tüm Bilgileri Değişmez Hale Getirilir.</font>"),20,0,1,1);

   // layout->setColumnStretch(6, 255);


    return girisPage;
}
#ifndef GIRIS_H
#define GIRIS_H

#endif // GIRIS_H
