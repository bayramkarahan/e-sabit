#!/bin/bash
usr=$(cat /usr/share/e-sabit/e-sabit.conf|grep "kullaniciDizin"|cut -d'|' -f 2)

user=$(echo "$usr"|cut -d'/' -f 3)
bilgi=$(cat /usr/share/e-sabit/e-sabit.conf|grep "yedekState|1")

esabit="/home/$user/Masaüstü/esabit"



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
