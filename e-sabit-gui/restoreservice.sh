#!/bin/bash
usr=$(cat /usr/share/e-sabit/e-sabit.conf|grep "kullaniciDizin"|cut -d'|' -f 2)
user=$(echo "$usr"|cut -d'/' -f 3)

bilgi=$(cat /usr/share/e-sabit/e-sabit.conf|grep "yedekState|1")

esabit="/home/$user/Desktop/esabit"

# Eğer Serbest dizini yoksa oluştur
if [ ! -d "$esabit" ]; then
    mkdir -p "$esabit"
    chown "$user":"$user" "$esabit"
    chmod 755 "$esabit"
fi

if [ "yedekState|1" == "$bilgi" ]; then

	if [ -d /var/backups/e-sabit/"$user" ]; then
                rsync -apoglr --delete \
                    --exclude='Desktop/esabit' \
                    "$backup"/ /home/"$user"/

                chown -R "$user":"$user" /home/"$user"/
                # chmod -R 744 /home/"$user"/   # gerekmedikçe devre dışı bırak
	fi
fi
