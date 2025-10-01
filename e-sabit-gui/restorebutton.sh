#!/bin/bash

conf="/usr/share/e-sabit/e-sabit.conf"

usr=$(grep "kullaniciDizin" "$conf" | cut -d'|' -f 2)
user=$(basename "$usr")
backup="/var/backups/e-sabit/$user"
esabit="/home/$user/Masaüstü/esabit"

# Eğer Serbest dizini yoksa oluştur
if [ ! -d "$esabit" ]; then
    mkdir -p "$esabit"
    chown "$user":"$user" "$esabit"
    chmod 755 "$esabit"
fi

if [ -d "$backup" ]; then
    rsync -apoglr --delete \
        --exclude='Masaüstü/esabit' \
        "$backup"/ /home/"$user"/

    chown -R "$user":"$user" /home/"$user"/
    chmod -R 755 /home/"$user"/   # gerekmedikçe devre dışı bırak
fi
