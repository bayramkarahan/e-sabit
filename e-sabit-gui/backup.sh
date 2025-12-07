#!/bin/bash
conf="/usr/share/e-sabit/e-sabit.json"
# Dizini oku
kullaniciDizin=$(jq -r '.[0].kullaniciDizin' "$conf")
# Sadece kullanıcı adı
user=$(basename "$kullaniciDizin")
# yedekState true mu?
yedekState=$(jq -r '.[0].yedekState' "$conf")
esabit="/home/$user/Masaüstü/esabit"
# yedekState false ise hiçbir şey yapma
if [ "$yedekState" != "true" ]; then
    exit 0
fi

if [ -n "$user" ]; then
    # Eğer Serbest dizini yoksa oluştur
    if [ ! -d "$esabit" ]; then
        mkdir -p "$esabit"
	chown "$user":"$user" "$esabit"
	chmod 755 "$esabit"
    fi
    rsync -apoglr --delete \
        --exclude='Masaüstü/esabit' \
	/home/"$user"/ /var/backups/e-sabit/"$user"/
fi
