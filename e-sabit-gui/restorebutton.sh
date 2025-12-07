#!/bin/bash
conf="/usr/share/e-sabit/e-sabit.json"   # JSON biçiminde
# JSON'dan kullaniciDizin değerini al
usr=$(jq -r '.[0].kullaniciDizin' "$conf")
user=$(basename "$usr")
backup="/var/backups/e-sabit/$user"
esabit="/home/$user/Masaüstü/esabit"

if [ -d "$backup" ]; then

        # Eğer Serbest dizini yoksa oluştur
	if [ ! -d "$esabit" ]; then
	        mkdir -p "$esabit"
		chown "$user":"$user" "$esabit"
		chmod 755 "$esabit"
	fi

    rsync -apoglr --delete \
        --exclude='Masaüstü/esabit' \
	"$backup"/ /home/"$user"/

    chown -R "$user":"$user" /home/"$user"/
    chmod -R 755 /home/"$user"/   # gerekmedikçe devre dışı bırak
fi
