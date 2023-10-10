#!/bin/bash
usr=$(cat /usr/share/e-sabit/e-sabit.conf|grep "kullaniciDizin"|cut -d'|' -f 2)
user=$(echo "$usr"|cut -d'/' -f 3)

bilgi=$(cat /usr/share/e-sabit/e-sabit.conf|grep "yedekState|1")

if [ "yedekState|1" == "$bilgi" ]; then

	if [ -d /var/backups/e-sabit/"$user" ]; then
		rsync -apoglr --delete /var/backups/e-sabit/"$user"/ /home/"$user"/
		chown -R "$user":"$user" /home/"$user"/
		chmod -R 744 /home/"$user"/
	fi
fi
