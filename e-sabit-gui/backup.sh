#!/bin/bash
usr=$(cat /usr/share/e-sabit/e-sabit.conf|grep "kullaniciDizin"|cut -d'|' -f 2)

user=$(echo "$usr"|cut -d'/' -f 3)
bilgi=$(cat /usr/share/e-sabit/e-sabit.conf|grep "yedekState|1")

if [ -n "$user" ]; then
        pkill firefox
	rsync -apoglr --delete /home/"$user"/ /var/backups/e-sabit/"$user"/
fi
